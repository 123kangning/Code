package test1;

import java.util.Arrays;
import java.util.stream.IntStream;

class Solution {
    public static void main(String... args) {
        int[][] a = new int[100][100];
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                a[i][j] = 1;
            }
        }
        int sum = Arrays.stream(a).map(e -> IntStream.of(e).sum()).reduce((e1, e2) -> e1 + e2).get();
        System.out.println("sum = " + sum);
    }
}