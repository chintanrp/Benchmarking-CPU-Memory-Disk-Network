#include <stdio.h>

__global__ void MyKernel() {
}
__global__ void MyKernelFlops(float n, float a, float b, float c) {
  int i =0;
  while (i<n) {
    a+=b*c;
    i++;
  }
}
__global__ void MyKernelIops(int n, int a, int b, int c) {
  int i =0;
  while (i<n) {
    a+=b*c;
    i++;
  }
  
}

void measureInIops() {
  int n = 1000000;
  cudaEvent_t start, stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);
  cudaEventRecord(start);
  MyKernelIops<<<2, 1024>>>(n, 2, 3, 6);
  cudaEventRecord(stop);
  cudaEventSynchronize(stop);
  float milliseconds = 0;
  cudaEventElapsedTime(&milliseconds, start, stop);
  printf("\nTime in milliseconds : %f",milliseconds);
  float giops = (n*1)/milliseconds/1e6;
  printf("\nGIOPS : %f",giops);
}

void measureInFlops() {
  int n = 1000000;
  cudaEvent_t start, stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);
  cudaEventRecord(start);
  MyKernelFlops<<<2, 1024>>>(n, 2.1f, 3.5f, 6.0f);
  cudaEventRecord(stop);
  cudaEventSynchronize(stop);
  float milliseconds = 0;
  cudaEventElapsedTime(&milliseconds, start, stop);
  printf("\nTime in milliseconds : %f",milliseconds);
  float gflops = (n*1)/milliseconds/1e6;
  printf("\nGFLOPS : %f",gflops);
}
int main(void)
{
  int n, type ;
  float *d_a, *d_b;
  printf("Please select from below options :\n1 -> Measure GPU Speed \n2 -> Measure memory bandwidth \n --> : ");
  scanf("%d",&type);
  if(type == 1) {
    int m;
    printf("Please select from below options :\n1 -> Measure in GIOPS \n2 -> Measure in GFLOPS \n --> : ");
    scanf("%d",&m);
    if(m==1) {
     measureInIops();
    } else if(m == 2) {
     measureInFlops();
    }
  }else if(type == 2) {
    printf("Enter Block size : ");
    scanf("%d",&n);
  
    cudaMalloc(&d_a, n); 
    cudaMalloc(&d_b, n);
  
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
  
    cudaMemcpy(d_a, d_b, n, cudaMemcpyDeviceToDevice);
    
    cudaEventRecord(start);
  
    MyKernel<<<2, 1024>>>();
  
    cudaEventRecord(stop);
  
    cudaEventSynchronize(stop);
    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);
  
    printf("Bandwidth (GB/s): %fn", n*4/milliseconds/1e6);
  }
}