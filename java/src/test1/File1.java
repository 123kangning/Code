package test1;

import java.io.*;
import java.util.Date;


public class File1 {
    public static void main(String[] args) throws IOException {
        try{
            ObjectOutputStream output=new ObjectOutputStream(new FileOutputStream("1.txt"));
            ObjectInputStream input=new ObjectInputStream(new FileInputStream("1.txt"));
            output.writeUTF("Wang");
            output.writeInt(90);
            output.writeObject(new Date());
            System.out.println(input.readUTF()+" "+input.readInt()+" "+input.readObject());
            input.close();
            output.close();
        }
        catch(ClassNotFoundException e){
            System.out.println(e.getMessage());
        }
    }
}
