#include<stdio.h>//后进先出
#include<stdlib.h>
#define maxsize 10
typedef struct xs
{
	int front,rear;
	int data[maxsize];
}queue1;
int main()
{	int n,i;
	queue1 *p;
	p=(queue1 *)malloc(sizeof(queue1));p->front=0;p->rear=0;
	printf("请输入元素个数\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)//进队列
	{
		if((p->rear+1)%maxsize==p->front){printf("队列已满！\n");break;	}
		p->data[p->rear]=i;
		p->rear=(p->rear+1)%maxsize;
	}
	printf("队列的长度为：%d\n",(maxsize-p->front+p->rear)%maxsize);
	printf("出队列的第一个元素：\n");
	printf("%d\n-------\n",p->data[p->front]);
	p->front=(p->front+1)%maxsize;
	printf("队列清空：\n");
	while(p->front!=p->rear)//队列清空
	{
		printf("%d ",p->data[p->front]);
		p->front=(p->front+1)%maxsize;
	}
	printf("\n");
	printf("空间释放：\n");
	free(p);
}