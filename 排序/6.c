#include<stdio.h>
#include<time.h>
void mpsort(int r[],int n)
{
	int i,j,exchange,t;
	for(i=1;i<=n-1;i++)
	{
		exchange=0;
		for(j=1;j<=n-1;j++)
		{
			if(r[j]>r[j+1])
			{
				t=r[j];
				r[j]=r[j+1];
				r[j+1]=t;
				exchange=1;
			} 
		}
		if(exchange==0)
			return;
	}
}

void fun(char s[])
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	printf("%s\n",s);
	printf("%s",asctime(timeinfo));
}

void main()
{
	int a[]={10,73,56,2,15,9,12,8,67,18,7},i;
	mpsort(a,10);
	for(i=1;i<=10;i++)
		printf(" %d",a[i]);
	printf("\n");	
	fun("简单选择排序程序实现");
}
