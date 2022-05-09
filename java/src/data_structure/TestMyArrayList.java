package data_structure;


public class TestMyArrayList {
  public static void main(String[] args) {
    // Create a list
    MyList<Integer> list = new MyArrayList<>();
    for(int i=0;i<10;i++){
      list.add(i);
    }
    Integer[] num=new Integer[]{1,2,3,4,5};
    MyList<Integer> list1=new MyArrayList<>(num);
//    MyList<Integer> list1=new MyArrayList<>(num);
    //System.out.println(1);
//    for (Integer s: list){
//      System.out.print(s + " ");
//    }
//    System.out.println();
//    for (Integer s: list1){
//      System.out.print(s + " ");
//    }
    System.out.println(list);
    System.out.println(list1);


  }
}
