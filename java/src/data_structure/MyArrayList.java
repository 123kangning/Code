package data_structure;


import java.util.*;

public  class MyArrayList<E> implements MyList<E>,Iterable<E>{
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
    }
    public int size(){
        return size;
    }
    public void clear(){
        data=(E[])new Object[INITIAL_CAPACITY];
    }
    public void add(int index,E e){
        if(size>=data.length){
            E[] temp=(E[])new Object[2*size];
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
        if(index<0||index>=size){
            checkIndex(index);
        }
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
    public boolean equals(Object e){
        if(e==this){
            return true;
        }
        if(!(e instanceof MyList)){
            return false;
        }
        return true;
    }
    public boolean contains(Object e){
        return indexOf(e)>=0;
    }
    public boolean containsAll(Collection<?> c) {
        for(Object e:c){
            if(!this.contains(e)){
                return false;
            }
        }
        return true;
    }

    @Override
    public Iterator<E> iterator() {
        Iterator<E> iterator=new Iterator<E>() {
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
        return iterator;
    }

    public boolean retainAll(Collection<?> c){
        boolean sign=true;
        for(int i=0;;i++){
            if(i==size){
                return sign;
            }
            if(!c.contains(data[i])){
                remove(data[i]);
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
    public <T> T[] toArray(T[] array){
        if(array.length<=size){
            array=(T[])new Object[size];
        }
        for(int i=0;i<size;i++){
            array[i]=(T)data[i];
        }
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
}
