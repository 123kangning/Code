package project;

import java.util.concurrent.TimeUnit;

public class TestMyThreadPool {
    public static void main(String[] args) throws InterruptedException {
        //BlockingQueue<Runnable> ans = new ArrayBlockingQueue<>(10);
        MyBlockingQueue<Runnable> ans;
        //ThreadPoolExecutor exec = new ThreadPoolExecutor(0, 5, 1, TimeUnit.NANOSECONDS, ans);
        MyPool exec = new MyThreadPool(3, 10, 1, TimeUnit.NANOSECONDS);
        //ExecutorService exec = Executors.newCachedThreadPool();
        for (int i = 0; i < 1000; i++) {
            exec.execute(new Count(i));
        }
        TimeUnit.MILLISECONDS.sleep(1000);
        ans = exec.shutdown();
        //exec.shutdown();
//        System.out.println("---------------------------------------------------");
//        System.out.println("ans.isFull = " + ans.isFull());
//        for (int i = 0; i < 10; i++) {
//            System.out.println("shutdown ");
//            System.out.println(ans.take());
//        }
        Thread.currentThread().interrupt();
        System.out.println("----------------------------------------------------\nThread.interrupted()  " + Thread.interrupted());
        System.out.println("have " + ans.size() + " runnable");
//        while (ans.size() > 0) {
//            ans.take().run();
//        }
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
//        count++;
//        if (count % 100 == 0) System.out.println(count);
        System.out.println(i + " | " + Thread.currentThread().getName() + "~~~~~~~~~ " + count++);
    }
}