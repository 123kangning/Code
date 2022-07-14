package NIO;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.nio.charset.Charset;

public class NIOClient {

    public static void main(String[] args) throws IOException,InterruptedException{
        SocketChannel sc=SocketChannel.open();
        sc.connect(new InetSocketAddress("localhost",6660));
        sc.write(Charset.defaultCharset().encode("heloolo\n"));
        ByteBuffer buffer=ByteBuffer.allocate(1000);

        sc.close();

    }
}
