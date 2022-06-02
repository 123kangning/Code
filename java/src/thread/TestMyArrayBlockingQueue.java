package thread;

public class TestMyArrayBlockingQueue {
    public static void main(String[] args) {
        MyArrayBlockingQueue<Integer> block = new MyArrayBlockingQueue<>(10);
        for (int i = 0; i < 10; i++) {
            block.add(i);
            System.out.println("add " + i);
        }
        for (int i = 0; i < 10; i++) {
            System.out.println(block.take());
        }
        
    }
}
