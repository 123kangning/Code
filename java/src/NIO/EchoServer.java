package NIO;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Set;
import java.util.logging.Level;
import java.util.logging.Logger;

public class EchoServer {
    public static final Logger log=Logger.getLogger(EchoServer.class.toString());
    public static int port=8889;
    public static void main(String[] args) throws IOException,InterruptedException{
        log.setLevel(Level.INFO);
        ServerSocketChannel serverChannel=null;
        ServerSocket ss=null;
        Selector selector=Selector.open();

        try{
            serverChannel=ServerSocketChannel.open();
            ss=serverChannel.socket();
            InetSocketAddress address=new InetSocketAddress(port);
            ss.bind(address);
            serverChannel.configureBlocking(false);

            serverChannel.register(selector, SelectionKey.OP_ACCEPT);
            while(true){
                try{
                    selector.select();
                }catch(IOException ex){
                    ex.printStackTrace();
                    while(true);

                }
                Set<SelectionKey> Keys=selector.selectedKeys();
                Iterator<SelectionKey> iterator=Keys.iterator();
                while(iterator.hasNext()){
                    SelectionKey key=iterator.next();
                    iterator.remove();
                    try{
                        if(key.isAcceptable()){
                            ServerSocketChannel server=(ServerSocketChannel) key.channel();
                            SocketChannel client=server.accept();
                            client.configureBlocking(false);
                            SelectionKey clientKey= client.register(selector,SelectionKey.OP_READ);

                        }
                        else if(key.isReadable()){
                            log.info("Readable "+key.channel().toString());
                            SocketChannel client=(SocketChannel)key.channel();
                            ByteBuffer output=ByteBuffer.allocate(1000);
                            if(-1==client.read(output)){
                                key.cancel();
                                log.info("write false...");
                            }else{
                                log.info("ago flip "+output);
                                output.flip();
                                log.info("after flip write ago "+output);
                                TestBuffer1.show(output);
//                                client.write(output);
//                                output.compact();
                                log.info("write success... "+output.get(0)+" | "+output.get(1)+" | "+output.get(2));
                            }

                        }
//                        else if(key.isWritable()){
//
//                            SocketChannel client=(SocketChannel) key.channel();
//                            ByteBuffer output=(ByteBuffer) key.attachment();
//
//
//
//
//
//
//                        }
                    }catch(IOException ex){
                        ex.printStackTrace();
                        key.cancel();
                        key.channel().close();
                        while(true)System.out.print("");
                    }
                }
            }
        }catch(IOException ex){
            ex.printStackTrace();
        }finally {
            if(ss!=null){
                ss.close();
            }
            if(serverChannel!=null){
                serverChannel.close();
            }
        }
    }
}
