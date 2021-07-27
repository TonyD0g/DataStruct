#include<stdio.h>
#define maxsize 6
//void fun(int r[],int n,int p);
void reverse(struct xs *sqlist,int left,int right,int n);
void fun(struct xs *sqlist,int p,int n);
struct xs{
	int a[maxsize];
};
int main()
{

	int p,i,n;
	struct xs sqlist1;
	printf("请输入n的值：");
	scanf("%d",&n); 
	for(i=0;i<n;i++)
	{
		scanf("%d",&sqlist1.a[i]);
	}
	printf("----\n请输入p的值:");
	scanf("%d",&p);
	if(p>n)
		return 0;
	fun(&sqlist1,p,n);
	return 0;
}
void fun(struct xs *sqlist1,int p,int n)
{
	int i;
	reverse(sqlist1,0,n,n);
	reverse(sqlist1,0,n-p,n);
	reverse(sqlist1,n-p,n,n);

	for(i=0;i<n;i++)
	{
		printf("%d ",sqlist1->a[i]);
	}
}
void reverse(struct xs *sqlist1,int left,int right,int n)
{
	int i,j;
	struct xs sqlist2;
	for(i=left;i<right;i++)
	{
		sqlist2.a[right-i-1]=sqlist1->a[i];//1,2
	}
	j=left;
	for(i=0;i<right-left;i++)
	{
		sqlist1->a[j]=sqlist2.a[i];
		j++;
	}
}