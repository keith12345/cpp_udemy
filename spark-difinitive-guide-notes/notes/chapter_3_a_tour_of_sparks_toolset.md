
## Datasets

Only available in Scala (python and R are dynamically typed).  
**DataFrames** are a distributed collection of objects of type **Row** that can hold tabular data.  
The **Dataset** API gives users the ability to assign a Java/Scala class o the records within a DataFrame and manipulate
it as a collection of typed objects (similar to Java `ArrayList` or Scala `Seq`).

API available on Datasets are **type-safe**, basically meaning you won't get type errors half-way through processing
some column.

Types in Datasets are restricted to JavaBean pattern and cases classes (in Scala). These are basically just interface
standards that add `getters`/`setters` and ensure the object is serializable (which I think basically just means that it
can be saved in byte or text form).


