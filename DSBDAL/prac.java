public class WordCount{

    public static class TokenizerMapper extends Mapper<Object, Text, Text, IntWritable>{
        private static final IntWritable one = new IntWritable(1);
        private Text word = new Text();

        public void map(Object key, Text value, Context context)throws IOException, InterruptedException{
            StringTokenizer itr = new StringTokenizer(value.toString());
            while(itr.hasMoreTokens()){
                word.set(itr.nextToken());
                context.write(word,one);
            } 
        }
    }

    public static class IntSumReducer extends Reducer<Text, IntWritable, Text, IntWritable>{
        private IntWritable result = new IntWritable();
        public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException{
            sum = 0;
            for(IntWritable val : values){
                sum += val.get();
            }
            result.set(sum);
            context.write(key,result);
        }
    }

    public static void main(String[] args) throws Exception{

    }
}