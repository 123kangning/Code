package test1;

import java.util.Scanner;

public class SearchPrime1 {
    public static void main(String... args){
        Scanner input=new Scanner(System.in);
        int n=input.nextInt();
        int count=0;
        boolean[] isPrime=new boolean[n+1];
        for(int i=0;i<isPrime.length;i++){
            isPrime[i]=true;
        }
        for(int k=2;k*k<n;k++){
            if(isPrime[k]){//k is prime
                for(int i=k;i*k<n;i++){
                    isPrime[k*i]=false;
                }
            }
        }
        for(int i=2;i<isPrime.length;i++){
            if(isPrime[i]){
                count++;
                if(count%10==0)
                    System.out.printf("%15d\n",i);
                else
                    System.out.printf("%15d",i);
            }
        }
    }
}
