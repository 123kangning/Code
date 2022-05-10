package data_structure;

public class TestMyLinkedList {
  /** Main method */
  public static void main(String[] args) {
    // Create a list for strings
    MyLinkedList<Integer> list = new MyLinkedList<Integer>();
    MyLinkedList<Integer> list1 = new MyLinkedList<Integer>();

    for(int i=0;i<10;i++){
      list.add(i);
      list1.add((i+5)%10);
    }
//    list.addAll(list1);
    System.out.println(list.containsAll(list1));
    System.out.println(list);
    System.out.println(list1);

  }
}