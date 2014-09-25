import java.io.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.*;
import javax.swing.JOptionPane;


class th extends Thread 
{ byte[] a;
  int j=0;
  int k;
  int block;  
  OutputStream out;
 //th(int block)
      
th(OutputStream out,int k,int block)
{ 
    int i=0;
    block=this.block;
    while(i<block)
       {
        a[i]=1;
        i++;
       }
      
  this.k=k;
  this.out=out;
   start();
  }
public void run()
{   try{
   while(j<k/block)
       {   
         out.write(a);
         j++;
       }
      }catch(Exception e)
        {}
}
}




public class clitcpth1 {
    public static void main(String[] args) throws IOException 
{     System.out.println("Enter block size(1/1000/64000):");
      Scanner sc = new Scanner(System.in);
       int block = sc.nextInt();
      System.out.println("ebter (1/2):");
    //  Scanner sc = new Scanner(System.in);
       int thread = sc.nextInt();
       int i=0;
       int j=0; 
            //  byte[] a = new byte[block]; 
       th[] c=new th[10];   
       Socket tSocket = new Socket("localhost", 8888);
       OutputStream out=tSocket.getOutputStream();
        for(i=0;i<thread;i++)
        {
         c[i]=new th(out,10000000/thread,block);}
        for(i=0;i<thread;i++)
         {
   try{
             c[i].join();
       }
    catch(Exception e){}
      }        


  }
                         }


