
## DataFrames vs DataSets

* Both rows and cols.
* Both have type info.
* Both immutable and lazily evaluated.

While both of these are typed, those types function somewhat differently.  
DataFrame types are verified at runtime, while DataSets check type at compile time.

DataSets are only available to JVM based languages (Java, Scala) where types are specified cases classes and Java Beans.

## Structured types

Regardless of whether you write in scala or pyspark, operation are performed _purely in spark_. 

Spark uses an engine called **Catalyst** for all of its operations. When an operation is called is scala or in pyspark,
it's executed in **Catalyst** (or, rather on a Spark's internal Catalyst represetation of the data). 


