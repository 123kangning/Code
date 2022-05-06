package algorithm;

import java.util.ArrayList;
import java.util.Comparator;

public class Heap<E> {
    private ArrayList<E> list=new ArrayList<E>();
    private Comparator<? super E> c;
    public Heap(){
        this.c=(e1,e2)->((Comparable<E>)e1).compareTo(e2);
    }
    public Heap(Comparator<E> c){
        this.c=c;
    }
    public Heap(E[] objects){
        this();
        for(E e:objects){
            add(e);
        }
    }
    public void add(E newObject){
        list.add(newObject);
        int currentIndex=list.size()-1;
        while(currentIndex>0){
            int parentIndex=(currentIndex-1)/2;
            if(c.compare(list.get(currentIndex),list.get(parentIndex))>0){
                E temp=list.get(currentIndex);
                list.set(currentIndex,list.get(parentIndex));
                list.set(parentIndex,temp);
            }else
                break;
            currentIndex=parentIndex;
        }
    }
    public E remove(){
        if(list.size()==0)return null;
        E removeObject=list.get(0);
        list.set(0,list.get(list.size()-1));
        list.remove(list.size()-1);
        int currentIndex=0;
        while(currentIndex<list.size()){
            int leftIndex=currentIndex*2+1;
            int rightIndex=currentIndex*2+2;
            if(leftIndex>=list.size())break;//current is a heap
            int maxIndex=leftIndex;
            if(rightIndex<list.size()&&c.compare(list.get(maxIndex),list.get(rightIndex))<0)
                maxIndex=rightIndex;
            if(c.compare(list.get(currentIndex),list.get(maxIndex))<0){
                E temp=list.get(currentIndex);
                list.set(currentIndex,list.get(maxIndex));
                list.set(maxIndex,temp);
                currentIndex=maxIndex;
            }else
                break;
        }
        return removeObject;
    }
    public int size(){
        return list.size();
    }
    public boolean isEmpty(){
        return list.isEmpty();
    }
}
