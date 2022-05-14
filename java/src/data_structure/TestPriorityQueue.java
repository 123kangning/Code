package data_structure;

public class TestPriorityQueue {
  public static void main(String[] args) {
    Patient patient1 = new Patient("John", 2);
    Patient patient2 = new Patient("Jim", 1);
    Patient patient3 = new Patient("Tim", 5);
    Patient patient4 = new Patient("Cindy", 7);
    
    MyPriorityQueue<Patient> priorityQueue 
      = new MyPriorityQueue<>();
    priorityQueue.add(patient1);
    priorityQueue.add(patient2);
    priorityQueue.add(patient3);
    priorityQueue.add(patient4);

    for(Patient e:priorityQueue)System.out.println(e+"  "+e.priority);
    while (priorityQueue.size() > 0)
      System.out.print(priorityQueue.remove() + " ");
  }
  
  static class Patient implements Comparable<Patient> {
    private String name;
    private int priority;
    
    public Patient(String name, int priority) {
      this.name = name;
      this.priority = priority;
    }
    
    @Override
    public String toString() {
      return name + "(priority:" + priority + ")";
    }
    
    public int compareTo(Patient o) {
      return this.priority - o.priority;
    }
  }
}
