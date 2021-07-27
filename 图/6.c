#include "stdio.h" 
#include "stdlib.h"
#include <time.h>
#define VEXNUM 6
#define ARCNUM 10
#define INF 9999    //无穷大
struct Graph        //通用图形定义，用于创建图形的邻接矩阵和邻接表-全局变量
{
	int vexnum,arcnum,kind;//顶点数、边数、图类型：1234-无向图、有向图、无向网、有向网
	char vexs[VEXNUM+1];   //顶点字符数组
	int arcs[ARCNUM*3];     //边起止点下标及权值数组
} graph={5,7,4,"ABCDEF",{0,4,100,0,3,30,0,1,10,1,2,50,2,4,10,3,4,60,3,2,20}};
//6个顶点、10条边、无向网、顶点依次为ABCDEF、A-B:6/A-C:1/A-D:5/B-C:5/B-E:3/C-E:6/C-F:4/C-D:5/D-F:2/E-F:6
struct MGraph_Mat      //图的邻接矩阵存储数据定义
{
	int vexnum,arcnum;//顶点数、边数
	char vexs[VEXNUM];//顶点数组
	int arcs[VEXNUM][VEXNUM];//邻接矩阵
	int kind;                //图类型
};
void create_Mat(struct MGraph_Mat *g)
{
	int i,j;
	g->vexnum=graph.vexnum;//顶点数
	g->arcnum=graph.arcnum;//边数
	g->kind=graph.kind;      //图类型：1234-无向图、有向图、无向网、有向网
	for(i=0;i<=g->vexnum-1;i++)
	  g->vexs[i]=graph.vexs[i];
    for(i=1;i<=g->vexnum;i++)
	{
		for(j=1;j<=g->vexnum;j++)
		{
			if(g->kind==1||g->kind==2)
				g->arcs[i-1][j-1]=0;
			else
				g->arcs[i-1][j-1]=INF;
		}
	}
	for(i=0;i<=g->arcnum-1;i++)
	{
		if(g->kind==1)
		{
			g->arcs[graph.arcs[i*3]][graph.arcs[i*3+1]]=1;
			g->arcs[graph.arcs[i*3+1]][graph.arcs[i*3]]=1;
		}
		else if(g->kind==2)
		{
			g->arcs[graph.arcs[i*3]][graph.arcs[i*3+1]]=1;
		}
		else if(g->kind==3)
		{
			g->arcs[graph.arcs[i*3]][graph.arcs[i*3+1]]=graph.arcs[i*3+2];
			g->arcs[graph.arcs[i*3+1]][graph.arcs[i*3]]=graph.arcs[i*3+2];
		}
		else if(g->kind==4)
		{
			g->arcs[graph.arcs[i*3]][graph.arcs[i*3+1]]=graph.arcs[i*3+2];
		}
	}
}
void print_Mat(struct MGraph_Mat g)     //显示邻接矩阵
{
	int i,j;
	printf("  ");
	for(i=0;i<=g.vexnum-1;i++)
		printf("%4c",g.vexs[i]);
	printf("\n");
	for(i=0;i<=g.vexnum-1;i++)
	{
		printf("  %c  ",g.vexs[i]);
		for(j=0;j<=g.vexnum-1;j++)
		{
			if(g.kind==1||g.kind==2)
				printf("%d   ",g.arcs[i][j]);
			else
			{
				if(g.arcs[i][j]==INF)
					printf("∞ ");
				else
					printf("%d  ",g.arcs[i][j]);
			}
		}
		printf("\n");
	}
}
struct arcnode
{
	int adjvex,weight;
	struct arcnode*nextarc;
};
struct vexnode
{
	char vexdata;
	struct arcnode*firstarc;
};
struct MGraph_Adj
{
	int vexnum,arcnum;
	struct vexnode vexarr[VEXNUM];
	int kind;
};
void create_Adj(struct MGraph_Adj *g)      //根据全局通用图形定义graph,创建图的邻接表
{
	int i;
	struct arcnode *p=NULL;
	g->vexnum=graph.vexnum;
	g->arcnum=graph.arcnum;
	g->kind=graph.kind;
	for(i=0;i<=g->vexnum-1;i++)
	{
		g->vexarr[i].vexdata=graph.vexs[i];
		g->vexarr[i].firstarc=NULL;
	}
	for(i=0;i<=g->arcnum-1;i++)
	{
		p=(struct arcnode*)(malloc(sizeof(struct arcnode)));
		p->adjvex=graph.arcs[i*3+1];
		p->weight=graph.arcs[i*3+2];
		p->nextarc=g->vexarr[graph.arcs[i*3]].firstarc;
		g->vexarr[graph.arcs[i*3]].firstarc=p;
		if(g->kind==1||g->kind==3)
		{
			p=(struct arcnode*)(malloc(sizeof(struct arcnode)));
            p->adjvex=graph.arcs[i*3];
			p->weight=graph.arcs[i*3+2];
			p->nextarc=g->vexarr[graph.arcs[i*3+1]].firstarc;
			g->vexarr[graph.arcs[i*3+1]].firstarc=p;
		}
	}
}
void print_Adj(struct MGraph_Adj g)
{
	int i;
	struct arcnode *p=NULL;
	printf("\n\n");
	for(i=0;i<=g.vexnum-1;i++)
	{
		printf(" %d %c",i,g.vexarr[i].vexdata);
		p=g.vexarr[i].firstarc;
		while(p)
		{
			if(g.kind==1||g.kind==2)
				printf("->%d",p->adjvex);
			else
				printf("->%d|%d",p->adjvex,p->weight);
			p=p->nextarc;       //下一边表
		}
		printf("\n");
	}
}
// ----------------------这是分割线-------------------------


