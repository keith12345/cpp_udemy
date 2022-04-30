## Cluster manager

Spark has its own standalone cluster manager.  
YARN and Mesos are other examples of cluster managers.

## Driver and Executor processes

**Driver** - runs your `main()` functions - sits on a node in the cluster.  
Responsible for three things:  
* maintaing information about the Spark Application
* responding to a user's program or input
* analyzing/distributing/scheduling work across the executors

**Executors** - assigned work by the drivers.  
Responsible for two things:  
* execute the assigned code
* report back with the results


When stuff in run locally, Drivers and executors are typically run as different threads from the same processor.

## Starting spark

when you start a spark shell, you implicitly create a **Driver** process called a **SparkSession** that manages 
the **Spark Application**.  
When you start though a standalone application using **spark-submit**, you must create the SparkSession object yourself
in your application code.

## Transformations

Core data structures in spark are _immutable_.

```scala
scala> val myRange = spark.range(1000).toDF("number")
myRange: org.apache.spark.sql.DataFrame = [number: bigint]

scala> val divisBy2 = myRange.where("number % 2 = 0")
divisBy2: org.apache.spark.sql.Dataset[org.apache.spark.sql.Row] = [number: bigint]
```

```python
>>> my_range = spark.range(1000).toDF("number")
>>> divis_by_2 = my_range.where("number % 2 = 0")
```

Note that these return no output.  
All we've done is specify an abstract transformation, spark will not act on transformations until we call an **action**.

### Two types of transformations

Those with **narrow dependencies** (transformations using these are called **narrow transformation**) - those for which 
each input partition will contribute to one output partition.

The `where` statement specifies a narrow dependeny - one input partition contributes to at most one output partition.

Input partitions to output partitions are either matched 1-to-1 (or are reduced to fewer partitions).

A **wide dependency** style transformtion (or **wide transformation**) will have input partitions contributing to many
output partitions - think `n x m` complexity.  
This is often referred to as a **shuffle** in which Spark will exchange partitions across a cluster.

With narrow transformations, spark with automatically perform an operation called **pipelining** - meaning that if we
specify multiple filters on DataFrames, they'll all be performed in memory (can't say the same for shuffles).  
Spark will write data to disk during shuffles when necessary.

## Lazy Evaluation

Basically just means that spark will late until the last minute to execute of graph of computation instructions. This
allows spark to better optimize the instructions you've passed.  

Spark has something called a **predicate pushdown** in DataFrames.  
If we build a large spark job with a filter at the end that only requires one row from the source data, then only one
fow will be fetched. Spark will "push the filter down" automatically.

## Actions

Transformations all to build up a logical transformation plan.  
To trigger the computation, we run an **action**.  
An action instructs Spark to compute a result from a series of transformations.  
The simplest example of an action is `count`.

```scala
scala> divisBy2.count()
res0: Long = 500
```
```python
>>> divis_by_2.count()
500
```

There are three different types of actions:  
* actions to view data in the console
* to collect data to native objects in the respective language
* write to output data sources

This action:
* started a Spark job runs out filter transformation (a narrow transformation)
* then an aggregation (a wide transformation)
* then a collect - brings out result to a native object in the respective language

A **job** in Spark represents a set of transformations triggered by an individual action - jobs can be monitored from
the UI.

_Note that the number of columns when reading data is unknown because reading data is a transformation which is a lazy
operation_. 

Reading a CSV:

scala:
```scala
scala> val flightData2015 = (spark
     | .read
     | .option("inferSchema", "true")
     | .option("header", "true")
     | .csv("data/flight-data/csv/2015-summary.csv")
     | )
flightData2015: org.apache.spark.sql.DataFrame = [DEST_COUNTRY_NAME: string, ORIGIN_COUNTRY_NAME: string ... 1 more field]
scala> flightData2015.take(3)
res21: Array[org.apache.spark.sql.Row] = Array([United States,Romania,15], [United States,Croatia,1], [United States,Ireland,344])
```

python:
```python
>>> flight_date_2015 = (spark
... .read
... .option("inferSchema", "true")
... .option("header", "true")
... .csv("data/flight-data/csv/2015-summary.csv")
... )
```

and getting a plan for a transformation:
```
scala> flightData2015.sort("count").explain()
== Physical Plan ==
AdaptiveSparkPlan isFinalPlan=false
+- Sort [count#40 ASC NULLS FIRST], true, 0
   +- Exchange rangepartitioning(count#40 ASC NULLS FIRST, 200), ENSURE_REQUIREMENTS, [id=#52]
      +- FileScan csv [DEST_COUNTRY_NAME#38,ORIGIN_COUNTRY_NAME#39,count#40] Batched: false, DataFilters: [], Format: CSV, Location: InMemoryFileIndex(1 paths)[file:/home/keith/Documents/Spark-The-Definitive-Guide/data/flight-data..., PartitionFilters: [], PushedFilters: [], ReadSchema: struct<DEST_COUNTRY_NAME:string,ORIGIN_COUNTRY_NAME:string,count:int>
```

Plans have the end result at the top and work backwords from there until you get to the data source.

## DataFrames and SQL

Note that there's no performance difference between DataFrame code and SQL code.  
They both compile to the same underlying plan.  

With Spark SQL, you can register any DataFrame as a table of **view**, or temporary table, and query it using pure SQL.

To create a view, all you do is call the `.createOrReplaceTempView("<name>")` method.

Doing a group by in Spark actually gives you a new object called a **RelationalGroupedDataset**.


