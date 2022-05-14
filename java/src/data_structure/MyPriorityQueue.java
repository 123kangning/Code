package data_structure;

import java.util.Comparator;
import java.util.Iterator;

public class MyPriorityQueue<E> implements Iterable<E>{
    Heap<E> heap;
    public MyPriorityQueue(){
        heap=new Heap<E>();
    }
    public MyPriorityQueue(Comparator<E> c){
        heap=new Heap<E>(c);
    }
    public void add(E e){
        heap.add(e);
    }
    public E remove(){
        return heap.remove();
    }
    public int size(){
        return heap.size();
    }
    public E peek(){
        return heap.peek();
    }
    public Object[] toArray(){
        return heap.toArray(new Object[heap.size()]);
    }
    public <E> E[] toArray(E[] array) {
        return heap.toArray(array);
    }
    public Iterator<E> iterator(){
        return heap.iterator();
    }
}
