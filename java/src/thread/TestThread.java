package thread;
/*
    have return value
 */

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class TestThread {
    public static void main(String args[]) {
        ExecutorService exec = Executors.newCachedThreadPool();
        List<Future<Integer>> result = new ArrayList<>();
        for (int i = 0; i < 20; i++) {
            result.add(exec.submit(new RunnableDemo(i + 1)));

        }
        exec.shutdown();
        for (int i = 0; i < 20; i++) {
            System.out.println("thread isDone is " + result.get(i).isDone());
            try {
                System.out.println("sum = " + result.get(i).get());
            } catch (ExecutionException e) {
                e.printStackTrace();
                return;
            } catch (InterruptedException e) {
                e.printStackTrace();
                return;
            }
        }
//        Thread.yield();
//        Thread.sleep(10);
//        Thread.yield();
//        for (int i = 0; i < 5; i++)
//            System.out.println("main run");
    }
}