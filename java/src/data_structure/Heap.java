package data_structure;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.Iterator;

public class Heap<E> implements Iterable<E>,Cloneable{//每一条支路上有大小，但是兄弟间无大小
    private ArrayList<E> list=new ArrayList<>();
    private Comparator<? super E> c;
    public Heap(){
        this.c=(e1,e2)->((Comparable<E>)e1).compareTo(e2);
    }//default ascending order
    public Heap(Comparator<E> c){
        this.c=c;
    }
    public Heap(E[] objects){
        this();
        for(E e:objects){
            add(e);
        }
    }
    public void add(E[] objects){
        for(E e: objects){
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
        return list.size()==0;
    }
    public E peek(){
        if(list.isEmpty())return null;
        return list.get(0);
    }
    public Object[] toArray(){
        Object[] array=new Object[list.size()];
        for(int i=0;i<list.size();i++){
            array[i]=list.get(i);
        }
        return array;
    }
    public <E> E[] toArray(E[] array) {
        if(list.size()> array.length){
            array=(E[])new Object[list.size()];
        }
        for(int i=0;i<list.size();i++){
            array[i]= (E)list.get(i);
        }
//       System.out.println(array[0]);
        return array;
    }
    public String toString(){
        StringBuilder ans=new StringBuilder();
        ans.append("[");
        for(int i=0;;i++){
            ans.append(list.get(i));
            if(i==list.size()-1){
                return ans.append("]").toString();
            }else{
                ans.append(", ");
            }
        }
    }
    public Iterator<E> iterator(){
        Heap<E> clone;
        try{
            clone=(Heap<E>)this.clone();
        }catch(CloneNotSupportedException e){
            throw new RuntimeException(e);
        }

        return new Iterator<E>() {
            @Override
            public boolean hasNext() {
                return !clone.isEmpty();
            }
            @Override
            public E next() {
                return clone.remove();
            }
        };
    }
}
