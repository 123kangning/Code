package test1;

import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Scanner;

public class OpenUrl {
    public static void main(String... args){
        try{
            URL url=new URL("https://liveexample.pearsoncmg.com/checkpoint12/Chapter12.html");
            Scanner input=new Scanner(url.openStream());
            long count=0;
            while(input.hasNext()){
                String line=input.nextLine();
                System.out.println(line+"\n");
                count+=line.length();
            }
            System.out.println("url size is "+count);

        } catch(MalformedURLException  e1){
            System.out.println(e1.getMessage());
            e1.printStackTrace();
        } catch(IOException e){
            System.out.println(e.getMessage());
            e.printStackTrace();
        }
    }
}
