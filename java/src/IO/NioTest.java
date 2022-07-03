package IO;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;

public class NioTest {
    public static void main(String[] args) throws IOException{
        fastCopy("1.txt","hfm1.dat");
    }
    public static void fastCopy(String src, String dist) throws IOException {

        /* ??????????? */
        FileInputStream fin = new FileInputStream(src);

        /* ???????????? */
        FileChannel fcin = fin.getChannel();

        /* ???????????? */
        FileOutputStream fout = new FileOutputStream(dist);

        /* ?????????? */
        FileChannel fcout = fout.getChannel();

        /* ?????? 1024 ??? */
        ByteBuffer buffer = ByteBuffer.allocateDirect(1024);

        while (true) {

            /* ??????????????? */
            int r = fcin.read(buffer);

            /* read() ?? -1 ?? EOF */
            if (r == -1) {
                break;
            }

            /* ???? */
            buffer.flip();

            /* ?????????????? */
            fcout.write(buffer);

            /* ????? */
            buffer.clear();
        }
    }

}
