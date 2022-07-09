package IO;

import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;

public class NIOClient {

    public static void main(String[] args) throws IOException {
        Socket socket = new Socket("127.0.0.1", 8888);
        InputStream out = socket.getInputStream();
//        String s = "hello world";
//        out.write(s.getBytes());
        System.out.println(out.read());
        out.close();
    }
}

