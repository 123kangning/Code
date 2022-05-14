package data_structure;

public class TestHash {
    public static void main(String... args){
        MyHash hash=new MyHash();
        String a="ABCDEFGHIJK";
        int hashCode=hash.hashCodeForString(a);
        System.out.println("hashCode = "+hashCode);
    }
}
