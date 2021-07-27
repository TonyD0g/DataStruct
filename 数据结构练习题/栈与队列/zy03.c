#include<stdio.h>
#include<stdlib.h>
#define maxsize 20 
/*迷宫定义：{1,1,1,1,1,1}	a0
　　　　　　{1,2,2,3,1,1}	a1,(1,1)~(4,4)
　　　　　　{1,0,1,1,1,1}	a2
　　　　　　{1,0,0,0,0,1}	a3
　　　　　　{1,0,0,0,0,1}	a4
　　　　　　{1,1,1,1,1,1}	a5
*/
typedef struct xs
{
	int top;
	int data1[maxsize];//存储i；
	int data2[maxsize];//存储j；
}stack1;
int a[6][6]={{1,1,1,1,1,1},{1,0,0,0,1,1},{1,0,1,1,1,1},{1,0,0,0,0,1},{1,0,0,0,0,1},{1,1,1,1,1,1}};
void option1()
{	int i=1,j=1;
	stack1 p;p.top=-1;
	//默认方向为 "向右";
					//(i=1,j=1);
	p.top=p.top+1;	p.data1[p.top]=i;p.data2[p.top]=j;a[i][j]=2;
	while(i<4&&j<=4)
{	if(a[i][j+1]==0)
	{	p.top=p.top+1;
		p.data1[p.top]=i;p.data2[p.top]=j+1;//right
		a[i][j+1]=2;i=i;j=j+1;
		
	}
	else
	{
		if(a[i+1][j]==0)
		{p.top=p.top+1;
			p.data1[p.top]=i+1;p.data2[p.top]=j;//down
			a[i+1][j]=2;i=i+1;j=j;
		}
		else
		{
				if(a[i][j-1]==0)
			{	p.top=p.top+1;
				p.data1[p.top]=i;p.data2[p.top]=j-1;//left
				a[i][j-1]=2;i=i;j=j-1;
				
			}
				else
				{
					if(a[i-1][j]==0)//up
					{p.top=p.top+1;	p.data1[p.top]=i-1;p.data2[p.top]=j;a[i-1][j]=2;i=i-1;j=j;}
					else
					{
						p.top=p.top-1;//出栈，不要了
						a[i][j]=3;i=p.data1[p.top];j=p.data2[p.top];
					}
				}

		}
	}
}
	printf(" 结果：\n");
	for(i=0;i<6;i++)
	{
		for(j=0;j<6;j++)
		printf("%d ",a[i][j]);printf("\n");
	}
	printf("已到达！\n");
}
int main()
{	int i,j;
	printf("迷宫定义:\n");
	for(i=0;i<6;i++)
	{
		for(j=0;j<6;j++)
		printf("%d ",a[i][j]);printf("\n");
	}
	printf("\n--------------\n");
	option1();
	return 0;
}