package NIO;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.nio.charset.Charset;
import java.util.Iterator;
import java.util.Set;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.logging.Logger;

public class MultiThreadServer {
    public static final Logger log=Logger.getLogger(EchoServer.class.toString());
    //selector boss ???????
    public static void main(String[] args)throws IOException {
        Thread.currentThread().setName("boss");

        ServerSocketChannel ssChannel = ServerSocketChannel.open();
        ssChannel.configureBlocking(false);
        Selector boss = Selector.open();
        SelectionKey ssKey=ssChannel.register(boss, SelectionKey.OP_ACCEPT);
        InetSocketAddress address = new InetSocketAddress("127.0.0.1", 8887);
        ssChannel.bind(address);

        //1.???????Worker ,????
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
                log.info("hasNext ");
                    if (key.isAcceptable()) {
                        SocketChannel sc = ssChannel.accept();
                        log.info("connected... "+sc.getRemoteAddress());
                        sc.configureBlocking(false);
                        //2.?? selector
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
        //private static ConcurrentLinkedDeque<Runnable> queue=new ConcurrentLinkedDeque<>();
        public Worker(String name){
            this.name=name;
        }

        public void register(SocketChannel sc)throws IOException{
            if(!start){
                worker=Selector.open();
                thread=new Thread(this,name);
                thread.start();

                start=true;
            }
//            queue.add(()-> {
//                try {
//                    sc.register(worker,SelectionKey.OP_READ,null);
//                } catch (ClosedChannelException e) {
//                    e.printStackTrace();
//                }
//            });
            worker.wakeup();
            sc.register(worker,SelectionKey.OP_READ,null);
        }

        @Override
        public void run() {
            while(true){
                try{

                    worker.select();
//                    Runnable task=queue.poll();
//                    if(task!=null){
//                        task.run();;
//                    }
                    Iterator<SelectionKey> iterator=worker.selectedKeys().iterator();
                    while(iterator.hasNext()){
                        SelectionKey key=iterator.next();
                        iterator.remove();
                        if(key.isReadable()){
                            ByteBuffer buffer=ByteBuffer.allocate(16);
                            SocketChannel channel=(SocketChannel) key.channel();

                            int read=channel.read(buffer);
                            buffer.flip();
                            if(read!=-1){
                                log.info("read... Thread = "+Thread.currentThread());
                                System.out.println(Charset.defaultCharset().decode(buffer));
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
