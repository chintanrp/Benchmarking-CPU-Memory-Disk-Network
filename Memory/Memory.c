#include <stdio.h>      
#include <stdlib.h>
#include <unistd.h>    
#include <sys/types.h> 
#include <pthread.h>    
#include <string.h>     
#include <sys/time.h>  
#include <errno.h>      
     

typedef struct str_thdata
{
    char *c;
    char *temp;
    int i,j,type;
} thdata;
void thread_start ( void *ptr )
{
    thdata *data;      
    data = (thdata *) ptr;  
    long k = 0;
    while(data->i < data->j)
    {
        k = (long)data->i;
        if(data->type == 2) {
            k = rand()%(data->j);
        }
        memset((data->c + k),'s',1);
        (data->i)++;
    }
    while(data->i < data->j)
    {
        k = (long)data->i;
        if(data->type == 2) {
            k = rand()%(data->j);
        }
        data->temp = strchr((data->c + k), '1');
        (data->i)++;
    }
    pthread_exit(0); /* exit */
}


int main()
{
    struct timeval t1,t2;
    struct timezone z;
    pthread_t thread1, thread2;  
    thdata data1, data2;         /* structs to be passed to threads */
    int t,b;
    long itr,r = 0;
    printf("Enter Block size (1B, 1KB, 1MB): ");
    scanf("%d",&b);
    printf("\nEnter Number of Thread (1 or 2): ");
    scanf("%d",&t);
    printf("\nEnter Number of iteration : ");
    scanf("%ld",&itr);
    printf("\nPress 1.>Sequential or 2.>Random : ");
    scanf("%d",&data1.type);
    data2.type = data1.type;
    if(t==1) {
        data1.c = (char*)malloc(b);
        data1.i = 0;
        data1.j = itr;
        gettimeofday(&t1,&z);
        pthread_create (&thread1, NULL, (void *) &thread_start, (void *) &data1);
        gettimeofday(&t2,&z);
        free(data1.c);
        r=t2.tv_usec-t1.tv_usec;
    }else if(t==2) {

    data1.c=(char*)malloc(b);
    data1.i = 0;
    data1.j = itr/2;
   
    
    data2.c=(char*)malloc(b);
    data2.i = itr/2;
    data2.j = itr;
    
    
    gettimeofday(&t1,&z);   
    //printf("\nStart time in micro sec. : %d\n",t1.tv_usec);   
    pthread_create (&thread1, NULL, (void *) &thread_start, (void *) &data1);
    pthread_create (&thread2, NULL, (void *) &thread_start, (void *) &data2);

    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    gettimeofday(&t2,&z);    
    //printf("\nEnd time in micro sec. : %d\n",t2.tv_usec);
    free(data1.c);
    free(data2.c);
    r=t2.tv_usec-t1.tv_usec;
    }
    printf("Time in useconds : %ld\n",r);
  float t_millisecond = (float)r/1000;
  float t_second = (float)t_millisecond/1000;
  printf("Latency in milliseconds : %.12f\n",(t_millisecond)/itr);
  float th = (float)(b/t_second);
  if(b==1) {
     printf("Throughput in MB/sec : %f\n",th);
  } else if(b==1000) {
    printf("Throughput in MB/sec : %f\n",th/1000);
  } else {
    printf("Throughput in MB/sec : %f\n",th/1000000);
  }
  
       
    exit(0);
} 