void Floyd_Mat(struct MGraph_Mat g)
{
	int i,j,k,m=1;
	int d[VEXNUM][VEXNUM];//距离矩阵
	int p[VEXNUM][VEXNUM];//经过点矩阵
	
	for(i=0;i<=g.vexnum-1;i++)//初始化floyd算法的d,p两个矩阵
		for(j=0;j<=g.vexnum-1;j++)
		{
			d[i][j]=g.arcs[i][j];//距离矩阵初始化-复制有向网矩阵
			p[i][j]=j;//经过点矩阵初始化-默认都是直达i-j,存j
		}
		//显示弗洛伊德算法处理过程-显示初始距离矩阵和经历点矩阵
		printf("弗洛伊德处理过程:\n %d.初始距离矩阵(直达)&经历点矩阵(直达)\n     ",m++);
		for(i=0;i<=g.vexnum-1;i++)
			printf("%3c ",g.vexs[i]);//显示第一行，各节点字符
		printf("         ");
		for(i=0;i<=g.vexnum-1;i++)
			printf("%3c ",g.vexs[i]);//显示第一行，各节点字符
		printf("\n") ;
		
		for(i=0;i<=g.vexnum-1;i++)//各行
		{
			printf("  %c  ",g.vexs[i]);//先显示字符
			for(j=0;j<=g.vexnum-1;j++)//各列
				if(d[i][j]==INF)
					printf("%3s ", "∞");//显示无穷
				else
					printf("%3d ",d[i][j]);//或 显示权值
				printf("       %c ",g.vexs[i]);//先显示字符
				for(j=0;j<=g.vexnum-1;j++)//各列
					printf("%3d ",p[i][j]);//或显示权值
				printf("\n") ;
		}
		//
		for(k=0;k<=g.vexnum-1;k++)//k为依次探测经过的中间点
		{
			for(i=0; i<=g.vexnum-1;i++)//i为起点
				for(j=0;j<=g.vexnum-1;j++)//j为终点
					if((d[i][k]+d[k][j])<d[i][j]&&(i!=j))//如果经过k点小于i-j现有距离
					{
						d[i][j]=d[i][k]+d[k][j];//更新最小距离
						p[i][j]=p[i][k];//更新最小路径中间点
					}
		
//显示弗洛伊德算法处理过程-显示经各探测点的距离矩阵和经历点矩阵
					printf("\n %d.经历探测%d点的距离矩阵&经历点矩阵\n   ",m++,k);
					for(i=0;i<=g.vexnum-1;i++)
						printf("%3c ",g.vexs[i]);//显示第一行，各节点字符
					printf("         ");
					for(i=0;i<=g.vexnum-1;i++)
						printf("%3c ",g.vexs[i]);//显示第一行，各节点字符
					printf("\n");
					for(i=0;i<=g.vexnum-1;i++)//各行
					{
						printf(" %c ",g.vexs[i]);//先显示字符
						for(j=0;j<=g.vexnum-1;j++)//各列
							if(d[i][j]==INF)
								printf("%3s ","∞");//显示无穷
							else
								printf("%3d ",d[i][j]);//或显示权值
							
						printf("       %c ",g.vexs[i]);//先显示字符
						for(j=0;j<=g.vexnum-1;j++)//各列
							printf("%3d ",p[i][j]);//或显示权值
						printf("\n");
					}
					//
		}
					printf("\n各点之间的最短路径:\n");
					printf(" \t");
					for(i=0;i<=g.vexnum-1;i++)
						printf("%c\t",g.vexs[i]);
					printf("\n");
					for(i=0;i<=g.vexnum-1;i++)
					{
						printf(" %c\t",g.vexs[i]);
						for(j=0;j<=g.vexnum-1;j++)
							if(d[i][j]==INF)
								printf("∞\t");
							else
							{
								printf("%d",d[i][j]);//显示求得的最短距离
								k=p[i][j];
								if(k!=j)//如果有经历点
								{
									printf("-");
									while(k!=j)
									{//逐级显示经历点
										printf("%c",g.vexs[k]);//打印中间点
										k=p[k][j];
									}
								}
								printf("\t");
							}
							printf("\n");
					}
}
/////////////////////////////////////////
void Floyd_Adj(struct MGraph_Adj g)

