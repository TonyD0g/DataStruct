#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
int insert(struct xs *sqlist);//插入
int newer(struct xs *sqlist);//初始化
int dele(struct xs *sqlist);//删除
int display(struct xs *sqlist);//遍历显示
void clear(struct xs *sqlist);//清空
struct xs{
	int a[maxsize];
	int length;
};
int main()
{
	struct xs sqlist; 
	int y,w,d,dis;
	sqlist.length=0;
		w=newer(&sqlist);
		y=insert(&sqlist);
		d=dele(&sqlist);
		display(&sqlist);
		clear(&sqlist);
	return 0; 
}
void clear(struct xs *sqlist)
{
	int i,n;
	sqlist->length=0;
	printf("线性表已被清空！\n");
}
int display(struct xs *sqlist)
{
	int i;
	if(sqlist->length<1)
	{
		return printf("\n The sqlist is no existence!\n");
	}
	for(i=0;i<sqlist->length;i++)
	{
		printf("%d ",sqlist->a[i]);
	}
	printf("\n");
}
int dele(struct xs *sqlist)
{
	int i,x,n;
	printf("你要删除几号元素？\n");
	scanf("%d",&x);
	if(x>sqlist->length||x<1)
		return printf("error!\n");
	if(x<sqlist->length)
	{
		for(i=x;i<sqlist->length;i++)
			sqlist->a[i-1]=sqlist->a[i];
	}
	sqlist->length--;
}
int newer(struct xs *sqlist)
{
	int i;
	for(i=0;i<5;i++)
	{
		printf("%d ",sqlist->a[i]=i*i);
		sqlist->length=sqlist->length+1;
	}
	printf("\n");
	return 0;
}
int insert(struct xs *sqlist)
{ 
	int i,elem,loc;
	printf("请输入你要插入的元素和位置\n");
	scanf("%d %d",&elem,&loc);
	if(loc<1||loc>sqlist->length+1)
		return printf("error!\n");
	if(sqlist->length==maxsize)
		return printf("error!\n");
	if(loc<=sqlist->length)
	{
		for(i=sqlist->length;i>=loc-1;i--)
		{
			sqlist->a[i+1]=sqlist->a[i];
		}
	}
	sqlist->a[loc-1]=elem;
	sqlist->length=sqlist->length+1;
		for(i=0;i<sqlist->length;i++)
	{
		printf("%d ",sqlist->a[i]);
	}
		printf("\n");
	return 0;
}

