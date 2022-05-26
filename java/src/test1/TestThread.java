package test1;

import java.util.Arrays;

class RunnableDemo implements Runnable {
    private static int taskCount = 0;
    private final int id = taskCount++;
    private int n = 10;

    RunnableDemo() {
        System.out.println("thread birth");
    }

    RunnableDemo(int n) {
        this.n = n;
        System.out.println("thread birth");
    }

    //    public void run() {
//        for (int i = 0; i < 3; i++) {
//            System.out.println("run the thread " + id);
//            Thread.yield();
//        }
//    }
    public void run() {
        int[] f = new int[n];
        if (n < 1) return;
        if (n < 2) {
            System.out.println("[1]");
            return;
        }
        f[0] = f[1] = 1;
        for (int i = 2; i < n; i++)
            f[i] = f[i - 1] + f[i - 2];
        System.out.println(Arrays.toString(f));
    }
}

public class TestThread {
    public static void main(String args[]) throws InterruptedException {
        for (int i = 0; i < 10; i++) {
            Thread r1 = new Thread(new RunnableDemo(i));
            r1.start();
        }


//        Thread.yield();
//        Thread.sleep(10);
//        Thread.yield();
//        for (int i = 0; i < 5; i++)
//            System.out.println("main run");
    }
}