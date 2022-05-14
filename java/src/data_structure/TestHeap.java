package data_structure;

import data_structure.Heap;

import java.util.Comparator;

public class TestHeap {
    public static void main(String... args){
        Heap<Integer> heap=new Heap<>();
        for(int i=0;i<20;i++){
            heap.add((int)(Math.random()*100));
        }
//        heapSort(num);
//        for(int e:num)System.out.print(e+" ");
//        System.out.println();
//        for(int i=0;i<num.length;i++){
//            System.out.print(heap.peek());
//        }
//        System.out.println();
        for(int e:heap)System.out.println(e);
        while(!heap.isEmpty()){
            System.out.print(heap.remove()+" ");
        }

    }
//    public static <E> void heapSort(E[] list){
//        heapSort(list,(e1,e2)->((Comparable<E>)e1).compareTo(e2));
//    }
//    public static <E> void heapSort(E[] list, Comparator<E> c){
//        Heap<E> heap=new Heap<E>(c);
//        for(E e:list){
//            heap.add(e);
//        }
//        for(int i= heap.size()-1;i>=0;i--){
//            list[i]=heap.remove();
//        }
//    }
}
