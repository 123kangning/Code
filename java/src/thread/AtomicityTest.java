package thread;//: concurrency/AtomicityTest.java

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadFactory;

class CaughtException implements Thread.UncaughtExceptionHandler {
    public void uncaughtException(Thread t, Throwable e) {
        System.out.println("caught Exception " + e);
    }
}

class MyThreadFactory implements ThreadFactory {
    public Thread newThread(Runnable r) {
        Thread t = new Thread(r);
        t.setUncaughtExceptionHandler(new CaughtException());
        return t;
    }
}

public class AtomicityTest implements Runnable {
    private int i = 0;

    public static void main(String[] args) {
        Thread.setDefaultUncaughtExceptionHandler(new CaughtException());
        ExecutorService exec = Executors.newCachedThreadPool(new MyThreadFactory());
        AtomicityTest at = new AtomicityTest();
        exec.execute(at);

        while (true) {
            int val = at.getValue();
            if (val % 2 != 0) {
                System.out.println("val = " + val);
                System.exit(0);
            }
        }
        //exec.shutdown();
    }

    public synchronized int getValue() {
        return i;
    }

    private synchronized void evenIncrement() throws InterruptedException {
        i++;
        i++;
        Thread.sleep(100);
        System.out.println("i = " + i);
    }

    public void run() {
        while (true) {
            try {
                evenIncrement();
            } catch (InterruptedException e) {
                try {
                    throw e;
                } catch (InterruptedException ex) {
                    throw new RuntimeException(ex);
                }
            }
        }
    }
} /* Output: (Sample)
191583767
*///:~
