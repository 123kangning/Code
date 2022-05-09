package data_structure;

import java.util.Collection;
import java.util.Iterator;

class Node<E>{
    E element;
    Node<E> next;
    Node<E> last;
    public Node(){
        element=null;
    }
    public Node(E e){
        element=e;
    }
}
public  class MyLinkedList<E> implements MyList<E>{
    Node<E> head=null;
    Node<E> tail=null;
    int size;
    public MyLinkedList(){
        size=0;
    }
    public void addFirst(E e){
        Node<E> newNode=new Node<>(e);
        if(head==null||tail==null)head=tail=newNode;
        else{
            newNode.next=head;
            head.last=newNode;
            head=newNode;
            head.last=null;
        }
        size++;
    }
    public void addLast(E e){
        Node<E> newNode=new Node<>(e);
        if(tail==null){//LinkedList is null
            head=tail=newNode;
        }
        else{
            tail.next=newNode;
            newNode.last=tail;
            tail=newNode;
            tail.next=null;
        }
        size++;
    }
    public void add(int index,E e){
        if(index==0)
            addFirst(e);
        else if(index>=size)
            addLast(e);
        else{
            Node<E> current=head;
            for(int i=0;i<index;i++){
                current=current.next;
            }
            Node<E> temp=current.next;
            current.next=new Node<>(e);
            current.next.next=temp;
            size++;
        }
    }

    @Override
    public E get(int index) {
        if(index==0)return head.element;
        if(index==size-1)return tail.element;
        if(index<0||index>=size)return null;
        Node<E> current=head;
        for(int i=0;i<index;i++){
            current=current.next;
        }
        return current.element;
    }

    public E removeFirst(){
        if(head==null)return null;
        Node<E> ans=head;
        head=head.next;
        head.last=null;
        size--;
        return ans.element;
    }
    public E removeLast(){
        if(tail==null)return null;
        Node<E> ans=tail;
        tail=tail.last;
        tail.next=null;
        size--;
        return ans.element;
    }
    public E remove(int index){
        if(index<0||index>=size)return null;
        if(index==0)return removeFirst();
        if(index==size-1)return removeLast();
        Node<E> current=head;
        for(int i=0;i<index-1;i++){
            current=current.next;
        }
        Node<E> ans=current.next;
        current.next=current.next.next;
        current.next.last=current;
        size--;
        return ans.element;
    }

    @Override
    public E set(int index, E e) {
        Node<E> current=head;
        for(int i=0;i<index;i++){
            current=current.next;
        }
        E ans=current.element;
        current.element=e;
        return ans;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean contains(Object e) {
        return indexOf(e)>=0;
    }

    @Override
    public Iterator<E> iterator() {
        Iterator<E> iterator=new Iterator<E>() {
            int current = 0;
            Node<E> currentNode = head;

            public boolean hasNext() {
                return current < size;
            }

            public E next() {
                Node<E> ans=currentNode;
                current++;
                currentNode=currentNode.next;
                return ans.element;
            }
        };
        return iterator;
    }

    @Override
    public void clear() {
        head=null;
        tail=null;
        size=0;
    }

    public int indexOf(Object e){
        Node<E> p1=head;
        int index=0;
        while(p1!=null){
            if(p1.equals(e)){
                return index;
            }
            index++;
            p1=p1.next;
        }
        return -1;
    }

    @Override
    public int lastIndexOf(Object e) {
        Node<E> p1=tail;
        int index=size-1;
        while(p1!=null){
            if(p1.equals(e)){
                return index;
            }
            index--;
            p1=p1.last;
        }
        return -1;
    }
    public String toString(){
        StringBuilder s=new StringBuilder("[ ");
        Node<E> p1=head;
        while(p1!=null){
            s.append(p1.element);
            p1=p1.next;
            if(p1!=null)
                s.append(", ");
        }
        s.append("]");
        return String.valueOf(s);
    }

    }

