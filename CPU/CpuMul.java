import java.util.*;
class th extends Thread {
  
  public int i,j,k;
  th( int i){
    this.i=i;
    start();
  }
  public void run() {
    int j=0, a=20,b=10;  
    while(j<i)
    {
      a+=b;
      b+=i;
      a+=b+j;
      b+=j+a;
      b+=a*j;
      a+=b;
      b+=i;
      a+=b+j;
      b+=j+a;
      b+=a*j;
      j++;
    } 
  }
}

public class CpuMul {
  public static void main(String args[]) {

    int threads1 = Integer.parseInt(args[0]);
    int iteration = Integer.parseInt(args[1]);
    th[] threads = new th[threads1];
    int itr = iteration/threads1;
      
    long start1 = System.currentTimeMillis();
    System.out.println(start1);

    for(int i = 0 ; i < threads1 ; i++) {
      threads[i] = new th(itr);
    }
    try{
      for(int i = 0 ; i < threads1 ; i++) {
        threads[i].join();
      }
    }
    catch(Exception e)
    {
      System.out.println("this is not done!!!!");
    }
      
    long end = System.currentTimeMillis();
    System.out.println(end);

    long time = end - start1;
    System.out.println("Running Time in milliseconds : " + time);

    float iops = 0 , giops =0;
    iops = ((iteration/time)*1000)*16;

    giops = (iops/1000000000);
    System.out.println("IOPS : " + iops);
    System.out.println("GIOPS : " + giops);
  }
}