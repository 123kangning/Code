package data_structure;


public class TestMyArrayList {
  public static void main(String[] args) {
    // Create a list
    MyList<Integer> list = new MyArrayList<>();
    MyList<Integer> list1=new MyArrayList<>();
    for(int i=0;i<10;i++){
      list.add(i);
      list1.add(i+5);
    }
    //System.out.println(1);
//    for (Integer s: list){
//      System.out.print(s + " ");
//    }
//    System.out.println();
//    for (Integer s: list1){
//      System.out.print(s + " ");
//    }
    //list.removeAll(list1);
    System.out.println(list.containsAll(list1));
//    System.out.println(list.equals(list1));
  }
}
