package test1;

import java.io.IOException;
import java.util.concurrent.atomic.AtomicInteger;

public class F001 {
    public static void main(String... args) throws IOException {
        AtomicInteger a = new AtomicInteger(0);
        a.getAndAdd(10);
        a.getAndDecrement();
        a.getAndIncrement();
        System.out.println(a.get());
    }
}
