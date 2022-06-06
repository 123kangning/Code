package project;

public interface MyBlockingQueue<E> {
    void put(E e);

    E take();

    boolean offer(E e);

    int size();

    boolean isFull();
}
