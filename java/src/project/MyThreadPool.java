package project;

import java.util.*;

public class MyThreadPool implements MyPool {
    private static MyBlockingQueue<Runnable> queue = null;
    private final HashSet<Worker> workers = new HashSet<>();
    private final List<Thread> listThread = new ArrayList<>();
    private int poolSize = 0;//线程池大小
    private int coreSize = 0;//创建的线程总数
    private volatile boolean RUNNING = true;

    public MyThreadPool(int coreSize, int poolSize, long timeOut) {
        this.coreSize = coreSize;
        this.poolSize = poolSize;
        queue = new MyArrayBlockingQueue<>(poolSize);
        Timer timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                Thread.currentThread().interrupt();
            }
        }, timeOut);
    }

    public MyThreadPool(int poolSize) {
        this.poolSize = poolSize;
        queue = new MyArrayBlockingQueue<>(poolSize);
    }

    public void execute(Runnable r) {
        //System.out.println("execute");
        if (r == null) throw new NullPointerException();
        if (coreSize < poolSize) {
            addThread(r);
        } else {
            queue.put(r);
        }
    }

    public void addThread(Runnable r) {
        //System.out.println("addThread");
        coreSize++;
        Worker worker = new Worker(r);
        workers.add(worker);
        Thread t = new Thread(worker);
        listThread.add(t);
        t.start();
    }

    public MyBlockingQueue<Runnable> shutdown() {
        //System.out.println("shutdown");
        RUNNING = false;
        Thread t = null;
        for (Thread thread : listThread) {
            System.out.println("interrupt " + thread);
            thread.interrupt();
        }
        Thread.currentThread().interrupt();
        return queue;
    }

    class Worker implements Runnable {
        public Worker(Runnable r) {
            queue.put(r);
        }

        public void run() {
            while (RUNNING) {
                Runnable task = getTask();
                if (task == null) {
                    System.out.println("task is null ");
                    continue;
                }
                task.run();
                System.out.println("task.run");
            }
        }

        public Runnable getTask() {
            return queue.take();
        }
    }
}
