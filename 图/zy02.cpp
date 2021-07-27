#include<stdio.h>
#include<stdlib.h>
#include<time.h> 
#define VEXNUM 8
#define INF 9999//无穷大

struct Graph
{
	int vexnum,arcnum,kind;//顶点数，边数，图类型：1234-无向图，有向图，无向网，有向网 
	char vexs[VEXNUM+1];//顶点字符数组 
	int arcs[30];//边起止点下标及权值数组 
} graph={8,10,2,"ABCDEFGH",{0,1,6,0,2,1,0,3,5,1,2,5,1,4,3,2,4,6,2,5,4,2,3,5,3,5,2,4,5,6}};
//6个顶点，10条边，无向网，顶点依次为ABCDEF，
/*
  A-B:6
  A-C:1
  A-D:5
  B-C:5
  B-E:3
  C-E:6
  C-F:4
  C-D:5
  D-F:2
  E-F:6
*/
struct MGraph_Mat//图的邻接矩阵存储数据定义 
{
	int vexnum,arcnum;//顶点数，边数 
	char vexs[VEXNUM];//顶点数组 
	int arcs[VEXNUM][VEXNUM];//邻接矩阵 
	int kind;//图的类型 
};

void create_Mat(struct MGraph_Mat *g)//创建图的邻接矩阵 
{
	int i,j;
	g->vexnum=graph.vexnum;//顶点数
	g->arcnum=graph.arcnum;//边数
	g->kind=graph.kind;//图的类型：1234-无向图，有向图，无向网，有向网 
	
	for(i=0;i<=g->vexnum-1;i++)
	{
		g->vexs[i]=graph.vexs[i];//逐个赋值顶点字符 
	}
	for(i=1;i<=g->vexnum;i++)//邻接矩阵初始化
	{
		for(j=1;j<=g->vexnum;j++)
		{
			if(g->kind==1||g->kind==2)//如果是无向图的或有向图 
			{
				g->arcs[i-1][j-1]=0;//邻接矩阵全部初始值为0 
			}
			else
			{
				g->arcs[i-1][j-1]=INF;//邻接矩阵全部初始值为无穷 
			}
		}
	}
	for(i=0;i<=g->arcnum-1;i++)//逐个边处理，赋权值或1 
	{
		if(g->kind==1)//如果是无向图，一条边处理矩阵两个元素，放1 
		{
			g->arcs[graph.arcs[i*3]][graph.arcs[i*3+1]]=1;
			g->arcs[graph.arcs[i*3+1]][graph.arcs[i*3]]=1;//对称点
		}
		else if(g->kind==2)//如果是有向图，一条边处理矩阵一个元素，放1 
		{
			g->arcs[graph.arcs[i*3]][graph.arcs[i*3+1]]=1;
		}
		else if(g->kind==3)//如果是无向网，一条边处理矩阵两个元素，放权值 
		{
			g->arcs[graph.arcs[i*3]][graph.arcs[i*3+1]]=graph.arcs[i*3+2];
			g->arcs[graph.arcs[i*3+1]][graph.arcs[i*3]]=graph.arcs[i*3+2];
		}
		else if(g->kind==4)//如果是有向网，一条边处理矩阵一个元素，放权值
		{
			g->arcs[graph.arcs[i*3]][graph.arcs[i*3+1]]=graph.arcs[i*3+2];
		}
	}
}
void print_Mat(struct MGraph_Mat g)//显示邻接矩阵 
{
	int i,j;
//	printf("     ");
	for(i=0;i<=g.vexnum-1;i++)
	printf("%3c",g.vexs[i]);//显示第一行，各节点字符 
	printf("\n");
	
	for(i=0;i<=g.vexnum-1;i++)//各行 
	{
		printf("%c",graph.vexs[i]);//先显示字符 
		for(j=0;j<=g.vexnum-1;j++)//各列 
		{
			if(g.kind==1||g.kind==2)//如果是图 
		printf("%d  ",g.arcs[i][j]);//显示1，0 
			else//如果是网 
			{
				if(g.arcs[i][j]==INF)
					printf(" ∞");//显示无穷 
				else
					printf(" %d ",g.arcs[i][j]);//或权值 
			}
		}
		printf("\n");
	}
}

