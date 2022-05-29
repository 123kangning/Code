package thread;

class TimeCostThread extends Thread {
    private int n;

    public TimeCostThread(Runnable r, int n) {
        super(r);
        this.n = n;
    }

    @Override
    public void run() {
        long start = System.currentTimeMillis();
        super.run();
        long end = System.currentTimeMillis();
        System.out.println("start time = " + start + " end time = " + end + "   run time  = " + (end - start) + "   super = " + n);
    }
}

public class TestThreadMethod {
    public static void main(String... args) {
        //List<Future<Object>> array = new ArrayList<>();
        int i;
        for (i = 1; i < 10; i++) {
            TimeCostThread ans = new TimeCostThread(new RunnableDemo(i), i);
            ans.start();
        }
//        i = 1;
//        for (Future<Object> e : array) {
//            System.out.println("When i = " + i++ + " fibonacci.sum = " + (Integer) e.get());
//        }
    }
}
