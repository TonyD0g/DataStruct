#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>
typedef struct xs{
	int data;
	int *next;
}link;

link* init();//初始化
void initlist(link *hd,int n);
void insert(link *hd,int n);
link* search(link *hd,int n);
void dele(link *hd,int n);
void display(link *hd);
void deleall(link *hd);
int main()
{	
	int n;
	link *hd=NULL;
	hd=init();
	printf("请输入初始链表的长度\n");
	scanf("%d",&n);
	initlist(hd,n);
	printf("请输入你要插入的节点位置：\n");//bug
	scanf("%d",&n);
	insert(hd,n);
	printf("请输入你要删除的节点位置：\n");
	scanf("%d",&n);
	dele(hd,n);
	printf("链表清空操作执行\n");
	deleall(hd);
	return 0;
}
void deleall(link *hd)
{
	link *p,*q;
	p=hd->next;
	while(p)
	{
		q=p->next;
		free(p);
		p=q;
	}
	hd->next=NULL;
	display(hd);

}
void display(link *hd)
{
	link *p=hd;
	printf("操作结果：");
	while(p->next)
	{
		p=p->next;
		printf("%d ",p->data);
	}
	printf("\n");
}
void dele(link *hd,int n)
{
	link *q,*p;
	p=search(hd,n-1);
	q=p->next;
	p->next=q->next;
	free(q);
	printf("haven delete!\n");
	display(hd);
}
link* search(link *hd,int n)
{
	int i=0;
	link *p;
	p=hd;
	while(p&&i<n)
	{	p=p->next;
		i++;
	}
	if(!p||i>n)
		return -1;
	return p;

}
void insert(link *hd,int n)
{
	int c;
	link *p,*s;
	p=search(hd,n-1);
	s=(link *)malloc(sizeof(link));
	printf("请输入要插入的元素数据:\n");
	scanf("%d",&c);
	s->data=c;
	s->next=p->next;
	p->next=s;
	display(hd);
}
void initlist(link *hd,int n)
{
	int i;
	link *p;
		for(i=0;i<n;i++)
	{
		p=(link *)malloc(sizeof(link));
		p->data=i;
		p->next=hd->next;
		hd->next=p;
	}
		display(hd);
}
link* init()
{
	link *hd=(link *)malloc(sizeof(link));
	hd->next=NULL;
	return  hd;
}
