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
} graph={6,8,4,"ABCDEF",{0,5,100,0,4,30,0,2,10,1,2,5,2,3,50,3,5,10,4,3,20,4,5,60}};
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


void Dijkstra_Mat (struct MGraph_Mat g, int index)//Dijkstra求最短路径函数index表示起始点
{
	int i,j,k;
    int min_j1,min_xb;//最小距离、最小点下标
    int used[VEXNUM];//标记点是否选择过-各趟最近点
    int distance[VEXNUM];//index起始点到各点的最短距离
    char path[VEXNUM] [VEXNUM];//记录index起始点到其他各点路径-经过的点-下标序列
    int num[VEXNUM];//index起始点到其他各点路径长度-经历点个数，和path二维数组一起使用
    for(i=0;i<=g.vexnum-1;i++)//循环-顶点个数次
    {
		used[i]=0;//初始化均未为选过
        path[i][0]=g.vexs[index];//初始化各路径起始点字符均为-index对应的字符
        num[i]=1;//初始化经历点个数为1 (因为各路径第一点均为起始点，path[i][0]-0已用过，再用从1开始)
    }
	for(i=0;i<=g.vexnum-1;i++)//循环-顶点个数次
	{
		distance[i]=g.arcs[index][i];
             //初始化index起始点到各点的最短距离为:index到各顶点的直接距离，即矩阵第index行
        if(distance[i]!=INF)//如果index点到某点有边
			path[i][num[i]++]=g.vexs[i];//记录经过的点字符
               //num[i]++:下标用后++，是为了下一次使用做准备
	}
//显示过程-直达各点距离
	printf("   迪杰斯特拉过程: ");
    printf("\n\t\t  ");
    for(i=0;i<=g.vexnum-1;i++)
    {
		if(i==index) continue;//跳过出发点
        printf("v%d\t",i);//显示标题和
	}
    printf(" 选出最小 ");
    printf("\n  v%d直达各点距离: ",index);
    for(i=0;i<=g.vexnum-1;i++)//显示第一行直达各点距离
	{
		if(i==index) continue;
		if(distance[i]==INF)//如果index到i点的最短距离为无穷
			printf("∞\t");
		else
			printf("%d\t",distance[i]);
	}
	//
	used[index]=1;//设置起始点index使用过标记
	for(i=0;i<=g.vexnum-2;i++)//挑选处理趟数-顶点个数减1次
	{
		min_xb=index+1;//假设起始点下一点为最近点
        min_j1=INF;//最近距离初值为无穷
        for(j=0;j<=g.vexnum-1;j++)//循环找最短路径点-循环顶点个数减1次
		{
			if((used[j]==0)&&(distance[j]<min_j1))
            //如果k点未选过且距离小于min_ j1点
			{
				min_j1=distance[j];//最近 距离
                min_xb=j;//记录找到的最近点下标
			}
		}
//循环结束后，min_ j1为找到的最近距离，min_xb为找到的最近点下标
//
		if(min_j1==INF)
            printf("找到最近点v%d(∞)\n",min_xb);
        else
            printf("找到最近点v%d(%d)\n",min_xb,min_j1);
//
		used[min_xb]=1;//标记找到的最近点-已使用过
        for(j=0;j<=g.vexnum-1;j++)
//逐点判断经过最近min_ xb点两段距离之和，是否小于原距离，是则更新-循环顶点个数减1次
		{
			if((used[j]==0)&&(distance[min_xb]+g.arcs[min_xb][j]<distance[j]))
//如果经过min_ _xb点路径更近
			{
				distance[j]=distance[min_xb]+g.arcs[min_xb][j];//更新距 离
                for(k=0;k<=num[min_xb]-1;k++)
					path[j][k]=path[min_xb][k];//更新复制路径
				num[j]=num[min_xb];//复制经历点个数
				path[j][num[j]++]=g.vexs[j];
				//添加路径点，且num[k]++加1为下一次使用做准备
			}
		}
//显示处理过程
		printf("经过v%d点最短距离: ",min_xb);
        for(j=0;j<=g.vexnum-1;j++)
		{
			if(j==index) continue;//同一点调过
			if(distance[j]==INF)//如果index到i点的最短距离为无穷
				printf(" ∞\t");
			else
				printf("%d\t",distance[j]);
		}
	}
	//显示结果
	printf("\n\n  v%d到各点的最短路径依次为:\n", index);//index单源起始点字符
	for(i=0;i<=g.vexnum-1;i++)//起始点到其他各点的下标
	{
		if(i==index) continue;
		
			printf("    %c-%c\t",g.vexs[index],g.vexs[i]);
			if(distance[i]==INF)//如果index到i点的最短距离为无穷
				printf("   ∞\t");
			else
			{
				printf("   %d\t",distance[i]);//显 示index到i点的最短距离
			    printf("%c",path[i][0]);//最短距离-路径-起始点
				for(j=1;j<=num[i]-1;j++)
					printf("-%c",path[i][j]);//最短距离的路径-各经过点
			}
			printf("\n");
		}
}
void Dijkstra_Adj(struct MGraph_Adj g,int index)//Dijkstra求最短路径函数index表示起始点
{
	int i,j;
	int min_xb,min_j1;//最小下标、最小距离
	int used[VEXNUM];//标记点是否使用过
    int distance[VEXNUM];//到各 点的距离
    char path[VEXNUM] [VEXNUM];//记录各路径经过的点
    int num[VEXNUM];//exp数组 下标
    struct arcnode *p=NULL;
	for(i=0;i<=g.vexnum-1;i++)
	{
		used[i]=0;//初始化均未使用过
		path[i][0]=g.vexarr[index].vexdata;//设置各路径起始点
		num[i]=1;
	}
	for(i=0;i<=g.vexnum-1;i++)
		distance[i]=INF;
	p=g.vexarr[index].firstarc;
	while(p)//循环边表各结点
	{
		distance[p->adjvex]=p->weight;//有边更新距离
		path[p->adjvex][num[p->adjvex]++]=g.vexarr[p->adjvex].vexdata;
		p=p->nextarc;
	}
//
	used[index]=1;//设置起始点index使用过标记
	for(i=0;i<=g.vexnum-2;i++)//挑选处理趟数
	{
		min_xb=index+1;//假设起始点下一点为最近点
		min_j1=INF;//最近距离初值为INF
		for(j=0;j<=g.vexnum-1;j++)//循环找最短路径点

		{
			if((used[j]==0)&&(distance[j]<min_j1))
			{
				min_j1=distance[j];//最近距 离
				min_xb=j;          //j为刚刚找到的V-U中 到源点路径最短的顶点
			}
		}
		used[min_xb]=1;//标记最近点使用过标记
		p=g.vexarr[min_xb].firstarc;
		while(p)//遍历最近min_ xb结点的边表各结点
		{
			if((used[p->adjvex]==0)&&(distance[min_xb]+p->weight<distance[p->adjvex]))//如果经过min. _xb点路径更近
			{
				distance[p->adjvex]=distance[min_xb]+p->weight;//更新距离
				for(j=0;j<num[min_xb];j++)
					path[p->adjvex][j]=path[min_xb][j];//复制更新路径
				num[p->adjvex]=j;
				path[p->adjvex][num[p->adjvex]++]=g.vexarr[p->adjvex].vexdata;//添加路径点
			}
			p=p->nextarc;
		}
	}

	printf("\n %c到各点的最短路径依次为:\n",g.vexarr[index].vexdata);
	for(i=0;i<=g.vexnum-1;i++)
	{
		if(i==index) continue;
		printf("    %c-%c\t",g.vexarr[index].vexdata,g.vexarr[i].vexdata); 
		if(distance[i%g.vexnum]==INF)
			printf("  ∞\t");
		else
		{
			printf("  %d\t",distance[i]);
			printf("%c",path[i][0]);//最短距离-路径-起始点
			for(j=1;j<num[i];j++)
				printf("-%c",path[i][j]);
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
	Dijkstra_Mat(g,0);
	create_Adj(&g1);
	Dijkstra_Adj(g1,0);

	printf("\n");
	funp("迪杰斯特拉算法基于邻接矩阵邻接表的程序实现");
}




