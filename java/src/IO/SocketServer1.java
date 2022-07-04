package IO;


import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.URLDecoder;
import java.net.URLEncoder;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.util.Iterator;

public class SocketServer1 {


    /**
     * ??
     */


    public static void main(String[] args) throws Exception {
        ServerSocketChannel serverChannel = ServerSocketChannel.open();
        serverChannel.configureBlocking(false);
        ServerSocket serverSocket = serverChannel.socket();
        serverSocket.setReuseAddress(true);
        serverSocket.bind(new InetSocketAddress("127.0.0.1",8077));

        Selector selector = Selector.open();
        //????????????SelectionKey.OP_ACCEPT??
        serverChannel.register(selector, SelectionKey.OP_ACCEPT);
        System.out.println(1);
        try {
            while(true) {
                //?????????????selector????????????????????
                //java???????IO??????????? ?????????
                if(selector.select(100) == 0) {
                    //================================================
                    //      ???????????????????
                    //================================================
                    continue;
                }
                //???????????????????????????????(??????????)
                Iterator<SelectionKey> selecionKeys = selector.selectedKeys().iterator();
                System.out.println(2);
                while(selecionKeys.hasNext()) {
                    SelectionKey readyKey = selecionKeys.next();
                    System.out.println(3);

                    System.out.println("isAccept = "+readyKey.isAcceptable()+" isValid = "+ readyKey.isValid());
                    SelectableChannel selectableChannel = readyKey.channel();
                    if(readyKey.isValid() && readyKey.isAcceptable()) {

                        ServerSocketChannel serverSocketChannel = (ServerSocketChannel)selectableChannel;
                        SocketChannel socketChannel = serverSocketChannel.accept();
                        registerSocketChannel(socketChannel , selector);
                        readSocketChannel(readyKey);
                    }
                    selecionKeys.remove();
                }
            }
        } catch(Exception e) {

        } finally {
            serverSocket.close();
        }
    }


    private static void registerSocketChannel(SocketChannel socketChannel , Selector selector) throws Exception {
        socketChannel.configureBlocking(false);

        socketChannel.register(selector, SelectionKey.OP_READ , ByteBuffer.allocate(2048));
    }


    private static void readSocketChannel(SelectionKey readyKey) throws Exception {
        SocketChannel clientSocketChannel = (SocketChannel)readyKey.channel();
        System.out.println(4);
        InetSocketAddress sourceSocketAddress = (InetSocketAddress)clientSocketChannel.getRemoteAddress();
        Integer resoucePort = sourceSocketAddress.getPort();

        ByteBuffer contextBytes = (ByteBuffer)readyKey.attachment();

        int realLen = -1;
        try {
            realLen = clientSocketChannel.read(contextBytes);
        } catch(Exception e) {
            System.out.println("exit");
            clientSocketChannel.close();
            return;
        }

        if(realLen == -1) {

            return;
        }


        contextBytes.flip();

        byte[] messageBytes = contextBytes.array();
        String messageEncode = new String(messageBytes , "UTF-8");
        String message = URLDecoder.decode(messageEncode, "UTF-8");
        System.out.println("message = "+message);

        if(message.indexOf("over") != -1) {

            contextBytes.clear();



            ByteBuffer sendBuffer = ByteBuffer.wrap(URLEncoder.encode("??????", "UTF-8").getBytes());
            clientSocketChannel.write(sendBuffer);
            clientSocketChannel.close();
        } else {

            contextBytes.position(realLen);
            contextBytes.limit(contextBytes.capacity());
        }
    }
}
