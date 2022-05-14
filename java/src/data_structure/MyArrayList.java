package data_structure;


import kotlin.reflect.jvm.internal.impl.load.kotlin.JvmType;

import java.util.*;

public  class MyArrayList<E> implements MyList<E> {
    public static final int INITIAL_CAPACITY =16;
    public E[] data=(E[])new Object[INITIAL_CAPACITY];
    public int size=0;//forbid set size to static
    public MyArrayList(){
        this.size=0;
    }
    public MyArrayList(E[] objects){
        for(int i=0;i<objects.length;i++){
            add(objects[i]);
        }
//        data=objects;
//        size= objects.length;
    }
    public int size(){
        return size;
    }
    public void clear(){
        data=(E[])new Object[INITIAL_CAPACITY];
    }
    public void add(int index,E e){
        if(index<0||index>size)checkIndex(index);
        if(size>=data.length){
            E[] temp=(E[])new Object[2*size+1];
            for(int i=0;i<size;i++){
                temp[i]=data[i];
            }
            this.data=temp;
        }
        for(int i=size-1;i>=index;i--){
            data[i+1]=data[i];
        }
        data[index]=e;
        size++;
    }
    public void checkIndex(int index){
        throw new ArrayIndexOutOfBoundsException("Index: "+index+" size:"+size);
    }
    public E get(int index){
        if(index<0||index>=size)checkIndex(index);
        return data[index];
    }
    public int indexOf(Object e){
        for(int i=0;i<size;i++){
            if(data[i].equals((E)e)){
                return i;
            }
        }
        return -1;
    }
    public int lastIndexOf(Object e){
        for(int i=size-1;i>=0;i--){
            if(data[i].equals((E)e)){
                return i;
            }
        }
        return -1;
    }
    public E remove(int index){
        E result=data[index];
        for(int i=index+1;i<size;i++){
            data[i-1]=data[i];
        }
        size--;
        return result;
    }
    public E set(int index,E e){
        if(index>=size)size++;
        E old=data[index];
        data[index]=e;
        return old;
    }
    public boolean contains(Object e){
        return indexOf(e)>=0;
    }
    @Override
    public Iterator<E> iterator() {
        return new Iterator<E>() {
            int current=0;
            @Override
            public boolean hasNext() {
                return current<size;
            }

            @Override
            public E next() {
                return data[current++];
            }
        };
    }
    public boolean retainAll(Collection<?> c){
        boolean sign=true;
        for(int i=0;;i++){
            if(i==size){
                return sign;
            }
            if(!c.contains(data[i])){
                remove(data[i]);
                i--;
                sign=false;
            }
        }
    }
    public Object[] toArray(){
        Object[] array=new Object[size];
        for(int i=0;i<size;i++){
            array[i]=data[i];
        }
        return array;
    }
    public <T> T[] toArray(T[] array) {
        if(size> array.length){
            array=(T[])new Object[size];
        }
        for(int i=0;i<size;i++){
            array[i]= (T) data[i];
        }
//        System.out.println(array[0]);
        return array;
    }
    public String toString(){
        StringBuilder ans=new StringBuilder();
        ans.append("[");
        for(int i=0;;i++){
            ans.append(data[i]);
            if(i==size-1){
                return ans.append("]").toString();
            }else{
                ans.append(", ");
            }
        }
    }
    public void trimToSize(){
        E[] num=(E[])new Object[size];
         for(int i=0;i<size;i++){
            num[i]=data[i];
         }
         data=num;
    }
//    public void sort(){
//        Arrays.sort(data,new Comparator<E>(){
//            public int compare(E o1,E o2){
//                return
//            }
//        });
//    }
}
