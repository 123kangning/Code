package test1;

import java.io.*;
import java.util.*;


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
public class Huffman {
    static int count=0;
    static String src1="1.txt",src2="hfm2.txt",src3="hfm1.txt";
    static String numCode="";
    public static void main(String... args)  throws IOException{

        Scanner input=new Scanner(new FileInputStream(src1));
        PrintWriter output=new PrintWriter(new FileOutputStream(src2));
        Map<Character,Integer> map=account(input);
        Node root =creatTree(map);

        setCode(root);
        //print(root);
        Map<Character,String> map1=new HashMap<>();
        matchCode(root,map1);
        printToFile(map1);
        restoreTree(map1);
    }
    public static Map<Character,Integer> account(Scanner input) throws IOException{
        Map<Character,Integer> map=new HashMap<>();
        while(input.hasNext()){
            for(Character e: input.nextLine().toCharArray()){
                if(map.get(e)==null){
                    map.put(e,1);
                }else{
                    map.put(e,map.get(e)+1);
                }
            }
        }
        return map;
    }
    public static Node creatTree(Map<Character,Integer> map){
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
        return list.get(0);
    }
    public static void setCode(Node root){
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
    public static Map<Character,String> matchCode(Node root,Map<Character,String> map){
        if(root==null){
            return map;
        }
        matchCode(root.left,map);
        matchCode(root.right,map);
        if(root.getC()!='\0'){
            map.put(root.getC(),root.getCode());
        }
        return map;
    }
    public static void print(Node root){
        if(root==null){
            return;
        }
        System.out.println(root.getC()+" "+root.getCode());
        print(root.left);
        print(root.right);
    }
    public static void printToFile(Map<Character,String> map)throws IOException{
        Scanner input=new Scanner(new FileInputStream(src1));
        PrintWriter output=new PrintWriter(new FileOutputStream(src2));
        while(input.hasNext()){
            String s=input.next();
            for(char e: s.toCharArray()){
                numCode=numCode.concat(map.get(e));
            }
        }
        System.out.println("    "+numCode);
        int code=0;
        for(char e: numCode.toCharArray()){
            if(count%32==0&&code!=0){
                //System.out.println(code);
                output.println(code);
                code=0;
            }
            if(e=='0'){
                code|=0;
            }else{
                code|=1;
            }
            count++;
            code=code<<1;
        }
        code=code>>1;
        //System.out.println(code);
        output.println(code);
        input.close();
        output.close();
    }
    public static void restoreTree(Map<Character,String> map) throws IOException{
        Scanner input=new Scanner(new FileInputStream(src2));
        PrintWriter output=new PrintWriter(new FileOutputStream(src3));
        String s=numCode;

        System.out.println("s = "+s);
        int len=s.length();
        for(int i=0;i<len;i++){
            for(int L=1;L<=len/2+1;L++){
                int j=L+i;
                if(j>len)break;
                //System.out.println("i = "+i+" j = "+j);
                String sub=s.substring(i,j);
                //System.out.println(sub);
                for(Map.Entry<Character,String> e: map.entrySet()){
                    if(sub.equals(e.getValue())){
                        //System.out.println(e.getKey());
                        output.print(e.getKey());
                        i+=L;
                        L=0;
                    }
                }
            }
        }
        input.close();
        output.close();
    }
}
