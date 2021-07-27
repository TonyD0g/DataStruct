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
int high,mid,low;
printf("请输入n的数量\n");
scanf("%d",&x);	high=x;low=0;
	for(i=0;i<x;i++)
	{
		scanf("%d",&a[i]);	
	}
	printf("请输入你想要查找的数字\n");
	scanf("%d",&n);
		while(low<=high)
	{	
			//if(a[low]=n){printf("%d",low);break;}if(a[high]=n){printf("%d",high);break;}
		mid=(high+low)/2;
		if(a[mid]>n)
		{
			high=mid-1;
		}
		else
			if(a[mid]<n)
			low=mid+1;
		else
			if(a[mid]=n)
			{	printf("查找的元素在数组中的下标为%d\n",mid); break;}
	}
	
		fun("折半查找算法");
	
}