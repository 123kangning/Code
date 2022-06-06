package project;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class MyThreadPool implements MyPool {
    private static MyBlockingQueue<Runnable> queue = new MyArrayBlockingQueue<>(10);
    private final HashSet<Worker> workers = new HashSet<>();
    private final List<Thread> listThread = new ArrayList<>();
    private int poolSize = 10;//线程池大小
    private int coreSize = 0;//创建的最少核心线程总数
    private volatile int c = 0;//运行线程数
    private volatile boolean RUNNING = true;
    private long timeOut;
    private Lock lock = new ReentrantLock(), lockWork = new ReentrantLock();
    private Condition notFull = lock.newCondition(), notEmpty = lockWork.newCondition();

    public MyThreadPool(int coreSize, int poolSize, long keepAliveTime, TimeUnit unit) {
        this.coreSize = coreSize;
        this.poolSize = poolSize;
        timeOut = unit.toMillis(keepAliveTime);
    }

    public MyThreadPool(int poolSize) {
        this.poolSize = poolSize;
    }

    public void execute(Runnable r) {
        if (r == null) throw new NullPointerException();
        if (c < coreSize) {
            addThread(r, true);
        } else {
            if (!queue.offer(r)) {
                addThread(r, false);
            }

        }
    }

    public synchronized void addThread(Runnable r, boolean core) {
        c++;
        if (c > (core ? coreSize : poolSize)) {
            System.out.println("addThread return | coreSize = " + coreSize + " c = " + c + " poolSize = " + poolSize);
            return;
        }
        Worker worker = new Worker(r);
        workers.add(worker);
        Thread t = new Thread(worker);
        listThread.add(t);
        t.start();
    }

    public MyBlockingQueue<Runnable> shutdown() {
        RUNNING = false;
        Thread t = null;
        for (Thread thread : listThread) {
            thread.interrupt();
        }
        return queue;
    }

    class Worker implements Runnable {

        public Worker(Runnable r) {
            queue.put(r);
        }

        public void run() {
            Runnable task = null;
            while (RUNNING && ((task = getTask()) != null)) {
                task.run();
            }
        }

        public Runnable getTask() {
            return queue.take();
        }
    }
}
