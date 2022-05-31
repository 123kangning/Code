package thread;

import java.util.Timer;
import java.util.TimerTask;

public class TestTimer {
    public static void main(String[] args) {
        for (int i = 0; i < 10000; i++) {
            new Timer().schedule(new TimerTask() {
                @Override
                public void run() {
                    System.out.println("aborted");
                }
            }, i * 5);
        }
    }
}
