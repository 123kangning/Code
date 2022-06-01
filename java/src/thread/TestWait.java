package thread;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

class Wait1 implements Runnable {
    Start start;

    public Wait1(Start i) {
        start = i;
    }

    public void run() {
        try {
            while (!Thread.interrupted()) {//need false
                //System.out.println("Wait1 start is " + start.get());
                start.waitFalse();
                TimeUnit.MILLISECONDS.sleep(100);
                start.ture();
                System.out.println("The Wait1 is " + start.get());
            }
        } catch (InterruptedException e) {
            System.out.println("Interrupted in wait2");
        }
    }
}

class Wait2 implements Runnable {
    Start start;

    public Wait2(Start i) {
        start = i;
    }

    public void run() {
        try {
            while (!Thread.interrupted()) {//need true
                //System.out.println("Wait2 start is " + start.get());
                start.waitTrue();
                TimeUnit.MILLISECONDS.sleep(100);
                start.ture();
                System.out.println("The Wait2 is " + start.get());
            }
        } catch (InterruptedException e) {
            System.out.println("Interrupted in wait2");
        }
    }
}

class Start {
    private volatile boolean start = true;

    public synchronized void waitTrue() throws InterruptedException {
        while (!start)
            wait();
    }

    public synchronized void waitFalse() throws InterruptedException {
        while (start)
            wait();
    }

    public synchronized void ture() {
        start = !start;
        notifyAll();
    }

    public synchronized Boolean get() {
        return start;
    }
}

public class TestWait {


    public static void main(String[] args) throws InterruptedException {
        Start start = new Start();
        ExecutorService exec = Executors.newCachedThreadPool();
        System.out.println("main start is " + start.get());
        exec.execute(new Wait1(start));
        exec.execute(new Wait2(start));

        TimeUnit.SECONDS.sleep(5);
        exec.shutdownNow();
    }


}
