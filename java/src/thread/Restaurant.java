package thread;//: concurrency/Restaurant.java
// The producer-consumer approach to task cooperation.

import project.MyArrayBlockingQueue;

import java.util.Random;
import java.util.concurrent.*;

class WaitPerson implements Runnable {
    private MyArrayBlockingQueue<Integer> block;

    public WaitPerson(MyArrayBlockingQueue<Integer> e) {
        block = e;
    }

    public void run() {
        try {
            while (!Thread.interrupted()) {
                Integer ans = block.take();
                System.out.println("eat " + ans);
            }
            TimeUnit.MILLISECONDS.sleep(1000);
        } catch (InterruptedException e) {
            System.out.println("Chef interrupted");
        }
    }
}

class Chef implements Runnable {
    private int count = 0;
    private MyArrayBlockingQueue<Integer> block;
    private Random rand = new Random();

    public Chef(MyArrayBlockingQueue<Integer> e) {
        block = e;
    }

    public void run() {
        try {
            while (!Thread.interrupted()) {
                int ans = rand.nextInt(100);
                block.put(ans);
                System.out.println("make " + ans);
                TimeUnit.MILLISECONDS.sleep(1);
            }
        } catch (InterruptedException e) {
            System.out.println("Chef interrupted");
        }

    }
}

public class Restaurant {

    public static void main(String[] args) throws InterruptedException {
        BlockingQueue<Integer> ans = new ArrayBlockingQueue<>(10);
        ExecutorService exec = Executors.newCachedThreadPool();
        MyArrayBlockingQueue<Integer> block = new MyArrayBlockingQueue<>(5);
        exec.execute(new Chef(block));
        exec.execute(new WaitPerson(block));
        TimeUnit.SECONDS.sleep(3);
        exec.shutdownNow();
    }
} /* Output:
Order up! Waitperson got Meal 1
Order up! Waitperson got Meal 2
Order up! Waitperson got Meal 3
Order up! Waitperson got Meal 4
Order up! Waitperson got Meal 5
Order up! Waitperson got Meal 6
Order up! Waitperson got Meal 7
Order up! Waitperson got Meal 8
Order up! Waitperson got Meal 9
Out of food, closing
WaitPerson interrupted
Order up! Chef interrupted
*///:~
