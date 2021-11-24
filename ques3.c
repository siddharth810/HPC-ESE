%%cu
#include<stdio.h>
#include<cuda.h>
__global__ void matadd(int *l,int *m, int *n)
{
    int x=blockIdx.x;
    int y=blockIdx.y;
    int id=gridDim.x * y +x;
    n[id]=l[id]+m[id];
}
int main()
{
    int a[2][3];
    int b[2][3];
    int c[2][3];
    int *d,*e,*f;
    int i,j;
    printf("\n Matrix 1:\n");
    for(i=0;i<2;i++)
    {
        for(j=0;j<3;j++)
            {
            	a[i][j]=i+j;
            	printf("%d\t",a[i][j]);
               
            }
            printf("\n");
            
    }
    printf("\n  Matrix 2:\n");
        for(i=0;i<2;i++)
        {
            for(j=0;j<3;j++)
                {
                	b[i][j]=2*i+j;
                	printf("%d\t",b[i][j]);
                	
                	
                    //scanf("%d",&b[i][j]);
                }
                printf("\n");
        }
    cudaMalloc((void **)&d,2*3*sizeof(int));
    cudaMalloc((void **)&e,2*3*sizeof(int));
    cudaMalloc((void **)&f,2*3*sizeof(int));
 cudaMemcpy(d,a,2*3*sizeof(int),cudaMemcpyHostToDevice);
 cudaMemcpy(e,b,2*3*sizeof(int),cudaMemcpyHostToDevice);
    
dim3 grid(3,2);

    matadd<<<grid,1>>>(d,e,f);

 cudaMemcpy(c,f,2*3*sizeof(int),cudaMemcpyDeviceToHost);
    printf("\nSum = Matrix 1 + Matrix 2 :\n ");
    for(i=0;i<2;i++)
    {
        for(j=0;j<3;j++)
        {
              printf("%d\t",c[i][j]);
        }
        printf("\n");
    }
    cudaFree(d);
    cudaFree(e);
    cudaFree(f);
    return 0;
}
