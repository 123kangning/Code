package thread;

import java.util.concurrent.Callable;

public class CallableDemo implements Callable {
    private int id;

    CallableDemo(int id) {
        this.id = id;
    }

    public String call() {
        return "run thread " + id;
    }
}
