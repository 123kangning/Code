package test1;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.PrintWriter;
import java.lang.reflect.Array;
import java.util.*;

public class F001 {

    public static void main(String... args)throws IOException {
        LinkedList<Integer> list=new LinkedList<>();
        for(int i=0;i<10;i++){
            list.add(i);
        }
        System.out.println(list);
    }
}
