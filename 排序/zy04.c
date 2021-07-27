#include"stdio.h"
#include "time.h"
void inssort (int r[],int n)
{
	int i,j;
	for(i=2;i<=n;i++)
	{
		if(r[i]<r[i-1])
		{
			r[0]=r[i];
			r[i]=r[i-1];
			j=i-2;
			while(r[j]>r[0])
			{
			r[j+1]=r[j];
			j--;
			}
			r[j+1]=r[0];
		}
	}
}
 
void fun(char s[]) 
{ 
time_t rawtime; 
struct tm * timeinfo; 
time ( &rawtime ); 
timeinfo = localtime ( &rawtime ); 
printf("%s\n",s); 
printf("%s", asctime (timeinfo) ); 
} 
void main()
{
	int a[11]={6,33,54,25,16,93,12,80,18,7,55},i;
	printf("初始化：\n");
  for(i=0;i<11;i++)
  {
    printf("%d ",a[i]);
  }
  printf("\n结果为：");
	inssort(a,10);
	for(i=1;i<=10;i++)
		printf(" %d",a[i]);
	printf(" \n");
		fun("网安B203朱晋宏的编程实现直接插入排序"); 
}