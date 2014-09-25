import java.io.*;
import java.net.*;
import java.util.*;

class th extends Thread
{   int block;
    int k;
     byte[] a;
    int j=0;
InputStream in;
   th(int block,int k)
    { a=new byte[block];  
      //this.in=in;
                    try{
                    ServerSocket listener = new ServerSocket(8888);        
                    Socket socket = listener.accept();
                    InputStream in=socket.getInputStream();}
                    catch(Exception E)
                    {
                       }

      this.k=k;
      this.block=block;
      start();
    }

  public void run()
         {
       try{
          while(j<k/block)
          {    in.read(a);   
               j++;
          }
   }catch(Exception e){}

          } 


}


public class sertcpth1{
 
    public static void main(String[] args)
 {    System.out.println("Enter block size(1/1000/64000):");
      Scanner sc = new Scanner(System.in);
      int block = sc.nextInt();
      System.out.println("Enter Threads:(1/2/4):");
      int thread=sc.nextInt();
      int i;
      int j=0;
      int k=0;
   long start=0,stop=0;
   float speed;
   float latency;
   long div=1000000000;
    th[] c=new th[10];
        
      try{
                                             for(i=0;i<thread;i++)
        {
            c[i]=new th(10000000/thread,block);}
        for(i=0;i<thread;i++)
         {
   try{
             c[i].join();
       }
    catch(Exception e){}
      }        
  
 

}
        catch(Exception e) 
         {
            System.out.println("something is wrong");
         }
    //   stop=System.currentTimeMillis()-start;     
   //    System.out.println(stop);
  //     latency=(float)stop*block/(div);
 //      speed=(float)((float)(div/(stop*8))/1000);
  //     System.out.println("speed="+speed+"Mb/s and latency="+latency+".");
                     	                
                
 }
        
    }

