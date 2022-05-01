package test1;

import java.security.PublicKey;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

class Point implements Comparable{
    private double x;
    private double y;
    public double getX(){
        return x;
    }
    public double getY(){
        return y;
    }
    public void setX(double x){
        this.x=x;
    }
    public void setY(double y){
        this.y=y;
    }
    public int compareTo(Object a){
        return (int)((this.getX()-((Point)a).getX()));
    }
}
public class ClosePoints {
    public static void main(String... args){

    }
    public static double distance(Point a,Point b){
        return Math.sqrt(Math.pow(a.getX()-b.getX(),2)+Math.pow(a.getX()-b.getX(),2));
    }
    public static double search(Point[] points,int length,Point a,Point b){
        if(length<2)return 999999999;
        if(length==2)return distance(points[0],points[1]);
        Point[] points1=new Point[length];
        Point[] points2=new Point[length];
        Point[] points3=new Point[length];
        Point a1=new Point(),a2=new Point(),b1=new Point(),b2=new Point();
        double distance,d1,d2;

        Arrays.sort(points, new Comparator<Point>() {
            @Override
            public int compare(Point o1, Point o2) {
                return (int)(o1.getX()-o2.getX());
            }
        });
        double mid=points[length/2].getX();
        for(int i=0;i<length/2;i++){
            points1[i]=points[i];
        }
        for(int j=0,i=length/2;i<length;i++){
            points2[j++]=points[i];
        }
        d1=search(points1,length/2,a1,b1);
        d2=search(points2,length-length/2,a2,b2);
        if(d1<d2){
            distance=d1;
            a=a1;
            b=b1;
        }else{
            distance=d2;
            a=a2;
            b=b2;
        }
        int i=0,j=0,k=0,x=0;
        for(i=0,k=0;i<length;i++){
            if(Math.abs(points[i].getX()-mid)<=distance){
                points3[k++]=points[i];
            }
        }
        Arrays.sort(points3, new Comparator<Point>(){
            @Override
            public int compare(Point o1,Point o2){
                return (int)(o1.getY()-o2.getY());
            }
        });
        for(i=0;i<k;i++){
            if(points3[i].getY()>mid)continue;
            x=0;
            for(j=i+1;j<=i+6+6;j++){
                if(points[j].getX()<=mid){
                    x++;//jump the left point
                    continue;
                }
                if(distance(points3[i],points3[j])<distance){
                    distance=distance(points3[i],points3[j]);
                    a=points3[i];
                    b=points3[j];
                }
            }
        }
        return distance;
    }
}
