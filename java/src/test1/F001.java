package test1;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.PrintWriter;
import java.lang.reflect.Array;
import java.util.*;

public class F001 {

    public static void main(String... args)throws IOException {
        String a="ABCDEFGHIJK";
        int hashCode=hashCodeForString(a);
        System.out.println("hashCode = "+hashCode);
    }
    public static int hashCodeForString(String a){
        int b=31;
        int hashCode=a.charAt(0);
        for(Character e:a.substring(1).toCharArray()){
            hashCode*=b;
            hashCode+=e;

        }
        return hashCode;
    }

}
