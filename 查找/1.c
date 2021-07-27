#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define maxsize 20
void fun(char s[])
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	printf("%s\n",s);
	printf("%s",asctime(timeinfo));
}
int main()
{	int i,n,x,a[maxsize];
//int high,mid,low;
printf("请输入n的数量\n");
scanf("%d",&x);//	high=x;low=0;
	for(i=1;i<x+1;i++)
	{
		scanf("%d",&a[i]);	
	}
	printf("请输入你想要查找的数字\n");
	scanf("%d",&n);	a[0]=n;i=n;
		while(a[i]!=n)
		{
			i--;
		}
		if(i==0)printf("查找失败\n");else
		{	printf("查找成功!\n");printf("该元素在数组下标为%d\n",i);}
		fun("折半查找算法");
	
}