struct arcnode//邻接表-边界点 
{
	int adjvex,weight;//邻接边下标，权值 
	struct arcnode *nextarc;//下一边表指针 
};

struct vexnode//顶点结点 
{
	char vexdata;//顶点字符数据 
	struct arcnode *firstarc;//第一个边表指针 
};

struct MGraph_Adj//图的邻接表储存数据定义 
{
	int vexnum,arcnum;//顶点数，边数 
	struct vexnode vexarr[VEXNUM];//定点节点数组 
	int kind;//图类型 
};

void create_Adj(struct MGraph_Adj *g)//根据全局通用图形定义graph，创建图的邻接表 
{
	int i;
	struct arcnode *p=NULL;
	g->vexnum=graph.vexnum;//顶点数 
	g->arcnum=graph.arcnum;//边数 
	g->kind=graph.kind;//图的类型：1234-无向图，有向图，无向网，有向网 
	for(i=0;i<=g->vexnum-1;i++)
	{
		g->vexarr[i].vexdata=graph.vexs[i];//逐一顶点赋值-顶点字符 
		g->vexarr[i].firstarc=NULL;//第一条边初始值置空 
	}
	
	for(i=0;i<=g->arcnum-1;i++)//逐条边创建边表结点 
	{
		p=(struct arcnode *)(malloc(sizeof(struct arcnode)));//申请边表空间 
		p->adjvex=graph.arcs[i*3+1];//边界点-边下标 
		p->weight=graph.arcs[i*3+2];//边结点-权值 
		
		p->nextarc=g->vexarr[graph.arcs[i*3]].firstarc;
		g->vexarr[graph.arcs[i*3]].firstarc=p;//将p结点插入在指定顶点之后-前插 
		if(g->kind==1||g->kind==3)//若果是无向图或无向网，需再创建一个结点 
		{
			p=(struct arcnode *)(malloc(sizeof(struct arcnode)));
			p->adjvex=graph.arcs[i*3];//边结点-边下标 
			p->weight=graph.arcs[i*3+2];//边结点-权值 
			
			p->nextarc=g->vexarr[graph.arcs[i*3+1]].firstarc;
			g->vexarr[graph.arcs[i*3+1]].firstarc=p;//将p结点插入在指定顶点之后 
		}

	}		
}

