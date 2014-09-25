import java.io.*;
import java.net.*;
import java.util.*;
class cliudp
{
   public static void main(String args[]) throws Exception
   {
                   System.out.println("Enter block size(1/1000/64000):");
                   Scanner sc = new Scanner(System.in);
                   int block = sc.nextInt();
                   byte[] a = new byte[block];
                   int n=(1000000000/block)+5;
       int i=0;
       for(i=0;i<block;i++)
      {
        a[i]=1;
      }
      DatagramSocket clientSocket = new DatagramSocket();
      InetAddress IP = InetAddress.getByName("localhost");
      DatagramPacket sendPacket = new DatagramPacket(a, a.length, IP, 9999);
       for(i=0;i<n;i++)      
       {  
         clientSocket.send(sendPacket);
       }
       clientSocket.close();
   }
}
