package test1;

import java.io.IOException;
import java.util.HashSet;
import java.util.Set;

public class F001 {
    public static void main(String... args) throws IOException {
        Set<Integer> n = new HashSet<>();
        Set<Integer> n1 = new HashSet<>();
        n.add(1);
        n.add(2);
        n1.add(1);
        n1.add(2);
        System.out.println(n.equals(n1));
    }
}
