package IO;

import java.io.*;
import java.net.Socket;

public class NIOClient {

    public static void main(String[] args) throws IOException,InterruptedException{
        Socket socket = new Socket("127.0.0.1", 8881);
        while(true){
            InputStream out = socket.getInputStream();
            Reader read=new BufferedReader(new InputStreamReader(out));
            char[] a=new char[20];
            read.read(a);
            System.out.print(a);
//            read.close();
            Thread.sleep(1000);
        }
    }
}