void print_Adj(struct MGraph_Adj g)//显示邻接表 
{
	int i;
	struct arcnode *p=NULL;
	printf("\n\n");
	for(i=0;i<=g.vexnum-1;i++)//处理各节点 
	{
		printf(" %d %c",i,g.vexarr[i].vexdata);//下标，顶点字符 
		p=g.vexarr[i].firstarc;//p指向第一个边表结点 
		while(p)//逐个边表显示 
		{
			if(g.kind==1||g.kind==2)//如果是图只显示边序号 
				printf("->%d",p->adjvex);
			else//如果是网，要同时显示边序号，权值 
				printf("->%d|%d",p->adjvex,p->weight);
			p=p->nextarc;//下一边表 
		}
		printf("\n");
	}
}
int visited[VEXNUM];//是否访问数组，用于图的深度广度优先搜索
void DFS_Mat(struct MGraph_Mat g,int v)//深度优先搜索-邻接矩阵存储
{
	int i;
	printf("%c ",g.vexs[v]);
	visited[v]=1;
	for(i=0;i<=g.vexnum-1;i++)
	{
		if(g.arcs[v][i]!=0&&g.arcs[v][i]!=INF&&visited[i]==0)
		{
			DFS_Mat(g,i);
		}
	}
}
void DFSTraverse_Mat(struct MGraph_Mat g,int v)//深度优先搜索-邻接矩阵存储
{
	int i;
	for(i=0;i<=g.vexnum-1;i++)
	visited[i]=0;
	printf("\n邻接矩阵深度优先搜索序列: ");
	for(i=v;i<=g.vexnum+v-1;i++)
		if(visited[i%g.vexnum]==0)
			DFS_Mat(g,i);
}
void BFS_Mat(struct MGraph_Mat g,int v)//广度优先搜索-邻接矩阵存储
{
	int Lq[VEXNUM];
	int i,j,f=0,r=0;
	printf("%c ",g.vexs[v]);
	visited[v]=1;
	Lq[r]=v;
	r++;
	while(r!=f)
	{
		i=Lq[f];
		f++;
		for(j=0;j<=g.vexnum-1;j++)
		{
			if(g.arcs[i][j]!=0&&g.arcs[i][j]!=INF&&visited[j]==0)
			{
				printf("%c ",g.vexs[j]);
				visited[j]=1;
				Lq[r]=j;
				r++;
			}
		}
	}
}
void BFSTraverse_Mat(struct MGraph_Mat g,int v)//广度优先搜索-邻接矩阵存储
{
	int i;
	for(i=0;i<=g.vexnum-1;i++)
		visited[i]=0;
	printf("\n邻接矩阵广度优先搜索序列: ");
	for(i=v;i<g.vexnum+v;i++)
		if(visited[i%g.vexnum]==0)
		BFS_Mat(g,i%g.vexnum);
}
void DFS_Adj(struct MGraph_Adj g,int v)//深度优先搜索-邻接表存储
{
	struct arcnode *p=NULL;
	printf("%c ",g.vexarr[v]);
	visited[v]=1;
	p=g.vexarr[v].firstarc;
	while(p)
	{
		if(visited[p->adjvex]==0)
			DFS_Adj(g,p->adjvex);
		p=p->nextarc;
	}
}
void DFSTraverse_Adj(struct MGraph_Adj g,int v)//深度优先搜索-邻接表存储
{
	int i;
	for(i=0;i<=g.vexnum-1;i++)
		visited[i]=0;
	printf("\n邻接表深度优先搜索序列: ");
	for(i=v;i<=g.vexnum+v-1;i++)
		if(visited[i%g.vexnum]!=1)
			DFS_Adj(g,i%g.vexnum);
}
void BFS_Adj(struct MGraph_Adj g,int v)
{
	int Lq[VEXNUM];
	int i,f=0,r=0;
	struct arcnode *p=NULL;
	printf("%c ",g.vexarr[v].vexdata);
	visited[v]=1;
	Lq[r]=v;
	r++;
	while(r!=f)
	{
		i=Lq[f];
		f++;
		p=g.vexarr[i].firstarc;
		while(p)
		{
			if(visited[p->adjvex]==0)
			{
				printf("%c ",g.vexarr[p->adjvex].vexdata);
				visited[p->adjvex]=1;
				Lq[r]=p->adjvex;
				r++;
			}
			p=p->nextarc;
		}
	}
}

void BFSTraverse_Adj(struct MGraph_Adj g,int v)
{
	int i;
	for(i=0;i<=g.vexnum-1;i++)
	{
		visited[i]=0;
	}
	printf("\n邻接表的广度优先搜索序列：");
	for(i=v;i<g.vexnum+v;i++)
	{
		if(visited[i%g.vexnum]==0)
			BFS_Adj(g,i%g.vexnum);
	}
}

void fun(char s[])
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	printf("%s\n",s);
	printf("%s",asctime(timeinfo));
}

void main()
{
	struct MGraph_Mat g;
	struct MGraph_Adj g1;
	create_Mat(&g);
	print_Mat(g);
	DFSTraverse_Mat(g,4);
	BFSTraverse_Mat(g,4);
	create_Adj(&g1);
	print_Adj(g1);
	DFSTraverse_Adj(g1,4);
	BFSTraverse_Adj(g1,4);
	printf("\n");
	fun("实现图邻接矩阵的深度和广度优先遍历、邻接表存储的深度广度优先遍历和显示的程序实现"); 
}
