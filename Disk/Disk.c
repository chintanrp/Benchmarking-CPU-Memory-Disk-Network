#include <stdio.h>      
#include <stdlib.h>
#include <unistd.h>    
#include <sys/types.h> 
#include <pthread.h>    
#include <string.h>     
#include <sys/time.h>  
#include <errno.h>      

typedef struct str_thdata
{   int thread_no;
//  char *c;
    char *temp;
    int i;
    int j;
    int siz;
   } thdata;

void readths ( void *ptr )
{   int i;
    int j;
    thdata *data;      
    data = (thdata *) ptr;  /* type cast to a pointer to thdata */        
    FILE  *fw;
             float m;
        m=500000000;      
   //     sizof=m/i;
        char *ch=(char*)calloc(data->j,data->siz);
        fw=fopen("to.txt","w");
        fread(ch,data->siz,data->j,fw);         
        fclose(fw);

    pthread_exit(0); /* exit */
}
void rreadths ( void *ptr )
{   int i;
    int j;
    int k;
    thdata *data;      
    data = (thdata *) ptr;  /* type cast to a pointer to thdata */        
    FILE  *fw;
             float m;
        m=500000000;      
   //     sizof=m/i;
        char *ch=(char*)calloc(data->j,data->siz);
        fw=fopen("to.txt","w");
        for(k=0;k<data->j;k++)         
{  
    j = rand()%data->j;
    fseek(fw, j, SEEK_SET );
    fread(ch,j,1,fw);         
} 
         
        fclose(fw);

    pthread_exit(0); /* exit */
}
void rwreadths ( void *ptr )
{   int i;
    int j;
    int k;
    thdata *data;      
    data = (thdata *) ptr;  /* type cast to a pointer to thdata */        
    FILE  *fw;
             float m;
        m=500000000;      
   //     sizof=m/i;
        char *ch=(char*)calloc(data->j,data->siz);
        fw=fopen("to.txt","w");
        for(k=0;k<data->j;k++)         
{  
    j = rand()%data->j;
    fseek(fw, j, SEEK_SET );
    fwrite(ch,j,1,fw);         
} 
         
        fclose(fw);

    pthread_exit(0); /* exit */
}


void wreadths ( void *ptr )
{   int i;
    int j;
    thdata *data;      
    data = (thdata *) ptr;  /* type cast to a pointer to thdata */        
    FILE  *fw;
             float m;
        m=500000000;      
   //     sizof=m/i;
        char *ch=(char*)calloc(data->j,data->siz);
        fw=fopen("to.txt","w");
        fwrite(ch,data->siz,data->j,fw);         
        fclose(fw);

    pthread_exit(0); /* exit */
}


