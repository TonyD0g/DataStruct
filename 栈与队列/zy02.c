#include<stdio.h>//后进先出
#define maxsize 10
typedef struct xs
{
	int top;
	int data[maxsize];
}stack1;
void option(stack1 *p,int x,int y)//x：要处理的数字，y：进制数字 
{
	int i,j;
	while(j!=0)
	{	i=x%y;
		j=x/y;x=j;
		p->top=p->top+1;
		p->data[p->top]=i;
	
	}printf("其对应的%d进制数为：",y);printf("\n");
	while(p->top!=-1)
	{
		printf("%d",p->data[p->top]);
		p->top=p->top-1;
	}
	printf("\n");
}
int main()
{
	stack1 p;int n,j,i;
	p.top=-1;
	printf("请输入一个十进制正整数：");
	scanf("%d",&n);
	option(&p,n,2);
	option(&p,n,8);
	option(&p,n,16);
	return 0;

}