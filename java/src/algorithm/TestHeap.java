package algorithm;

import algorithm.Heap;

import java.util.Comparator;

public class TestHeap {
    public static void main(String... args){
        Integer[] num=new Integer[]{1,5,2,3,4,0,12,43,23,13};
        heapSort(num);
        for(int e:num)System.out.print(e+" ");
    }
    public static <E> void heapSort(E[] list){
        heapSort(list,(e1,e2)->((Comparable<E>)e1).compareTo(e2));
    }
    public static <E> void heapSort(E[] list, Comparator<E> c){
        Heap<E> heap=new Heap<E>(c);
        for(E e:list){
            heap.add(e);
        }
        for(int i= heap.size()-1;i>=0;i--){
            list[i]=heap.remove();
        }
    }
}
