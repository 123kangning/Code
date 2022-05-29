package thread;

class RunnableDemo1 implements Runnable {
    private static int taskCount = 0;
    private final int id = taskCount++;
    private int n = 10;

    RunnableDemo1() {
        System.out.println("thread birth");
    }

    RunnableDemo1(int n) {
        this.n = n;
        System.out.println("thread birth");
    }

    public void run() {
        for (int i = 0; i < 3; i++) {
            System.out.println("run the thread " + id);
            Thread.yield();
        }
    }
}
