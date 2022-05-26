package thread;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

class RunnableDemo1 implements Runnable {
    private static int taskCount = 0;
    private final int id = taskCount++;
    private int n = 10;

    RunnableDemo1() {
        System.out.println("thread birth");
    }

    RunnableDemo1(int n) {
        this.n = n;
        System.out.println("thread birth");
    }

    public void run() {
        for (int i = 0; i < 3; i++) {
            System.out.println("run the thread " + id);
            Thread.yield();
        }
    }
}

public class Thread1 {
    public static void main(String args[]) throws InterruptedException {
        ExecutorService exec = Executors.newCachedThreadPool();
        for (int i = 0; i < 10; i++) {
            exec.execute(new RunnableDemo1(i));
        }
        exec.shutdown();
//        for (int i = 0; i < 10; i++) {
//            System.out.println("main run");
//        }
//
//        for (int i = 0; i < 10; i++) {
//            System.out.println("main run");
//        }
//        Thread.yield();
//        Thread.sleep(10);
//        Thread.yield();
//        for (int i = 0; i < 5; i++)
//            System.out.println("main run");
    }
}