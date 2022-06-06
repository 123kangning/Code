package project;

import java.util.concurrent.TimeUnit;

public class TestMyThreadPool {
    public static void main(String[] args) throws InterruptedException {
        MyBlockingQueue<Runnable> ans = new MyArrayBlockingQueue<>(10);
        MyPool exec = new MyThreadPool(1, 5, 100, TimeUnit.MILLISECONDS);
        //ExecutorService exec = Executors.newCachedThreadPool();
        for (int i = 0; i < 10; i++) {
            exec.execute(new Count(i));
        }
        TimeUnit.MILLISECONDS.sleep(1000);
        ans = exec.shutdown();
//        System.out.println("---------------------------------------------------");
//        System.out.println("ans.isFull = " + ans.isFull());
//        for (int i = 0; i < 10; i++) {
//            System.out.println("shutdown ");
//            System.out.println(ans.take());
//        }
        Thread.currentThread().interrupt();
        System.out.println("----------------------------------------------------\nThread.interrupted()  " + Thread.interrupted());
        System.out.println("have " + ans.size() + " runnable");
//        System.out.println(Thread.currentThread().getName());
    }
}

class Count implements Runnable {
    static int count = 1;
    private int i;

    public Count(int i) {
        this.i = i;
    }

    public void run() {
        System.out.println(i + " | " + Thread.currentThread().getName() + "~~~~~~~~~ " + count++);
    }
}