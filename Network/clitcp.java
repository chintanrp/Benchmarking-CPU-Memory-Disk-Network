import java.io.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.*;
import javax.swing.JOptionPane;

public class clitcp {
    public static void main(String[] args) throws IOException 
{     System.out.println("Enter block size(1/1000/64000):");
       Scanner sc = new Scanner(System.in);
       int block = sc.nextInt();
       int i=0;
       int j=0;
       int n=100000000/block; 
       byte[] a = new byte[block]; 
       while(i<block)
       {
        a[i]=1;
        i++;
       }     
       Socket tSocket = new Socket("localhost", 8888);
       OutputStream out=tSocket.getOutputStream();
       while(j<n)
       {   
         out.write(a);
         j++;
       }
}
                         }


