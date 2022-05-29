package thread;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

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