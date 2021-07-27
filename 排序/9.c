#include <stdio.h>
#include "stdlib.h"
#include <time.h>
int getDigit(int i,int d)//d：_位数
{
	int val;
	while (d--)
	{
		val=i%10;
		i/=10;
	}
	return val;
}
void fun1(char s[])
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	printf("%s\n",s);
	printf("%s",asctime(timeinfo));
}

void RadixSort(int *list,int n,int digit)
{
	int radix=10; //基数
	int i=0,j=0,d;
	int *count=(int*)malloc(radix*sizeof(int));
	int *bucket=(int*)malloc(n*sizeof(int)) ;
	for(d=1;d<=digit;d++)
	{
		for(i=0;i<radix;i++)
			count[i]=0;
		for(i=0;i<=n-1;i++)

		{
			j=getDigit(list[i],d);
			count[j]++;
		}
		for(i=1;i<radix;i++) 
			count [i]=count[i]+count[i-1];
		for(i=n-1;i>=0;i--)//分配
		{
			j=getDigit(list[i],d);
			bucket[count[j]-1]=list[i];
			count[j]--;
		}
		for(i=0,j=0;i<=n-1;i++,j++)//收集
			list[i]=bucket[j];
	}
	free(count);
	free(bucket) ;
}
void main()
{
	int i,a[10]={378,119,630,930,589,457,505,269,84,89};
	RadixSort(a,10,3);
	for(i=0;i<10;i++)
		printf("%d ",a[i]);

	printf("\n");
	fun1("基数排序程序实现");
}
