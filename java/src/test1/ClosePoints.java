package test1;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

class Point {
    private double x;
    private double y;

    Point() {
        x = 0.0;
        y = 0.0;
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public void setX(double x) {
        this.x = x;
    }

    public void setY(double y) {
        this.y = y;
    }
}

public class ClosePoints {
    public static void main(String... args) {
        Scanner input=new Scanner(System.in);
        int length=input.nextInt();
        Point[] points=new Point[length];
        for(int i=0;i<length;i++){
            points[i]=new Point();
            points[i].setX(input.nextDouble());
            points[i].setY(input.nextDouble());
        }
//        int length = 4;
//        Point[] points = new Point[length];
//        for (int i = 0; i < length; i++) {
//            points[i] = new Point();
//        }
//        points[0].setX(1.0);
//        points[0].setY(1.0);
//        points[1].setX(2.0);
//        points[1].setY(2.0);
//        points[2].setX(4.0);
//        points[2].setY(4.0);
//        points[3].setX(8.0);
//        points[3].setY(8.0);
        System.out.println("closest distance is "+search(points, length));
    }

    public static double distance(Point a, Point b) {
        return Math.sqrt(Math.pow(a.getX() - b.getX(), 2) + Math.pow(a.getY() - b.getY(), 2));
    }
    public static double search(Point[] points, int length) {
        if (length < 2) return Double.POSITIVE_INFINITY;
        if (length == 2) return distance(points[0], points[1]);
        ArrayList<Point> points1 = new ArrayList<>();
        ArrayList<Point> points2 = new ArrayList<>();
        ArrayList<Point> points3 = new ArrayList<>();
        double distance, d1, d2;

        Arrays.sort(points, new Comparator<Point>() {
            @Override
            public int compare(Point o1, Point o2) {
                return (int) (o1.getX() - o2.getX());
            }
        });
        double mid = points[length / 2].getX();
        for (int i = 0; i < length / 2; i++) {
            points1.add(points[i]);
        }
        for (int j = 0, i = length / 2; i < length; i++) {
            points2.add(points[j++]);
        }
        d1 = search(points1.toArray(new Point[points1.size()]), length / 2);
        d2 = search(points2.toArray(new Point[points2.size()]), length - length / 2);
        distance=Math.min(d1,d2);
        int i = 0, j = 0, k = 0, x = 0;
        for (i = 0, k = 0; i < length; i++) {
            if (Math.abs(points[i].getX() - mid) <= distance) {
                points3.add(points[i]);
            }
        }
        Arrays.sort(points3.toArray(new Point[points3.size()]), new Comparator<Point>() {
            @Override
            public int compare(Point o1, Point o2) {
                return (int) (o1.getY() - o2.getY());
            }
        });
        for (i = 0; i < k; i++) {
            if (points3.get(i).getY() > mid) continue;
            x = 0;
            for (j = i + 1; j <= i + 6 + 6; j++) {
                if (points[j].getX() <= mid) {
                    x++;//jump the left point
                    continue;
                }
                if (distance(points3.get(i), points3.get(j)) < distance) {
                    distance = distance(points3.get(i), points3.get(j));
                }
            }
        }
        return distance;
    }
}
