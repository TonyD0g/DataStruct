#include<stdio.h>
#define maxsize 20
void Q1(struct xs *sqlist1);
void Q2(struct xs *sqlist1);
void dele(struct xs *sqlist1,int *j);
void sort(struct xs *sqlist1);
struct xs
{
	int a[maxsize];
	int length;
};
void main()
{
	int i;
	struct xs sqlist1,sqlist2;
	sqlist1.length=0;
	sqlist2.length=0;
	for(i=0;i<9;i++)
	{
		sqlist1.a[i]=i*i;
		sqlist1.length++;
	}
	for(i=0;i<9;i++)
	{	sqlist2.a[i]=i;
		sqlist2.length++;
	}
				printf("Q1和Q2的初始化：\n");
				for(i=0;i<sqlist1.length;i++)
				printf("%d ",sqlist1.a[i]);printf("\n");
				for(i=0;i<sqlist2.length;i++)
				printf("%d ",sqlist2.a[i]);
				printf("\n");
	printf("开始合并：\n");
	for(i=0;i<sqlist2.length;i++)
	{	sqlist1.a[sqlist1.length]=sqlist2.a[i];
		sqlist1.length++;
	}
	Q1(&sqlist1);
	printf("\n");
	Q2(&sqlist1);
}
void Q2(struct xs *sqlist1)
{
		int i,j,w,t;
	printf("不操作自定义函数:");
	for(i=0;i<sqlist1->length;i++)
	{
		for(j=i+1;j<sqlist1->length;j++)
		{
			if(sqlist1->a[i]==sqlist1->a[j])
			{			for(w=j;w<sqlist1->length;w++)
						sqlist1->a[w]=sqlist1->a[w+1];
						sqlist1->length--;
			}
		}
	}
	for(i=0;i<sqlist1->length;i++)
	for(j=i+1;j<sqlist1->length;j++)
	if(sqlist1->a[i]>sqlist1->a[j])
	{	t=sqlist1->a[i];
		sqlist1->a[i]=sqlist1->a[j];
		sqlist1->a[j]=t;
	}
	for(i=0;i<sqlist1->length;i++)
		printf("%d ",sqlist1->a[i]);
}
void sort(struct xs *sqlist1)
{
	int i,j,t;
	for(i=0;i<sqlist1->length;i++)
	for(j=i+1;j<sqlist1->length;j++)
	if(sqlist1->a[i]>sqlist1->a[j])
	{	t=sqlist1->a[i];
		sqlist1->a[i]=sqlist1->a[j];
		sqlist1->a[j]=t;
	}
	for(i=0;i<sqlist1->length;i++)
		printf("%d ",sqlist1->a[i]);
}
void Q1(struct xs *sqlist1)
{
	int i,j;
	printf("操作自定义函数:");
	for(i=0;i<sqlist1->length;i++)
	{
		for(j=i+1;j<sqlist1->length;j++)
		{
			if(sqlist1->a[i]==sqlist1->a[j])
				dele(sqlist1,&j);
		}
	}
		sort(sqlist1);
}
void dele(struct xs *sqlist1,int *j)
{
	int i;
	for(i=*j;i<sqlist1->length;i++)
		sqlist1->a[i]=sqlist1->a[i+1];
	sqlist1->length--;
	
}
