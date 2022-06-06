package project;

import java.util.concurrent.TimeUnit;

public interface MyBlockingQueue<E> {
    void put(E e);

    E take();

    boolean offer(E e);

    int size();

    E poll(long time, TimeUnit unit);

    boolean isEmpty();

    boolean isFull();
}
