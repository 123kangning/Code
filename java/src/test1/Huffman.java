package test1;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

import static kotlin.reflect.jvm.internal.impl.builtins.StandardNames.FqNames.list;

public class Huffman {
    public static void main(String... args)  throws IOException{
        Map<Character,Integer> map=account();
        for(Map.Entry<Character, Integer> entry:map.entrySet()) {
            System.out.println(entry.getKey()+"出现的次数"+entry.getValue());
        }


    }
    public static Map<Character,Integer> account() throws IOException{
        Scanner input=new Scanner(new FileInputStream("1.txt"));
        Map<Character,Integer> map=new HashMap<>();
        while(input.hasNext()){
            for(Character e: input.nextLine().toCharArray()){
                if(map.get(e)==null){
                    map.put(e,1);
                }else{
                    map.put(e,map.get(e)+1);
                }
            }
        }
        return map;
    }
}
