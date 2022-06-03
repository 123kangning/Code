package project;

public class TestMyThreadPool {
    public static void main(String[] args) throws InterruptedException {
        MyBlockingQueue<Runnable> ans = new MyArrayBlockingQueue<>(10);
        MyPool exec = new MyThreadPool(3);
        for (int i = 0; i < 10; i++) {
            exec.execute(new Count(i));
        }
        //TimeUnit.SECONDS.sleep(1);
        ans = exec.shutdown();
        System.out.println("---------------------------------------------------");
        System.out.println("ans.isFull = " + ans.isFull());
        for (int i = 0; i < 10; i++) {
            System.out.println("shutdown ");
            System.out.println(ans.take());
        }
    }
}

class Count implements Runnable {
    private int i;

    public Count(int i) {
        this.i = i;
    }

    public void run() {
        System.out.println(i + " | " + Thread.currentThread().getName());
    }
}