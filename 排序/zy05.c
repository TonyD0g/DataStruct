#include "stdio.h"
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
void BinSort(int r[], int n)
{
	int low, high, mid, i, j;
	for (i=2; i<=n ;i++)
		{
			if(r[i]<r[i-1])
			{
				r[0]=r[i];//放要插入的元素 
				low=1;
				high=i-1;
				while (low<=high)
				{
					mid=(low+high)/2;

					if (r[0]<r[mid])
					 high=mid-1;

					else 
					low=mid+1;

				}//循环结束时low>high交叉, low指向大于r[0]的第一数

				for (j=i-1; j>=low; j--)
				{
				r[j+1]=r[j];
				}
				r[low]=r[0];
}	}}
void main()
{
int a[11]={76,33,52,27,1,98,12,88,67,187,75},i;
 printf("初始化：\n");
  for(i=0;i<11;i++)
  {
    printf("%d ",a[i]);
  }
  printf("\n结果为：");

BinSort (a, 10);

for (i=1; i<=10;i++)

printf (" %d",a[i]);

printf ("\n");
	fun("编程实现快速排序实现"); 
}