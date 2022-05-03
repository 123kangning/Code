package algorithm;

public class HeapSort {
    public static void main(String... args){
        int[] num=new int[]{2,1,4,3,8,5,7,6,9,34,65,12};
        heapSort(num);
        for(int e:num)System.out.print(e+" ");
    }
    public static void heapAdjust(int[] num,int head,int tail){
        int i,temp=num[head];
        for(i=2*head+1;i<=tail;i=2*i+1){
            if(i<tail&&num[i]<num[i+1]){
                i++;
            }
            if(num[i]<=temp)
                break;
            num[head]=num[i];
            head=i;
        }
        num[head]=temp;
    }
    public static void swap(int[] num,int o1,int o2){
        int temp=num[o1];
        num[o1]=num[o2];
        num[o2]=temp;
    }
    public static void heapSort(int[] num){
        int i,len=num.length;
        for(i=len/2-1;i>=0;i--){
            heapAdjust(num,i,len-1);
        }
        for(i=len-1;i>0;i--){
            swap(num,0,i);
            heapAdjust(num,0,i-1);
        }
    }
}
