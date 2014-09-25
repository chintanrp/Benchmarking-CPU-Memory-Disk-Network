import java.io.*;
import java.net.*;
import java.util.*;
public class sertcp
{

    public static void main(String[] args)
 { System.out.println("Enter block size(1/1000/64000):");
   Scanner sc = new Scanner(System.in);
   int block = sc.nextInt();
   int i;
   int j=0;
   int k=0;
   long start=0,stop=0;
   float speed;
   float latency;
   float data=100;
   float s;
   int n=100000000/block;
   long div=100000000;
        byte[] a = new byte[block];
      try{
                    ServerSocket listener = new ServerSocket(8888);        
                    Socket socket = listener.accept();
                    start=System.currentTimeMillis();
                    InputStream in=socket.getInputStream();
      while(j<n)
         {    in.read(a);   
              j++;
         }
 }
        catch(Exception e) 
         {
            System.out.println("something is wrong");
         }
       stop=System.currentTimeMillis()-start;     
       System.out.println(stop);
       latency=(float)stop*block/(div);
       s=(float)stop/1000; 
       speed=(float)((float)data*8/s);
       System.out.println("speed="+speed+"Mb/s and latency="+latency+".");
                     	                
                
 }
        
    }

