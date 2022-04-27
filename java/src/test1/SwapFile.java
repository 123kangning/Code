package test1;

import java.io.*;
import java.util.*;

public class SwapFile {
    public static void main(String[] args) throws IOException {
        File file1=new File(args[0]);
        File file2=new File(args[1]);
        File temp=new File("temp");

        if(!file1.exists()){
            file1.createNewFile();
        }
        if(!file2.exists()){
            file2.createNewFile();
        }
        try{
            temp.createNewFile();
            toFile(file1,temp);
            toFile(file2,file1);
            toFile(temp,file2);
            temp.delete();

        }catch(IOException e){
            System.out.println("error");
        }

    }
    public static void toFile(File a, File b) throws IOException{
        if(!a.exists()){
            a.createNewFile();
        }
        if(!b.exists()){
            b.createNewFile();
        }
        try {
            Scanner input=new Scanner(a);
            PrintWriter output=new PrintWriter(b);
            while(input.hasNext()){
                output.print(input.next()+"\n");
            }
            output.close();
            input.close();
        }
        catch (IOException e){
            System.out.println("toFile error");
        }
    }
}
