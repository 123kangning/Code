package thread;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

interface MyBlockingQueue<E> {
    void add(E e);

    E take();
}

class MyArrayBlockingQueue<E> {
    private int len = Integer.MAX_VALUE;
    private int start = 0, end = 0;
    private Object[] meal;
    private Lock lockAdd = new ReentrantLock(), lockTake = new ReentrantLock();
    private Condition notFull = lockAdd.newCondition(), notEmpty = lockTake.newCondition();


    public MyArrayBlockingQueue() {
        meal = new Object[len];
    }

    public MyArrayBlockingQueue(int n) {
        len = n + 1;
        meal = new Object[len];
    }

    public void add(E e) {
        try {
            lockAdd.lock();
            while ((end + 1) % len == start) {
                notFull.await();
            }
            lockAdd.unlock();
        } catch (InterruptedException e1) {
            System.out.println("add wait error" + e1.getMessage());
        }

        lockTake.lock();
        meal[end] = e;
        end = (end + 1) % len;
        notEmpty.signal();
        lockTake.unlock();
    }

    public E take() {
        try {
            lockTake.lock();
            while (start == end) {
                notEmpty.await();
            }
            lockTake.unlock();
        } catch (InterruptedException e1) {
            System.out.println("take wait error" + e1.getMessage());
        }
        lockAdd.lock();
        E ans = (E) meal[start];
        start = (start + 1) % len;
        notFull.signal();
        lockAdd.unlock();
        return ans;
    }
}
