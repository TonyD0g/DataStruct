#include<stdio.h>
#include<stdlib.h>
#define maxsize 6
//int Qjiaoji(xs *sqlist1,xs *sqlist2,xs *sqlist3);
//int Qjiaoji1(xs *sqlist1,xs *sqlist2);
void handle1(struct xs *sqlist1,struct xs *sqlist2,struct xs *sqlist3);
void operation1();
void operation2();
struct xs
{
	int a[maxsize];
	int length;
};
int main()
{
		
	operation1();//用线性表操作
	operation2();//不用线性表操作
	return 0;
}
void operation2()
{

	int i,j,x,n;
	struct xs sqlist1,sqlist2,sqlist3;
	sqlist1.length=0;
	sqlist2.length=0;
	sqlist3.length=0;
	printf("操作2:\n");
	printf("录入的集合1元素数:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&sqlist1.a[i]);
		sqlist1.length++;
	}
	printf("-----\n");
	printf("录入的集合2元素数:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&sqlist2.a[i]);
		sqlist2.length++;
	}
	for(i=0;i<sqlist1.length;i++)
	{
		for(j=0;j<sqlist2.length;j++)
		
			if(sqlist1.a[i]==sqlist2.a[j])
			{
				if(sqlist3.length!=0)
				{for(x=0;x<sqlist3.length;x++)
					if(sqlist1.a[i]==sqlist3.a[x])
						break;
					else
					{	if(sqlist3.length!=maxsize-1)
						{	sqlist3.a[sqlist3.length]=sqlist1.a[i];
							sqlist3.length++;
						}
						else  printf("集合3已满！\n");
					}
				}
				else
				{	sqlist3.a[sqlist3.length]=sqlist1.a[i];
					sqlist3.length++;
				}
			}
		
	}
	printf("交集为：");
	for(i=0;i<sqlist3.length;i++)
	printf("%d ",sqlist3.a[i]);
	printf("\n");
}
void operation1()
{
		int i,n;
struct xs sqlist1,sqlist2,sqlist3;
	sqlist1.length=0;
	sqlist2.length=0;
	sqlist3.length=0;
	printf("操作1:\n");
	printf("录入的集合1元素数:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&sqlist1.a[i]);
		sqlist1.length++;
	}
	printf("-----\n");
	printf("录入的集合2元素数:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&sqlist2.a[i]);
		sqlist2.length++;
	}
	printf("-----\n");
	handle1(&sqlist1,&sqlist2,&sqlist3);
	printf("交集为：");
	for(i=0;i<sqlist3.length;i++)
	printf("%d ",sqlist3.a[i]);
	printf("\n");
}
void handle1(struct xs *sqlist1,struct xs *sqlist2,struct xs *sqlist3)
{
	int i,j,x;
	for(i=0;i<sqlist1->length;i++)
	{
		for(j=0;j<sqlist2->length;j++)
		
			if(sqlist1->a[i]==sqlist2->a[j])
			{
				if(sqlist3->length!=0)
				{for(x=0;x<sqlist3->length;x++)
					if(sqlist1->a[i]==sqlist3->a[x])
						break;
					else
					{	if(sqlist3->length!=maxsize-1)
						{	sqlist3->a[sqlist3->length]=sqlist1->a[i];
							sqlist3->length++;
						}
						else  printf("集合3已满！\n");
					}
				}
				else
				{	sqlist3->a[sqlist3->length]=sqlist1->a[i];
					sqlist3->length++;
				}
			}
		
	}
}
