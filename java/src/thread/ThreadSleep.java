package thread;

public class ThreadSleep implements Runnable {
    private static int idCount = 0;
    private int testCount = 10;
    private int id = idCount++;
    private int priority;

    ThreadSleep() {
    }

    ThreadSleep(int priority) {
        this.priority = priority;
    }

    public void run() {
        Thread.currentThread().setPriority(this.priority);
        double a = 0;
        while (true) {
            for (int i = 0; i < 100000000; i++) {
                a += i / 1000;
                if (i % 1000 == 0) {
                    Thread.yield();
                }
            }
            System.out.println(" thread priority is " + Thread.currentThread().getPriority() + " testCount == " + testCount);
            if (--testCount == 0) {

                return;
            }
        }
    }
}
