package project;

public interface MyBlockingQueue<E> {
    void put(E e);

    E take();

    boolean isFull();
}
