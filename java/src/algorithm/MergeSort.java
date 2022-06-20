package algorithm;

import java.util.Random;

public class MergeSort {
    public static void main(String[] args) {
        Integer[] num=new Integer[100];
        Random rand=new Random(1000);
        for(int i=0;i<100;i++){
            num[i]=rand.nextInt(100);
        }
        for(int i=0;i<100;i++){
            System.out.print(num[i]+" ");
            if(i%10==0)
                System.out.println();
        }
        System.out.println("\n-----------------------------------------------\n");
        mergesort(num,0,99);
        for(int i=0;i<100;i++){
            System.out.print(num[i]+" ");
            if(i%10==0)
            System.out.println();
        }
    }
    public static void mergesort(Integer[] a,int start,int end){
        if(start>=end)return;
        int mid=mid=(start+end)>>1;
        mergesort(a,start,mid);
        mergesort(a,mid+1,end);
        merge(a,start,mid,end);
    }
    public static void merge(Integer[] a,int start,int mid,int end){
        int len=a.length,i=start,j=mid+1;
        //System.out.println("start= "+start+" end= "+end+" mid= "+mid);
        Integer[] aux=new Integer[len];
        for(int k=start;k<=end;k++){
            aux[k]=a[k];
        }
        for(int k=start;k<=end;k++){
            //System.out.print("aux[i]="+aux[i]+" aux[j]= "+aux[j]);
            if(i>mid){
                a[k]=aux[j++];
            }else if(j>end){
                a[k]=aux[i++];
            }else if(aux[i]<aux[j]){
                a[k]=aux[i++];
            }else{
                a[k]=aux[j++];
            }
            //System.out.println(" a[k]="+a[k]);
        }
    }
}
