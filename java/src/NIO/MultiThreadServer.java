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
import java.util.concurrent.atomic.AtomicInteger;
import java.util.logging.Logger;

public class MultiThreadServer {
    public static final Logger log=Logger.getLogger(EchoServer.class.toString());
    public static void main(String[] args)throws IOException {
        Thread.currentThread().setName("boss");

        ServerSocketChannel ssChannel = ServerSocketChannel.open();
        ssChannel.configureBlocking(false);
        Selector boss = Selector.open();
        ssChannel.register(boss, SelectionKey.OP_ACCEPT);
        InetSocketAddress address = new InetSocketAddress("127.0.0.1", 8887);
        ssChannel.bind(address);

        Worker[] workers=new Worker[6];
        for(int i=0;i<workers.length;i++){
            workers[i]=new Worker("worker-"+i);
        }

        AtomicInteger index=new AtomicInteger();
        while (true) {
            boss.select();
            Set<SelectionKey> keys = boss.selectedKeys();
            Iterator<SelectionKey> keyIterator = keys.iterator();

            while (keyIterator.hasNext()) {
                SelectionKey key = keyIterator.next();
                keyIterator.remove();
                    if (key.isAcceptable()) {
                        SocketChannel sc = ssChannel.accept();
                        log.info("connected... "+sc.getRemoteAddress());
                        sc.configureBlocking(false);

                        log.info("before register... "+sc.getRemoteAddress());
                        workers[index.getAndIncrement()% workers.length].register(sc);//????????worker???????select??????????????socketChannel?????worker??Selector?

                        log.info("after register... "+sc.getRemoteAddress());
                    }
                }
            }
    }
    //selector worker???????
    static class Worker implements Runnable{
        private Thread thread;
        private Selector worker;
        private volatile boolean start=false;
        private String name;
        public Worker(String name){
            this.name=name;
        }

        public void register(SocketChannel sc)throws IOException{
            if(!start){//对于每个worker对象只执行一次
                worker=Selector.open();
                thread=new Thread(this,name);
                thread.start();

                start=true;
            }

            worker.wakeup();
            ByteBuffer buffer=ByteBuffer.allocate(16);
            sc.register(worker,SelectionKey.OP_READ,buffer);
        }

        @Override
        public void run() {
            while(true){
                try{
                    worker.select();

                    Iterator<SelectionKey> iterator=worker.selectedKeys().iterator();
                    while(iterator.hasNext()){
                        SelectionKey key=iterator.next();
                        iterator.remove();
                        if(key.isReadable()){
                            ByteBuffer buffer=(ByteBuffer) key.attachment();
                            SocketChannel channel=(SocketChannel) key.channel();

                            int read=channel.read(buffer);

                            if(read!=-1){
                                TestBuffer1.split(buffer);

                                if(buffer.position()==buffer.limit()){
                                    buffer.flip();

                                    ByteBuffer buff=ByteBuffer.allocate(buffer.capacity()*2);
                                    buff.put(buffer);
                                    key.attach(buff);
                                }
                                log.info("read... Thread = "+Thread.currentThread());

                            }else{
                                log.info("read false... read ="+read);
                                key.cancel();
                            }

                        }
                    }
                }catch(IOException ex){
                    ex.printStackTrace();
                }

            }

        }
    }
}
