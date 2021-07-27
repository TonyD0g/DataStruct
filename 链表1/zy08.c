#include<stdio.h>
#define maxsize 20
void Qbingji(struct xs *sqlist1);
void Qbingji1(struct xs *sqlist1);
void dele(struct xs *sqlist1,int *j);

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
	for(i=0;i<sqlist2.length;i++)
	{	sqlist1.a[sqlist1.length]=sqlist2.a[i];
		sqlist1.length++;
	}
	Qbingji(&sqlist1);
	printf("\n");
	Qbingji1(&sqlist1);
}
void Qbingji1(struct xs *sqlist1)
{
	int i,j,w;
	printf("Qbingji1:");
	for(i=0;i<sqlist1->length;i++)
	{
		for(j=i+1;j<sqlist1->length;j++)
		{
			if(sqlist1->a[i]==sqlist1->a[j])
			{	
				for(w=j;w<sqlist1->length;w++)
				{	sqlist1->a[w]=sqlist1->a[w+1];
					sqlist1->length--;
				}
			}
		}
	}
		for(i=0;i<sqlist1->length;i++)
		printf("%d ",sqlist1->a[i]);
}
void Qbingji(struct xs *sqlist1)
{
	int i,j;
	printf("Qbingji:");
	for(i=0;i<sqlist1->length;i++)
	{
		for(j=i+1;j<sqlist1->length;j++)
		{
			if(sqlist1->a[i]==sqlist1->a[j])
				dele(sqlist1,&j);
		}
	}
		for(i=0;i<sqlist1->length;i++)
		printf("%d ",sqlist1->a[i]);
}
void dele(struct xs *sqlist1,int *j)
{
	int i;
	for(i=*j;i<sqlist1->length;i++)
		sqlist1->a[i]=sqlist1->a[i+1];
	sqlist1->length--;
	
}
