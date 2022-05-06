package test1;

import java.io.*;

public class CreateLargeFile {
  public static void main(String[] args) throws Exception {
    FileOutputStream output = new FileOutputStream("largedata.dat");

    for (int i = 0; i < 10; i++)
      output.write(1);

    output.close();

    // Display first 100 numbers
    FileInputStream input = new FileInputStream("largedata.dat");
    for (int i = 0; i < 10; i++)
      System.out.print(input.read() + " ");

    input.close();
  }
}
