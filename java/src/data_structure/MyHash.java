package data_structure;

public class MyHash implements Hash{
    public int hashCodeForString(String a){
        int b=31;
        int hashCode=a.charAt(0);
        for(Character e:a.substring(1).toCharArray()){
            hashCode*=b;
            hashCode+=e;
        }
        return hashCode;
    }
    public int hashCodeForChar(Character a){
        return (int)a;
    }
    public int hashCodeForByte(Byte a){
        return (int)a;
    }
    public int hashCodeForInteger(Integer a){
        return a;
    }
    public int hashCodeForShort(Short a){
        return (int)a;
    }
    public int hashCodeForLong(Long a){
        return (int)(a^(a>>32));
    }

}
