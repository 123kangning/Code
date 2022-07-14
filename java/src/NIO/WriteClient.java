package NIO;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.nio.charset.Charset;

public class WriteClient {
    public static void main(String[] args) throws IOException {
        SocketChannel sc=SocketChannel.open();
        sc.connect(new InetSocketAddress("localhost",6661));

        int count=0;
        while(true){
            ByteBuffer buffer=ByteBuffer.allocate(1024);
            count+=sc.write(Charset.defaultCharset().encode("hello"));
            sc.read(buffer);
            buffer.flip();
            System.out.println(Charset.defaultCharset().decode(buffer));
            buffer.clear();
        }
    }
}
