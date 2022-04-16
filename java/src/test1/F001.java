package test1;

public class F001 {
    public static void main(String[] args){
        String a="hello world";
        System.out.println(a);
        Parents parents=new Parents(88);
        parents.print();
        Son son=new Son(44);
        son.print();
        son.print1();

    }
}
class Parents{
    int age,high;
    public Parents(int age){
    this.age=age;
    this.high=100;
    }
    public void print(){
        System.out.println("I'm parents , my age is "+this.age);
    }
}
class Son extends Parents{
    int age,high;
    public Son(int age){
        super(age);
        this.high=50;
    }

    public void print(){
        System.out.println("I'm son , super.age = "+super.age);
        System.out.println("this.son = "+this.age);
        System.out.println("this.high = "+this.high);
    }
    public void print1(){
        super.print();
    }
}