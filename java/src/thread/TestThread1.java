package thread;
/*
    haven't return value
 */

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class TestThread1 {
    public static void main(String args[]) {
        ExecutorService exec = Executors.newCachedThreadPool();
        System.out.println("main thread's priority is " + Thread.currentThread().getPriority());
        for (int i = 0; i < 1; i++) {


            exec.execute(new ThreadSleep(Thread.MAX_PRIORITY));
            exec.execute(new ThreadSleep(Thread.MIN_PRIORITY));

            //exec.shutdown();
        }

        exec.shutdown();
    }
}