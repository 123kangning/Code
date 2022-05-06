package test1;

import java.io.*;
import java.util.*;

interface Tree{
    public default void setCode(Node root){
        Node p=root;
        Deque<Node> deque=new LinkedList<>();
        deque.offer(p);
        while(deque.size()>0){
            p=deque.poll();
            if(p.left!=null){
                p.left.setCode(p.getCode()+"0");
                deque.offer(p.left);
            }
            if(p.right!=null){
                p.right.setCode(p.getCode()+"1");
                deque.offer(p.right);
            }
        }
    }
    public default Node creatTree(Map<Character,Integer> map){
        LinkedList<Node> list=new LinkedList<>();
        for(Map.Entry<Character,Integer> e: map.entrySet()){
            Node node=new Node();
            node.setC(e.getKey());
            node.setWeight(e.getValue());
            node.left=null;
            node.right=null;
            list.add(node);
        }
        while(list.size()>0){
            Collections.sort(list);
            if(list.size()==1){
                return list.get(0);
            }else{
                Node node1=list.removeFirst();
                Node node2=list.removeFirst();
                Node node=new Node();
                node.setWeight(node1.getWeight()+node2.getWeight());
                node.setC('\0');

                if(node1.getWeight()<node2.getWeight()){
                    node.left=node1;
                    node.right=node2;
                }else{
                    node.left=node2;
                    node.right=node1;
                }
                list.add(node);
            }
        }
        return null;
    }
    public default void preCode(Node root,Map<Character,String> map){
        if(root==null){
            return ;
        }
        if(root.getC()!='\0'){
            map.put(root.getC(),root.getCode());
        }
        preCode(root.left,map);
        preCode(root.right,map);
    }
    public default void inCode(Node root,Map<Character,String> map){
        if(root==null){
            return ;
        }
        inCode(root.left,map);
        if(root.getC()!='\0'){
            map.put(root.getC(),root.getCode());
        }
        inCode(root.right,map);
    }
    public default void postCode(Node root,Map<Character,String> map){
        if(root==null){
            return ;
        }
        postCode(root.left,map);
        postCode(root.right,map);
        if(root.getC()!='\0'){
            map.put(root.getC(),root.getCode());
        }
    }
    public default void prePrint(Node root){
        if(root==null){
            return;
        }
        System.out.println(root.getC()+" "+root.getCode());
        prePrint(root.left);
        prePrint(root.right);
    }
    public default void inPrint(Node root){
        inPrint(root.left);
        if(root==null){
            return;
        }
        System.out.println(root.getC()+" "+root.getCode());
        inPrint(root.right);
    }
    public default void postPrint(Node root){
        postPrint(root.left);
        postPrint(root.right);
        if(root==null){
            return;
        }
        System.out.println(root.getC()+" "+root.getCode());
    }
}
class Node implements Comparable{
    private char c;
    private int weight;
    private String code="";
    Node left;
    Node right;
    public void setC(char c){
        this.c=c;
    }
    public void setWeight(int weight){
        this.weight=weight;
    }
    public void setCode(String c){
        code=code.concat(c);
    }
    public char getC(){
        return this.c;
    }
    public int getWeight(){
        return this.weight;
    }
    public String getCode(){
        return this.code;
    }
    public int compareTo(Object a){
        return this.getWeight()-((Node)a).getWeight();
    }
}
public class Huffman implements Tree{
    static String src1="1.txt",src2="hfm1.dat",src3="restore.txt";
    public static void main(String... args)  throws IOException{
        Tree tree=new Huffman();
        Scanner input=new Scanner(new FileInputStream(src1));
        Map<Character,Integer> map=account(input);
        Node root =tree.creatTree(map);

        tree.setCode(root);
        //print(root);
        Map<Character,String> map1=new HashMap<>();
        tree.preCode(root,map1);
        printToFile(map1);

//        for(Map.Entry<Character,String> e:map1.entrySet()){
//            System.out.println(e.getKey()+" "+e.getValue());
//        }System.out.println("--------------------------------------------------------------");
        try{
            restoreTree(map1);
        }catch(ClassNotFoundException e){
            e.printStackTrace();
            throw new RuntimeException(e);
        }
    }
    public static Map<Character,Integer> account(Scanner input) throws IOException{
        Map<Character,Integer> map=new HashMap<>();
        while(input.hasNext()){
            for(Character e: input.nextLine().concat("\n").toCharArray()){
                if(map.get(e)==null){
                    map.put(e,1);
                }else{
                    map.put(e,map.get(e)+1);
                }
            }
        }
        return map;
    }
    public static void printToFile(Map<Character,String> map)throws IOException{
        Scanner input=new Scanner(new FileInputStream(src1));
        ObjectOutputStream output=new ObjectOutputStream(new FileOutputStream(src2));

        output.writeObject(map);

        String numCode="";
        while(input.hasNext()){
            String s=input.nextLine();
            if(input.hasNext())s=s.concat("\n");
            for(char e: s.toCharArray()){
                numCode=numCode.concat(map.get(e));
            }
        }
        output.write('\n');
        for(char e: numCode.toCharArray()){
            if(e=='1')output.write(1);
            else output.write(0);
        }
        output.close();
    }
    public static void restoreTree(Map<Character,String> map) throws IOException, ClassNotFoundException {
        Map<Character,String> map1=new TreeMap<>();
        ObjectInputStream inputMap=new ObjectInputStream(new FileInputStream(src2));
        map1=(Map<Character, String>)inputMap.readObject();

        FileOutputStream output=new FileOutputStream(src3);
        String s="";
        int t=0;

        t=inputMap.read();
        while((t=inputMap.read())!=-1&&t<2){
            s=s.concat(String.valueOf(t));
        }

        int len=s.length();
        for(int i=0;i<len;i++){
            for(int L=1;L<=len/2+1;L++){
                int j=L+i;
                if(j>len)break;
                String sub=s.substring(i,j);
                for(Map.Entry<Character,String> e: map.entrySet()){
                    if(sub.equals(e.getValue())){
                        output.write(e.getKey());
                        i+=L;
                        L=0;
                    }
                }
            }
        }
        output.close();
    }
}