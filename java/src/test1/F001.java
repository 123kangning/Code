package test1;

import java.io.IOException;
import java.util.Random;
import java.util.stream.DoubleStream;

public class F001 {
    public static void main(String... args) throws IOException {
        Random rand = new Random();
        System.out.println(Double.MIN_VALUE);
        DoubleStream.of(rand.nextDouble()).forEach(e -> System.out.println(e));
    }
}
