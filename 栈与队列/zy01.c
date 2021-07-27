#include<stdio.h>//后进先出
#define maxsize 10
typedef struct xs
{
	int top;
	int data[maxsize];
}stack1;
int main()
{
	stack1 p;int n,j,i;
	p.top=-1;
	printf("请输入个数\n");
	scanf("%d",&n);printf("-----\n");
	for(i=0;i<n;i++)
	{
		if(p.top==maxsize-1){printf("栈最多装10个!\n");break;	}
		p.top=p.top+1;
		scanf("%d",&p.data[p.top]);
		
	}printf("依次出栈:\n");
	while(p.top!=-1)
	{
		printf("%d ",p.data[p.top]);
		p.top=p.top-1;
	}
	return 0;

}