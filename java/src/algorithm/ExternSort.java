package algorithm;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.IntStream;

public class ExternSort {
    static int MAX;
    static List<Integer> node,Iterator;
    static List<Integer[]> b=new ArrayList<>();
    public static void main(String[] args) {

        b.add(new Integer[]{1,2,3});
        b.add(new Integer[]{3,4,5});
        b.add(new Integer[]{5,6,7});
        b.add(new Integer[]{7,8,9});
        b.add(new Integer[]{9,11,12});
        MAX=5;
        for(Integer[] e:b){
            System.out.println(e[0]+" "+e[1]+" "+e[2]);
        }
        //System.out.println(b.get(1)[0]);

    }
    public int get(int index){
        return node.get(index);
    }
    public void set(int index){
        if(Iterator.get(index)==b.get(index).length){
            int min=9999999;
            for(Integer[] e:b){
                if(e[Iterator.get(index)]<min){
                    min=Iterator.get(index);
                }
            }
            node.set(index, min);
        }
        node.set(index,b.get(index)[Iterator.get(index)]);
        Iterator.set(index,Iterator.get(index)+1);
    }
}
