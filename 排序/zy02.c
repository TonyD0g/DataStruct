#include<stdio.h>
#include "time.h" 
void fun(char s[]) 
{ 
time_t rawtime; 
struct tm * timeinfo; 
time ( &rawtime ); 
timeinfo = localtime ( &rawtime ); 
printf("%s\n",s); 
printf("%s", asctime (timeinfo) ); 
} 
void mpsort(int r[],int n)
{
	int i,j,bz,t;
	for(i=1;i<=n-1;i++)
	{
		bz=0;
		for(j=0;j<=n-2;j++)
		
			if(r[j]>r[j+1])  
			{
				t=r[j];
				r[j]=r[j+1];
				r[j+1]=t;
				bz=1;
			}
		
	}
	if(bz==0)
		return;
}


void main()
{
	int a[10]={3,5,2,6,8,7,9,1,4,2},i;
	printf("初始化：\n");
	for(i=0;i<10;i++)
		printf("%d ",a[i]);
	printf("\n-------------------\n结果为:");
	mpsort(a,10);
	for(i=0;i<=9;i++)
		printf("%d ",a[i]);
	printf("\n");
	fun("编程实现冒泡排序实现"); 
}
