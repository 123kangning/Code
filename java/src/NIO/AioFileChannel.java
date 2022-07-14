package NIO;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.AsynchronousFileChannel;
import java.nio.channels.CompletionHandler;
import java.nio.charset.Charset;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.logging.Logger;

public class AioFileChannel {
    public static final Logger log=Logger.getLogger(EchoServer.class.toString());
    public static void main(String[] args){

        try(AsynchronousFileChannel channel=AsynchronousFileChannel.open(Paths.get("1.txt"), StandardOpenOption.READ)){
            //ByteBuffer ,position ,attachment ,????
            ByteBuffer buffer=ByteBuffer.allocate(16);
            log.info("read begin...");
            channel.read(buffer, 0, buffer, new CompletionHandler<Integer, ByteBuffer>() {
                @Override //read success
                public void completed(Integer result, ByteBuffer attachment) {//result ????????
                    log.info("read finish...");
                    attachment.flip();
                    System.out.println(Charset.defaultCharset().decode(attachment));
                }

                @Override //read false
                public void failed(Throwable exc, ByteBuffer attachment) {
                        exc.printStackTrace();
                }
            });
            log.info("read end...");
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }catch (IOException e){
            e.printStackTrace();
        }

    }
}
