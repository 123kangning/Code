package project;
/*
每次只能拿自己左边和右边中较小编号的筷子，如果编号较小的筷子已经被拿走了，就先去思考，暂时不吃饭
 */

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Eater2 {
    public static void main(String[] args) throws InterruptedException {
        ExecutorService exec = Executors.newCachedThreadPool();
        for (int i = 0; i < 5; i++) {
            exec.execute(new philosopher1(i, new Object()));
        }
        //TimeUnit.SECONDS.sleep(10);
        exec.shutdown();
    }
}

class philosopher1 implements Runnable {
    private static volatile Object[] lock = new Object[5];
    private static volatile boolean[] ware = {false, false, false, false, false};


    private int name;
    private boolean left = false;
    private boolean right = false;
    private boolean hungry = false, think = true;//先思考后吃饭


    public philosopher1(int i, Object a) {
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
            int name1 = name < (name + 1) % 5 ? name : (name + 1) % 5;
            int name2 = name > (name + 1) % 5 ? name : (name + 1) % 5;
            if (ware[name1]) return;
            synchronized (lock[name < (name + 1) % 5 ? name : (name + 1) % 5]) {

                //System.out.println(" name1 = " + name1 + " name2 = " + name2);
                while ((name == name1) ? left : right || ware[name1] || think || !hungry) {
                    lock[name1].wait();
                    System.out.println("wait");
                }

                ware[name1] = true;
                if (name == name1)
                    left = true;
                else
                    right = true;

                System.out.println(name1 + " have left ");
                synchronized (lock[name2]) {
                    while ((name == name1) ? right : left || ware[name2] || think || !hungry) {
                        lock[name2].wait();
                        System.out.println("wait");
                    }
                    ware[name2] = true;
                    if (name == name1)
                        right = true;
                    else
                        left = true;

                    hungry = false;
                    think = true;
                    left = false;
                    right = false;
                    ware[name1] = false;
                    ware[name2] = false;

                    System.out.println(name2 + " have eating !!! ");
                    Thread.sleep(1);

                    lock[name2].notifyAll();
                    lock[name1].notifyAll();
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