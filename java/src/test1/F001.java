package test1;

import java.io.IOException;
import java.util.*;

public class F001 {
    public static void main(String... args) throws IOException {
        double[] nums={3,2,1};
        System.out.println(Arrays.stream(nums).reduce((e1,e2)-> Math.pow(e1,e2)).getAsDouble());
        System.out.println(Arrays.stream(nums).reduce((e1,e2)-> Math.pow(e1,e2)).isPresent());
        System.out.println(Arrays.stream(nums).reduce(2,(e1,e2)-> Math.pow(e1,e2)));
    }
}