{
	int i,j,k;
	int p[VEXNUM][VEXNUM],d[VEXNUM][VEXNUM];
	struct arcnode *q=NULL;
	for(i=0;i<g.vexnum;i++)//初始化floyd算法的d,p两个矩阵

		for(j=0;j<=g.vexnum;j++)////////////////////////////////////
		{
			d[i][j]=INF;
			p[i][j]=j;//经过点矩阵
		}
		for(i=0;i<=g.vexnum-1;i++)//循环各顶点数组
		{
			q=g.vexarr[i].firstarc;
			while(q)//循环边表各结点
			{
				d[i][q->adjvex]=q->weight;//距离矩阵
				q=q->nextarc;
			}
		}
		for (k=0;k<g.vexnum;k++)//k为依次探测经过的中间点
		{
			for(i=0;i<g.vexnum;i++)//i为起点
				for(j=0;j<g.vexnum;j++)//j为终点
					if(d[i][j]>(d[i][k]+d[k][j])&&(i!=j))
					{
						d[i][j]=d[i][k]+d[k][j];//更新最小路径
						p[i][j]=p[i][k];//更新最小路径中间顶点
					}
		}
		printf("\n各点之间的最短路径:\n");
		printf(" \t");
		for(i=0;i<=g.vexnum-1;i++)
			printf("%c\t",g.vexarr[i].vexdata);
		printf("\n");
		for(i=0;i<g.vexnum;i++)
		{
			printf(" %c\t", g.vexarr[i].vexdata);
			for(j=0;j<g.vexnum;j++)
				if(d[i][j]==INF)
					printf("∞\t");
				else
				{
					printf("%d",d[i][j]);
					k=p[i][j];
					if(k!=j)
					{
						printf("-") ;
						while(k!=j)
						{
							printf("%c",g.vexarr[k].vexdata);//打印中间点
							k=p[k][j];
						}
					}
						printf("\t");
				}
				printf("\n");
		}
}

void funp(char s[])
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	printf("%s\n",s);
	printf("%s",asctime(timeinfo));
}

void main()
{
	struct MGraph_Mat g;
	struct MGraph_Adj g1;
	create_Mat(&g);
	Floyd_Mat (g);
	create_Adj(&g1);
	Floyd_Adj(g1);
	printf("\n");
	funp("网安B203的佛洛依德拉算法基于邻接矩阵邻接表的程序实现");
}






