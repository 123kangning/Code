package project;
/*
同时最多只能有4个筷子被拿起来，即筷子不能被拿完
 */

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicInteger;

public class Eater1 {
    public static void main(String[] args) throws InterruptedException {
        ExecutorService exec = Executors.newCachedThreadPool();
        for (int i = 0; i < 5; i++) {
            exec.execute(new philosopher(i, new Object()));
        }
        //TimeUnit.SECONDS.sleep(10);
        exec.shutdown();
    }
}

class philosopher implements Runnable {
    private static volatile Object[] lock = new Object[5];
    private static volatile boolean[] ware = {false, false, false, false, false};
    private static volatile AtomicInteger eater = new AtomicInteger(0);
    private int name;
    private boolean left = false;
    private boolean right = false;
    private boolean hungry = false, think = true;//先思考后吃饭


    public philosopher(int i, Object a) {
        name = i;
        lock[i] = a;
    }

    public void run() {
        while (true) {
            think();
            eat();
        }
    }

    public void eat() {
        try {
            synchronized (lock[name]) {
                while (left || ware[name] || think || !hungry || eater.get() >= 4) {
                    lock[name].wait();
                    System.out.println("wait");
                }
                eater.getAndIncrement();
                ware[name] = true;
                left = true;

                System.out.println(name + " have left  eater = " + eater.get());
                synchronized (lock[(name + 1) % 5]) {
                    while (right || ware[(name + 1) % 5] || think || !hungry) {
                        lock[(name + 1) % 5].wait();
                        System.out.println("wait");
                    }
                    ware[(name + 1) % 5] = true;
                    right = true;

                    hungry = false;
                    think = true;
                    left = false;
                    right = false;
                    ware[name] = false;
                    ware[(name + 1) % 5] = false;
                    eater.getAndDecrement();
                    System.out.println(name + " have eating !!!  eater = " + eater.get());
                    Thread.sleep(1);
                    lock[name].notifyAll();
                    lock[(name + 1) % 5].notifyAll();
                }
            }


        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }

    public void think() {
        try {
            Thread.sleep(1);
            think = false;
            hungry = true;
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}