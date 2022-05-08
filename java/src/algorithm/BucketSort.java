package algorithm;

public class BucketSort {
    public static void main(String... args){
        int[] num=new int[]{2,5,3,7,4,6,1,4,5,8,2,3,9,0,9,3,100};
        sort(num);
        for(int e:num)System.out.print(e+" ");
    }
    public static void sort(int[] num){
        int n=num.length,max=0;
        for(int e:num){
            if(e>max){
                max=e;
            }
        }
        int[] bucket=new int[max+1];
        for(int i=0;i<n;i++){
            bucket[num[i]]++;
        }
        int k=0;
        for(int i=0;i<max+1;i++){
            while(bucket[i]>0){
                num[k++]=i;
                bucket[i]--;
            }
        }
        //for(int e:num)System.out.print(e+"  ");
    }
}
