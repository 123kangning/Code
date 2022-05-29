package thread;

import java.util.Arrays;

class RunnableDemo implements Runnable {
    private static int taskCount = 0;
    private final int id = taskCount++;
    private int n = 10;

    RunnableDemo() {
        //System.out.println("thread birth");
    }

    RunnableDemo(int n) {
        this.n = n;
        //System.out.println("thread birth");
    }

    public void run() {
        int[] f = new int[n];
        if (n < 1) return;
        if (n < 2) {
            System.out.println("n= " + n + " [1]");
            return;
        }
        f[0] = f[1] = 1;
        for (int i = 2; i < n; i++)
            f[i] = f[i - 1] + f[i - 2];
        System.out.println("n= " + n + Arrays.toString(f));
    }

}
