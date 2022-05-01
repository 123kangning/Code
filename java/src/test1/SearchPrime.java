package test1;

import java.io.*;
import java.util.*;

public class SearchPrime {
    public static void  main(String... args)throws IOException {
        Scanner input=new Scanner(System.in);
        int number=2;
        int n=input.nextInt();
        ArrayList<Integer> list=new ArrayList<>();
        boolean prime;
        int squareRoot=1,count=0;
        while(number<n){
            prime=true;
            if(squareRoot*squareRoot<number)squareRoot++;
            for(int k=0;k<list.size()&&list.get(k)<=squareRoot;k++){
                if(number%list.get(k)==0){
                    prime=false;
                    break;
                }
            }
            if(prime){
                count++;
                list.add(number);
                if(count%10==0)
                    System.out.printf("%15d\n",number);
                else
                    System.out.printf("%15d",number);
            }
            number++;
        }
    }
}

