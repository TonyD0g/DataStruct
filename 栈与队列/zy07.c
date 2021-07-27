#include<stdio.h>
#include<stdlib.h>
typedef struct xs
{
	int data;
	struct xs *next;
}node,*link;
typedef struct 
{
	link front,rear;
}queue1;
void initqueue1(queue1 *p)
{
	p->front=p->rear=(link)malloc(sizeof(node));
	p->front->next=NULL;	
}
void inqueue1(queue1 *p)//进队
{
	node *s;int n,i;
	printf("输入进队元素个数:\n");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		s=(node *)malloc(sizeof(node));
		s->data=i;s->next=NULL;
		p->rear->next=s;
		p->rear=s;
	}
	printf("进队完毕！\n");
}
void visit(queue1 *p)
{
	node *s;
		s=p->front->next;
	while(s)
	{		printf("%d ",s->data);
			s=s->next;
	}
	
}
int outqueue1(queue1 *p)
{	
	node *s;
	if(p->front==p->rear)return 0;//队列已空
	printf("开始出队操作;\n");
	s=p->front->next;
	p->front->next=s->next;
	if(s==p->rear){p->rear=p->front;}
	printf("队列的第一个元素%d已出队\n",s->data);
	free(s);
	printf("出队结果:\n");
	visit(p);
	return 1;
}
void clearqueue1(queue1 *p)
{node *s;
	while(p->front!=p->rear)
	{
		s=p->front->next;
		p->front->next=s->next;
		if(s==p->rear){p->rear=p->front;}
		free(s);
	}
	printf("链队列已清空！\n");
	visit(p);
}
void lenght(queue1 *p)
{	node *s;int i=0;s=p->front->next;
	while(s)
	{
		i++;
		s=s->next;
	}
	printf("链队列长度为：%d\n",i);
}
int main()
{
	queue1 p;int i;
	initqueue1(&p);
	inqueue1(&p);//进队	
	lenght(&p);
	visit(&p);//遍历
	i=outqueue1(&p);//出队
	printf("\n");
	if(i==0)printf("队列已空！\n");
	clearqueue1(&p);//清空
	return 0;
}