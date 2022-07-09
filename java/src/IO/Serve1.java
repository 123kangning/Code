package IO;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.Date;

public class Serve1 {
    public static void main(String[] args) throws IOException {
        ServerSocket server=new ServerSocket(8888);
        while(true){
            try(Socket connection=server.accept()){
                System.out.println("run");
                OutputStream out=connection.getOutputStream();
                Writer writer=new BufferedWriter(new OutputStreamWriter(out, StandardCharsets.US_ASCII));
                Date now=new Date();
                writer.write(now+"\n");
                out.flush();
            }catch(IOException ex){
                ex.printStackTrace();
            }
        }

//        connection.close();
    }
}
