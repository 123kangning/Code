package project;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class TestMyArrayBlockingQueue {
    public static void main(String[] args) {
        MyArrayBlockingQueue<Integer> block = new MyArrayBlockingQueue<>(10000);
        ExecutorService exec = Executors.newCachedThreadPool();
        for (int i = 0; i < 10000; i++) {
            block.put(i);
        }
        for (int i = 0; i < 10; i++) {
            System.out.println(block.take() + "  size = " + block.size());
        }
        exec.shutdown();
    }
}

class Block1 implements Runnable {
    int i;
    private MyArrayBlockingQueue<Integer> block = null;

    public Block1(MyArrayBlockingQueue<Integer> b, int i) {
        block = b;
        this.i = i;
    }

    public void run() {
        if (i % 3 != 0) {
            System.out.println(block.take());
        } else {
            block.put(i);
        }
        System.out.println(" block.size = " + block.size());
    }
}