void main()
{ int siz;
  char rw;
  char sr;  
  struct timeval t1,t2;
  struct timezone z;
  int th=2;
  pthread_t thread1, thread2,thread3,thread4;  
  thdata data1, data2,data3,data4;         
  float speed,latency;  
  
   long r;
   printf("Read/Write:enter(r/w):");
   scanf("%c",&rw);
   printf("\nBlock size:(1B=1,1KB=2,1MB=3):");
   scanf("%d",&siz);
   printf("Sequncial or Random(s/r):");
   scanf(" %c",&sr);
   printf("Enter number of threads(1/2/4) :");
   scanf("%d",&th);
   printf("%C,%d,%c \n",rw,siz,sr);
   if(siz==1){siz=1;}
   if(siz==2){siz=1000;}
   if(siz==3){siz=1000000;}
   if(rw=='r'&& sr=='s')
       { gettimeofday(&t1,&z);
    // printf("%d",siz);
     file_read(siz);
     gettimeofday(&t2,&z);  
     r=t2.tv_usec-t1.tv_usec;
     printf("%ld\n",r);
      speed=500000000/r;
      latency=(r*siz)/500000000;
 printf("speed:%f,latency:%f",speed,latency);      
 }
   if(rw=='w'&& sr=='s')
       {
      gettimeofday(&t1,&z);
    //  printf("%d",siz);
      file_write(siz);
      gettimeofday(&t2,&z);  
      r=t2.tv_usec-t1.tv_usec;
      printf("%ld\n",r);
       speed=500000000/r;
      latency=(r*siz)/500000000;
      printf("speed:%f MB/s,latency:%f ms",speed,latency);
       }
   if(rw=='r'&& sr=='r')
        {
       gettimeofday(&t1,&z);
     // printf("%d",siz);
       r_file_read(siz);
       gettimeofday(&t2,&z);
       r=t2.tv_usec-t1.tv_usec;
       printf("%ld\n",r);
      speed=500000000/r;
      latency=(r*siz)/500000000;
      printf("\nspeed:%f MB/s,latency:%f ms \n",speed,latency);
      
         }
         if(rw=='w'&& sr=='r')
         {
         gettimeofday(&t1,&z);
   //     printf("%d",siz);
          r_file_write(siz);
         gettimeofday(&t2,&z); 
         r=t2.tv_usec-t1.tv_usec;
         printf("%ld\n",r);
      speed=500000000/r;
      latency=(r*siz)/500000000;
      printf("\nspeed:%f MB/s,latency:%f ms \n",speed,latency);
          }
   
   if(th>1&& rw=='w'&& sr=='s')
      {  
        
         data1.thread_no = 1;
         data1.i = 0;
         data1.j = 25000000/siz;
         data1.siz=siz;   
         data2.thread_no = 2;    
         data2.i = 250000000/siz+1;
         data2.j = 500000000/siz;
         data2.siz=siz;
        if(th==4)
          {
         data1.thread_no = 1;
         data1.i = 0;
         data1.j = 12500000/siz;
         data1.siz=siz;   
         data2.thread_no = 2;    
         data2.i = 125000000/siz+1;
         data2.j = 250000000/siz;
         data2.siz=siz;
         data3.thread_no = 3;
         data3.i = 25000000;
         data3.j = 35000000/siz;
         data3.siz=siz;   
         data4.thread_no = 4;    
         data4.i = 350000000/siz+1;
         data4.j = 500000000/siz;
         data4.siz=siz; 
             }
         gettimeofday(&t1,&z);       
         //  printf("\nStart time in micro sec. : %d\n",t1.tv_usec);   
         pthread_create (&thread1, NULL, (void *) & wreadths, (void *) &data1);
         pthread_create (&thread2, NULL, (void *) & wreadths, (void *) &data2);
         if(th==4)
         {pthread_create (&thread3, NULL, (void *) & wreadths, (void *) &data3);
         pthread_create (&thread4, NULL, (void *) & wreadths, (void *) &data4);
           }
         pthread_join(thread1, NULL);
         pthread_join(thread2, NULL);
         gettimeofday(&t2,&z);
         r=t2.tv_usec-t1.tv_usec;
         printf("%ld\n",r);  
         speed=500000000/r;
         latency=(r*siz)/500000000;
         printf("\nspeed:%f MB/s,latency:%f ms.\n",speed,latency);
      }
   if(th>1&& rw=='r'&& sr=='s')
      {  
        
         data1.thread_no = 1;
         data1.i = 0;
         data1.j = 25000000/siz;
         data1.siz=siz;   
         data2.thread_no = 2;    
         data2.i = 250000000/siz+1;
         data2.j = 500000000/siz;
         data2.siz=siz;
      if(th==4)
          {
         data1.thread_no = 1;
         data1.i = 0;
         data1.j = 12500000/siz;
         data1.siz=siz;   
         data2.thread_no = 2;    
         data2.i = 125000000/siz+1;
         data2.j = 250000000/siz;
         data2.siz=siz;
         data3.thread_no = 3;
         data3.i = 25000000;
         data3.j = 35000000/siz;
         data3.siz=siz;   
         data4.thread_no = 4;    
         data4.i = 350000000/siz+1;
         data4.j = 500000000/siz;
         data4.siz=siz; 
             }

         gettimeofday(&t1,&z);       
    //  printf("\nStart time in micro sec. : %d\n",t1.tv_usec);   
         pthread_create (&thread1, NULL, (void *) & readths, (void *) &data1);
         pthread_create (&thread2, NULL, (void *) & readths, (void *) &data2);
         if(th==4)
         {pthread_create (&thread1, NULL, (void *) & readths, (void *) &data3);
         pthread_create (&thread2, NULL, (void *) & readths, (void *) &data4);}
         pthread_join(thread1, NULL);
         pthread_join(thread2, NULL);
         gettimeofday(&t2,&z);
         r=t2.tv_usec-t1.tv_usec;
         printf("%ld\n",r);  
         speed=500000000/r;
         latency=(r*siz)/500000000;
         printf("\nspeed:%f MB/s,latency:%f ms. \n",speed,latency);
      }
   if(th>1&& rw=='r'&& sr=='r')
      {  
        
         data1.thread_no = 1; 
         data1.i = 0;
         data1.j = 25000000/siz;
         data1.siz=siz;   
         data2.thread_no = 2;    
         data2.i = 250000000/siz+1;
         data2.j = 500000000/siz;
         data2.siz=siz;
         gettimeofday(&t1,&z);
if(th==4)
          {
         data1.thread_no = 1;
         data1.i = 0;
         data1.j = 12500000/siz;
         data1.siz=siz;   
         data2.thread_no = 2;    
         data2.i = 125000000/siz+1;
         data2.j = 250000000/siz;
         data2.siz=siz;
         data3.thread_no = 3;
         data3.i = 25000000;
         data3.j = 35000000/siz;
         data3.siz=siz;   
         data4.thread_no = 4;    
         data4.i = 350000000/siz+1;
         data4.j = 500000000/siz;
         data4.siz=siz; 
             }
       
    //  printf("\nStart time in micro sec. : %d\n",t1.tv_usec);   
         pthread_create (&thread1, NULL, (void *) & rreadths, (void *) &data1);
         pthread_create (&thread2, NULL, (void *) & rreadths, (void *) &data2);
         if(th==4)
         {pthread_create (&thread1, NULL, (void *) & rreadths, (void *) &data1);
         pthread_create (&thread2, NULL, (void *) & rreadths, (void *) &data2);
         }
         pthread_join(thread1, NULL);
         pthread_join(thread2, NULL);
         gettimeofday(&t2,&z);
         r=t2.tv_usec-t1.tv_usec;
         printf("%ld\n",r);  
         speed=500000000/r;
         latency=(r*siz)/500000000;
         printf("\nspeed:%f MB/s,latency:%f ms.\n",speed,latency);
      }
if(th>1&& rw=='w'&& sr=='r')
      {  
        
         data1.thread_no = 1;
         data1.i = 0;
         data1.j = 25000000/siz;
         data1.siz=siz;   
         data2.thread_no = 2;    
         data2.i = 250000000/siz+1;
         data2.j = 500000000/siz;
         data2.siz=siz;
         if(th==4)
          {
         data1.thread_no = 1;
         data1.i = 0;
         data1.j = 12500000/siz;
         data1.siz=siz;   
         data2.thread_no = 2;    
         data2.i = 125000000/siz+1;
         data2.j = 250000000/siz;
         data2.siz=siz;
         data3.thread_no = 3;
         data3.i = 25000000;
         data3.j = 35000000/siz;
         data3.siz=siz;   
         data4.thread_no = 4;    
         data4.i = 350000000/siz+1;
         data4.j = 500000000/siz;
         data4.siz=siz; 
             }

         gettimeofday(&t1,&z);       
    //  printf("\nStart time in micro sec. : %d\n",t1.tv_usec);   
         pthread_create (&thread1, NULL, (void *) & rwreadths, (void *) &data1);
         pthread_create (&thread2, NULL, (void *) & rwreadths, (void *) &data2);
         if(th==4)
          {pthread_create (&thread1, NULL, (void *) & rwreadths, (void *) &data3);
           pthread_create (&thread2, NULL, (void *) & rwreadths, (void *) &data4);
         }
         pthread_join(thread1, NULL);
         pthread_join(thread2, NULL);
         gettimeofday(&t2,&z);
         r=t2.tv_usec-t1.tv_usec;
         printf("%ld\n",r);  
         speed=500000000/r;
         latency=(r*siz)/500000000;
         printf("\nspeed:%f MB/s,latency:%f ms.\n",speed,latency);
      
        }
      

    }
