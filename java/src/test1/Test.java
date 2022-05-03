package test1;

import java.math.BigInteger;
import java.util.Arrays;
import java.util.Scanner;

public class Test{
    public static void main(String... args){
        int[] num=new int[]{9,8,7,6,5,4,3,2,1,0};
        Arrays.sort(num,1,10);
        for(int e:num){
            System.out.println(e);
        }
    }
}
