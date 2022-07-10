package IO;

import java.io.*;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.Date;

public class Serve1 {
    public static void main(String[] args) throws IOException {
        try(ServerSocket server=new ServerSocket()){
            server.setReuseAddress(true);
            InetSocketAddress address=new InetSocketAddress(8881);
            server.bind(address);
            while(true){

                try(Socket connection=server.accept()){

                    System.out.println("run");
                    OutputStream out=connection.getOutputStream();
                    Writer writer=new BufferedWriter(new OutputStreamWriter(out, StandardCharsets.US_ASCII));
                    Date now=new Date();
                    writer.write(now+"\n");
                    writer.flush();
                    long lastTime=now.getTime()/1000,nowTime;
                    while(connection!=null){
                        now=new Date();
                        nowTime=now.getTime();
                        if(nowTime%1000==0&&nowTime/1000!=lastTime){
                            writer.write(now+"\n");
                            writer.flush();
                            lastTime=nowTime/1000;
                        }
                    }
                    System.out.println(now+"\n");

                }catch(IOException ex){
                    ex.printStackTrace();
                }
            }
        }catch(IOException ex){
            ex.printStackTrace();
        }
    }
}