file_read(int i)
{     int sizof;
        FILE  *fp,*fw;
              float m;
        m=500000000;      
        sizof=m/i;
        char *ch=(char*)calloc(sizof,i);
        fp=fopen("my.txt","r");
        fread(ch,i,sizof,fp);         
        fclose(fp);
}
file_write(int i)
{int sizof;
        FILE  *fw;
              float m;
        m=500000000;      
        sizof=m/i;
        char *ch=(char*)calloc(sizof,i);
        fw=fopen("to.txt","w");
        fwrite(ch,i,sizof,fw);         
        fclose(fw);

}

r_file_read(int i)
{       int sizof;
        FILE  *fp,*fw;
           int m;
        int k=0;
int j=0;
               m=500000000;      
               sizof=m/i;
               char *ch=(char*)calloc(sizof,i);
               fp=fopen("my.txt","r");
               for(k=0;k<sizof;k++)
                {  j = rand()%sizof;
                  fseek( fp, j, SEEK_SET );
                 fread(ch,i,1,fp);
                 }         
                fclose(fp);
}
r_file_write(int i)
       {int sizof;
        FILE  *fw;
              int m;
              int j,k;
        m=500000000;      
        sizof=m/i;
        char *ch=(char*)calloc(sizof,i);
        fw=fopen("to.txt","w");
for(k=0;k<sizof;k++)         
{  
    j = rand()%sizof;
    fseek(fw, j, SEEK_SET );
    fwrite(ch,j,1,fw);         
} 
 fclose(fw);
}



