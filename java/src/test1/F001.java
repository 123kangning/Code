package test1;

import java.util.*;

public class F001 {
    public static void  main(String... args){
        Scanner input=new Scanner(System.in);
        LinkedList<Integer> list=new LinkedList<>();
        while(input.hasNext()){
            int a=input.nextInt();
            if(a==999)break;
            if(list.contains(a))continue;
            list.add(a);
        }
        System.out.println(list);

    }
}

