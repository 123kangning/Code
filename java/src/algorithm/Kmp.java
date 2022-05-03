package algorithm;

public class Kmp {
    public static void main(String... args){
        String pattern="assdddffg";
        String text="asdfassdddffg";
        int result=match(text,pattern);
        if(result==-1){
            System.out.println("Not find pattern in text");
            System.exit(0);
        }
        System.out.println("match result is "+result);
    }
    public static int match(String text,String pattern){
        int[] fail=getNext(pattern);
        int i=0;
        int k=0;
        while(i<text.length()){
            if(text.charAt(i)==pattern.charAt(k)){
                if(k==pattern.length()-1){
                    return i-k+1;
                }
                i++;
                k++;
            }else{
                if(k>0){
                    k=fail[k-1];
                }else{
                    i++;
                }
            }
        }
        return -1;
    }
    public static int[] getNext(String pattern){
        int[] file=new int[pattern.length()];
        int i=1,k=0;
        while(i<pattern.length()){
            if(pattern.charAt(i)==pattern.charAt(k)){
                file[i]=k+1;
                i++;
                k++;
            }else{
                if(k>0){
                    k=file[k-1];
                }else{
                    i++;
                }
            }
        }
        return file;
    }
}
