package thread;
/*
    have return value
 */

public class TestThread {
    public static void main(String args[]) throws Exception {
        Thread demo = new Thread(new RunnableDemo1());
        demo.setDaemon(true);
        demo.start();
        System.out.println(demo.isDaemon());
        Thread.sleep(100);
    }
}