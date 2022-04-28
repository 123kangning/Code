package test1;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

public class F001 {
    public static void  main(String... args)throws IOException {
        File file=new File("hfm1.txt");
        PrintWriter output=new PrintWriter(file);
        System.out.println(file.getAbsolutePath());
        output.print("a");
        output.close();
    }
}

