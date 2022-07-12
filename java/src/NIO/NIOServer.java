package NIO;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Set;
import java.util.logging.Logger;

public class NIOServer {
    public static final Logger log=Logger.getLogger(EchoServer.class.toString());
    public static void main(String[] args) throws IOException {

        Selector selector = Selector.open();

        ServerSocketChannel ssChannel = ServerSocketChannel.open();
        ssChannel.configureBlocking(false);
        SelectionKey ssKey=ssChannel.register(selector, SelectionKey.OP_ACCEPT);
        InetSocketAddress address = new InetSocketAddress("127.0.0.1", 6665);
        ssChannel.bind(address);
        log.info("ssKey = "+ssKey);
        while (true) {
            selector.select();
            Set<SelectionKey> keys = selector.selectedKeys();
            Iterator<SelectionKey> keyIterator = keys.iterator();

            while (keyIterator.hasNext()) {
                SelectionKey key = keyIterator.next();
                keyIterator.remove();
                log.info("hasNext ");
                try{
                    if (key.isAcceptable()) {
                        ServerSocketChannel ssChannel1 = (ServerSocketChannel) key.channel();
                        SocketChannel sChannel = ssChannel1.accept();
                        sChannel.configureBlocking(false);
                        ByteBuffer buffer =ByteBuffer.allocate(10);
                        sChannel.register(selector, SelectionKey.OP_READ,buffer);
                    } else if (key.isReadable()) {
                        SocketChannel sChannel = (SocketChannel) key.channel();
                        int read=0;
                        ByteBuffer buffer=(ByteBuffer) key.attachment();
                        if(sChannel.isOpen()){
                            read=sChannel.read(buffer);
                        }
                        if(read!=-1){
                            TestBuffer1.split(buffer);
//

                            log.info("write success... read ="+read);
                        }else{
                            log.info("read false... read ="+read);
                            key.cancel();
                        }

                        //sChannel.close();
                    }
                }catch(IOException ex){
                    ex.printStackTrace();
                    key.cancel();
                    key.channel().close();
                    while(true);
                }
            }
        }
    }
}

