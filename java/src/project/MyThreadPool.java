package project;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class MyThreadPool implements MyPool {
    private static MyBlockingQueue<Runnable> queue = new MyArrayBlockingQueue<>(1000);
    private final HashSet<Worker> workers = new HashSet<>();
    private final List<Thread> listThread = new ArrayList<>();
    private int poolSize = 10;//线程池大小
    private int coreSize = 0;//创建的最少核心线程总数
    private volatile int c = 0;//运行线程数
    private volatile boolean RUNNING = true;
    private long keepAliveTime, count = 1;
    private boolean allowKeepAliveTime = false;
    private TimeUnit timeUnit;
    private Lock lock = new ReentrantLock(), lockWork = new ReentrantLock();
    private Condition notFull = lock.newCondition(), notEmpty = lockWork.newCondition();

    public MyThreadPool(int coreSize, int poolSize, long keepAliveTime, TimeUnit unit) {
        this.coreSize = coreSize;
        this.poolSize = poolSize;
        this.keepAliveTime = keepAliveTime;
        allowKeepAliveTime = true;
        timeUnit = unit;
    }

    public void execute(Runnable r) {
        if (r == null) throw new NullPointerException();
        //System.out.println("have " + c + "threads ");
        //System.out.println("have " + queue.size() + " runnable");
        if (c < coreSize) {
            //System.out.println("c < coreSize");
            addThread(r, true);
        } else {
            if (c == 0) {
                addThread(r, true);
            }
            //System.out.print("try offer to queue ");
            else if (!queue.offer(r)) {
                System.out.println(" offer false");
                addThread(r, false);
            }
        }
    }

    public synchronized void addThread(Runnable r, boolean core) {
        c++;
        if (c > (core ? coreSize : poolSize)) {
            int i = 0;
            for (Thread e : listThread) if (e.isAlive()) i++;
            System.out.println("addThread return | coreSize = " + coreSize +
                    " c = " + c + " poolSize = " + poolSize + " queue.size() =  " + queue.size() + " thread.Alive() = " + i);
            return;
        }
        if (core) {
            queue.put(r);
        }
        //System.out.println("enter");
        Worker worker = new Worker(r, core);
        workers.add(worker);
        Thread t = new Thread(worker);
        listThread.add(t);
        //System.out.println("count = " + count++ + " run from " + (core ? " thread " : " queue "));
        t.start();
    }

    public MyBlockingQueue<Runnable> shutdown() {
        lock.lock();
        RUNNING = false;
        Thread t = null;
        try {
            for (Thread thread : listThread) {
                thread.interrupt();
            }
            for (Thread thread : listThread) {
                System.out.println(thread.isAlive());
//                System.out.println(queue.size());
            }
            return queue;
        } finally {
            lock.unlock();
        }

    }

    class Worker implements Runnable {

        public Worker(Runnable r, boolean core) {
            if (!core)
                r.run();
        }

        public void run() {
            //System.out.println("enter run");
            Runnable task = null;
            while (RUNNING && ((task = getTask()) != null)) {
                //System.out.println("running");
                task.run();
            }
//            if (task == null) {
//                System.out.println("I miss a runnable ");
//            }
        }

        public Runnable getTask() {
            if (c > coreSize && allowKeepAliveTime) {
                //System.out.println("poll");
                return queue.poll(keepAliveTime, timeUnit);
            }
            //System.out.println("take");
            return queue.take();
        }
    }
}
