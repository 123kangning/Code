package NIO;

import java.io.IOException;
import java.net.Socket;

public class NIOClient {

    public static void main(String[] args) throws IOException,InterruptedException{
        Socket socket = new Socket("127.0.0.1", 8888);
        System.out.println();

    }
}

