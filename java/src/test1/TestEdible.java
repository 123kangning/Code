package test1;

public  class TestEdible {
    public static void main(String... args) {
        Object[] objects = {new Tiger(), new Chicken(), new Apple(),new Orange()};
        for (Object i : objects) {
            if (i instanceof Edible) {
                System.out.println(((Edible) i).howToEat());
            }
            if (i instanceof Animal) {
                System.out.println(((Animal) i).sound());
            }
        }
    }
}
      interface Edible{
          default String howToEat() {
              return "ha-ha-ha";
          }
      }
    abstract class Animal{
        private double weight;
        public double getWeight(){
            return weight;
        }
        public void setWeight(double weight){
            this.weight=weight;
        }
        public abstract String sound();
    }
    class Chicken extends Animal implements Edible{
        @Override
        public String howToEat(){
            return "Chicken: Fry it";
        }
        @Override
        public String sound(){
            return "ge-ge-ge";
        }
    }
    class Tiger extends Animal{
        @Override
        public String sound(){
            return "RR-OO-RR";
        }
    }
    class Apple implements Edible{
        @Override
        public String howToEat(){
            return "apple: make apple cider";
        }
    }
    class Orange implements Edible{
//        @Override
//        public String howToEat(){
//            return "Orange: make orange juice";
//        }
    }

