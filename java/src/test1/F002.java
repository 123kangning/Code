package test1;

 class A {
    public String s = "123";

    public void show(B obj){
        System.out.println("A and A");
    }

    public void show(D obj){
        System.out.println("A and D");
    }
}

class B extends A{
    public String s = "456";
//    public void show(B obj){
//        System.out.println("B and B");
//    }
    public void show(A obj){
        System.out.println("B and A");
    }
    public void show(E obj){
        System.out.println("B and E");
    }
}

class C extends B{
}

class D extends B{
}

class E{
}
public class F002 {
    public static void main(String[] args){
        A a1 = new A();
        A a2 = new B();

        B b = new B();
        C c = new C();
        D d = new D();
        E e = new E();

        a1.show(b);
        a1.show(c);
        a1.show(d);
        System.out.println(a1.s);

        a2.show(b);
        a2.show(c);
        a2.show(d);
        //a2.show(e);//这句编译不过
        System.out.println(a2.s);

        b.show(b);
        b.show(c);
        b.show(d);
        b.show(e);
        System.out.println(b.s);
    }
}