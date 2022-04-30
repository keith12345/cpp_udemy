
## Datasets - and why you might wanna use Scala

Only available in Scala (python and R are dynamically typed).  
**DataFrames** are a distributed collection of objects of type **Row** that can hold tabular data.  
The **Dataset** API gives users the ability to assign a Java/Scala class o the records within a DataFrame and manipulate
it as a collection of typed objects (similar to Java `ArrayList` or Scala `Seq`).

API available on Datasets are **type-safe**, basically meaning you won't get type errors half-way through processing
some column.

Types in Datasets are restricted to JavaBean pattern and case classes (in Scala). These are basically just interface
standards that add `getters`/`setters` and ensure the object is serializable (which I think basically just means that it
can be saved in byte or text form).

Example of a case class:
```scala
case class Flight(DEST_COUNTRY_NAME: String,
                  ORIGIN_COUNTRY_NAME: String,
                  count: BigInt)

val flightsDF = spark.read.parquet("data/flight-data/parquet/2010-summary.parquet/")
val flights = flightsDF.as[Flight]

flights
.filter(flight_row => flight_row.ORIGIN_COUNTRY_NAME != "Canada")
.map(flight_row => flight_row)
.take(5)
```

Note that when using `collect` or `take`, it will collect objects of the proper type of your dataset, not dataframe
rows.

## Structured Streaming

Available as of 2.2

You can take same operations that you'd normally run in batches and run them in streams.  
Can reduce latency and allow for incremental processing. 

Without streaming:
```scala
val staticDataFrame = (
    spark.read.format("csv")
    .option("header", "true")
    .option("inferSchema", "true")
    .load("data/retail-data/by-day/*.csv")
)

staticDataFrame.createOrReplaceTempView("retail_data")
val staticSchema = staticDataFrame.schema

import org.apache.spark.sql.functions.{window, column, desc, col}
(staticDataFrame
    .selectExpr(
        "CustomerId",
        "(UnitPrice * Quantity) as total_cost",
        "InvoiceDate")
    .groupBy(
        col("CustomerId"), window(col("InvoiceDate"), "1 day"))
    .sum("total_cost")
    .show(5))
```

As a stream:
```scala
spark.conf.set("spark.sql.shuffle.partitions", "5")

val streamingDataFrame = (spark.readStream
    .schema(staticSchema)
    .option("maxFilesPerTrigger", 1)
    .format("csv")
    .option("header", "true")
    .load("data/retail-data/by-day/*.csv")
)

streamingDataFrame.isStreaming

val purchaseByCustomerPerHour = (streamingDataFrame
    .selectExpr(
        "CustomerId",
        "(UnitPrice * Quantity) as total_cost",
        "InvoiceDate")
    .groupBy(
        $"CustomerId", window($"InvoiceDate", "1 day"))
    .sum("total_cost")
)
```

note that even though this is a streaming operation, it's also still a lazy operation.  
We need to call a streaming action to start execution.  

Output from the execution of a streaming operation will go to an in-memory table that will update after each
**trigger**.  
The **trigger** in this case is based on the reading of an individual file.

```scala
(purchaseByCustomerPerHour.writeStream
    .format("memory") // memory = store in-memory table
    .queryName("customer_purchases") // the name of the in-memory table
    .outputMode("complete") // complete = all the counts should be in the table
    .start())
```

Now you can see the stream update in real-time as it reads more data (not good for prod)
```scala
(purchaseByCustomerPerHour.writeStream
    .format("console")
    .queryName("customer_purchases_2")
    .outputMode("complete")
    .start())
```

Also, note that things are updating based on the event time, not on when the file was processed.  
This was previously an issue with spark streaming.

## MLib 

Just gonna copy and paste some stuff, not super relevant for me right now:

```scala
val staticDataFrame = (
    spark.read.format("csv")
    .option("header", "true")
    .option("inferSchema", "true")
    .load("data/retail-data/by-day/*.csv")
)

import org.apache.spark.sql.functions.date_format
val preppedDataFrame = (staticDataFrame
    .na.fill(0)
    .withColumn("day_of_week", date_format($"InvoiceDate", "EEEE"))
    .coalesce(5))

val trainDataFrame = preppedDataFrame.where("InvoiceDate < '2011-07-01'")
val testDataFrame = preppedDataFrame.where("InvoiceDate >= '2011-07-01'")

// They're split roughly equally
trainDataFrame.count()
testDataFrame.count()

// MLib needs number so gotta convert
// there are some nice little built-ins for that
import org.apache.spark.ml.feature.StringIndexer
val indexer = (new StringIndexer()
    .setInputCol("day_of_week")
    .setOutputCol("day_of_week_index"))

// but is one day really "greater" than another?
import org.apache.spark.ml.feature.OneHotEncoder
val encoder = (new OneHotEncoder()
    .setInputCol("day_of_week_index")
    .setOutputCol("day_of_week_encoded"))

// These features are returning sets of columns
// All MLib stuff takes vectors as inputs so we need to convert
import org.apache.spark.ml.feature.VectorAssembler
val vectorAssembler = (new VectorAssembler()
    .setInputCols(Array("UnitPrice", "Quantity", "day_of_week_encoded"))
    .setOutputCol("features"))

// We can actually take the three above steps and combine
// them into a "pipeline" for easy reproduce-ability
import org.apache.spark.ml.Pipeline
val transformationPipeline = new Pipeline().setStages(Array(indexer, encoder, vectorAssembler))

// Note that this step could also be included in the pipeline
val fittedPipeline = transformationPipeline.fit(trainDataFrame)

val transformedTraining = fittedPipeline.transform(trainDataFrame)

// We can also use this setting so that we store a copy of the transformed data
// (so that we don't need to run the "pipeline" again and can iterate much faster)
transformedTraining.cache()

// untrained models are referred to Algorithms
// Trained models are referred to as AlgorithmModels
// e.g. kMeans, kMeansModel, km, kmModel
import org.apache.spark.ml.clustering.KMeans
val kmeans = new KMeans().setK(20).setSeed(1L)

val kmModel = kmeans.fit(transformedTraining)

// Now we can see score our model
// note this is different after spark 3.0
// Here's the 3.* version
import org.apache.spark.ml.evaluation.ClusteringEvaluator
val evaluator = new ClusteringEvaluator()
val predictions = kmModel.transform(transformedTraining)
evaluator.evaluate(predictions)

// 2.* version
kmModel.computeCost(transformedTest)
```

### RDDs

Spark uses RDDs under the hood for pretty much everything but you rarely work directly with them.  
One instance in which you might is to parallelize raw data that you have stored in-memory on the driver machine.  
Here's a simple example of parallelizing something:
```scala
spark.sparkContext.parallelize(Seq(1, 2, 3)).toDF()
```
```python
# actually quite different syntax
from pyspark.sql import Row
spark.sparkContext.parallelize([Row(1), Row(2), Row(3)]).toDF()
```

Apparently you should never really use RDD unless you're on older spark or doing something like the above.
