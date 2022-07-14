package NIO;

import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.util.logging.Logger;

public class TestBuffer1 {
    public static final Logger log=Logger.getLogger(EchoServer.class.toString());
    public static void main(String[] args) {
        ByteBuffer source = ByteBuffer.allocate(10);
        source.put("hello,wor9".getBytes());
        split(source);

        source.put(" I'm zh\n".getBytes());
        split(source);
    }
    public static void split(ByteBuffer source){
        source.flip();
        for(int i=0;i<source.limit();i++){
            if(source.get(i)=='\n'){
                int length=i-source.position()+1;
                ByteBuffer target=ByteBuffer.allocate(length);
                for(int j=0;j<length;j++){
                    target.put(source.get());
                }
                target.flip();
                System.out.println(Charset.defaultCharset().decode(target));
            }
        }
        source.compact();
    }
    public static void show(ByteBuffer buffer){
        System.out.println("----------------------------------------------------------");
        for(int i=buffer.position();i<buffer.limit();i++){
            System.out.print(" | "+i);
        }System.out.println();
        for(int i=buffer.position();i<buffer.limit();i++){
            System.out.print(" | "+(char)buffer.get(i));
        }
        System.out.println("----------------------------------------------------------");
    }
}
