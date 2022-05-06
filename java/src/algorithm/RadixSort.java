package algorithm;

public class RadixSort {
    public static void main(String... args){
        int[] num=new int[]{2,5,3,7,4,6,1,4,5,8,2,3,9,0,9,3,100,21,32,43,54,65,76,78,123,432,125,342,237};
        sort(num);
        for(int e:num)System.out.print(e+" ");
    }
    public static void sort(int[] num){
        int d=0;
        for(int e:num){
            int a=(int)Math.ceil(Math.log10(e));
            if(a>d)d=a;
        }
        for(int i=0;i<d;i++){
            bucketSort(num,i);
        }
    }
    public static void bucketSort(int[] num,int d){
        int max=0;
        for(int e:num){
            if(e>max){
                max=e;
            }
        }
        int[][] bucket=new int[10][100];
        int[] count=new int[10];
        for (int j : num) {
            int temp = (int) (j / Math.pow(10, d)) % 10;
            count[temp]++;
            bucket[temp][count[temp] - 1] = j;
        }
        int k=0;
        for(int i=0;i<10;i++){
            int[] clone={0};
            if(count[i]>0){
                clone=bucket[i].clone();
                for(int a1=0,a2=count[i]-1;a1<a2;a1++,a2--){
                    int temp=clone[a1];
                    clone[a1]=clone[a2];
                    clone[a2]=temp;
                }
            }
            while(count[i]>0){
                num[k++]=clone[count[i]-1];
                count[i]--;
            }
        }
//        for(int e:num)System.out.print(e+"  ");
//        System.out.println();
    }
}
