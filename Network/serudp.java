import java.io.*;
import java.net.*;
import java.util.*;

class serudp
{
   public static void main(String args[]) throws Exception
      {int i=0;
       long start=0,stop=0;
       float s;
       float speed,latency;
                   System.out.println("Enter block size(1/1000/64000):");
                   Scanner sc = new Scanner(System.in);
                   int block = sc.nextInt();
                   int n=100000000/block;
                   DatagramSocket serverSocket = new DatagramSocket(9999);
                   byte[] receiveData = new byte[block];
           
          //         System.out.println("q");
                   DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
                  
                    serverSocket.receive(receivePacket);
                    start=System.currentTimeMillis();
                    System.out.println(start);
                    for(i=0;i<n;i++)
                    {  
                                serverSocket.receive(receivePacket);
                        //        String sentence = new String( receivePacket.getData());
                     }
               stop=System.currentTimeMillis()-start;
               s=(float)stop/1000;
                System.out.println(s);
            
               speed=(float)((float)100*8/s);
               latency=(float)((float)(stop*block)/1000000);
               System.out.println("speed="+speed+"Mb/s and latency="+latency+"ms.");                           
      }
}
