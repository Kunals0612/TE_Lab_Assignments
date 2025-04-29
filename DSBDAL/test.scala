import org.apache.spark.sql.SparkSession
import org.apache.spark.sql.function._

val spark = SparkSession
                .builder
                .appName("WC")
                .master("local[*]")
                .getOrCreate()


import spark.implicits._

val lines = spark.readStream
                .format("socket")
                .option("host","localhost")
                .option("port","9999")
                .load()


val words = lines.as[String].flatMap(._split(" "))

val wordcount = words.groupby("value").count()

val query = wordcount.writeStream
                .outputMode("complete")
                .format("console")
                .start()


query.awaitTermination()