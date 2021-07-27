#include "stdio.h" 
#include "stdlib.h"
#include<time.h>
#define VEXNUM 9
#define ARCNUM 11
#define INF 9999    //无穷大
struct Graph        //通用图形定义，用于创建图形的邻接矩阵和邻接表-全局变量
{
	int vexnum,arcnum,kind;//顶点数、边数、图类型：1234-无向图、有向图、无向网、有向网
	char vexs[VEXNUM+1];   //顶点字符数组
	int arcs[ARCNUM*3];     //边起止点下标及权值数组
} graph={9,11,4,"123456789",
{0,1,6,0,2,4,0,3,5,1,4,1,2,4,1,3,5,2,4,6,9,4,7,7,5,7,4,6,8,2,7,8,4}};
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

struct Activity
{
	int u;//活动起点
    int v;//活动终点
    int w;//权值
    int e;//活动最早发生时间
    int l;//活动最迟发生时间
};        //活动(边)--数据存储定义
void CritPath_Mat(struct MGraph_Mat g)//基于邻接矩阵存储的关键路径推导
{
	int i,j,k=0,min=INF;
    int ve[VEXNUM];                  //事件(顶点)的最早发生时间数组
    int vl[VEXNUM];                  //事件(顶点)的最迟发生时间数组
    struct Activity act[ARCNUM];     //活动(边) 数组

    for(i=0;i<=g.vexnum-1;i++)
	{
		ve[i]=0;                       //初始化各顶点事件最早发生时间
        vl[i]=INF;                     //初始化各顶点事件最迟发生时间
	}
	for(i=0;i<=g. vexnum-1;i++)               //遍历矩阵各行
		for(j=0; j<=g. vexnum-1; j++)      //遍历矩阵各列
            if(g. arcs[i][j]!=INF)        //创建活动数组
			{
				act[k].u=i;                 //活动(边)起点
                act[k].v=j;                //活动(边)终点
                act[k].w=g.arcs[i][j];     //活动(边)权值
                k++;
            }

	for(i=0;i<=g.arcnum-1;i++)                  //从起点遍历各边
        if(ve[act[i].u]+act[i].w>ve[act[i].v])   //求各顶点事件的最早发生时间
                  //如 果活动(边)起点最早发生时间+活动(边)权值>活动(边)的终点最早发生时间
           ve[act[i].v]=ve[act[i].u]+act[i]. w;
                 //则更新活动(边)终点的最早发生时间，若有多条路径取大的
     vl[g. vexnum-1]=ve[g. vexnum-1];
                 //最后终点的最迟发生时间，初始为最后终点的最早发生时间
     for(i=g.arcnum-1;i>=0;i--)                  //从终点向前遍历各边-从后向前推
         if(vl[act[i].v]-act[i].w<vl[act[i].u])  //求各顶点事件的最迟发生时间
                 //如果活动(边)终 点最迟发生时间-活动(边)权值<活动(边)起点最迟发生时间
              vl[act[i].u]=vl[act[i].v]-act[i].w;
                     //则更新活动(边)起点的最迟发生时间，若有多条路径取小的
     printf("各事件的最早开始时间/最迟开始时间:\n     ");
	 for(i=0; i<=g.vexnum-1; i++)
         printf(" v%c   ",g.vexs[i]);         //显示各顶点字符
      printf("\n");
      printf("Ve[i]:");
      for(i=0; i<=g. vexnum-1;i++)
           printf("%-6d",ve[i]);//显示各事件(顶点)最早发生时间
      printf("\n");
      printf("Vl[i]:");
	  for(i=0;i<=g.vexnum-1;i++)
      printf("%-6d",vl[i]);       //显示各事件(顶点)最迟发生时间
      for(i=0;i<=g.arcnum-1;i++)//从前往后推
	  {
          act[i].e=ve[act[i].u];
             //各活动(边)最早发生时间，就是各边起点的最早发生时间
          act[i].l=vl[act[i].v]-act[i].w;
             //各活动(边)最迟发 生时间，就是各边终点的最迟发生时间-边权值
	  }
      printf("\n各活动的最早开始时间/最迟开始时间: \n    ");

      for(i=0; i<=g.arcnum-1;i++)      //显示各活动(边)
          printf("v%c-v%c ",g.vexs[act[i].u],g.vexs[act[i].v]);
      printf("\n");

      printf("e[i]:");
      for(i=0; i<=g. arcnum-1;i++) //显示各活动(边)的最早发生时间
           printf("%-6d" ,act[i].e);
      printf("\n") ;
      printf("l[i]:");
      for(i=0; i<=g.arcnum-1;i++) //显示各活动(边)的最迟发生时间
      printf("%-6d" ,act[i].l);

      printf("\n关键路径:\n");
      for(i=0;i<=g.arcnum-1;i++)
          if(act[i].e==act[i]. l)//若活动(边)的最早最迟发生时间相等，则是关键路径-显示
			  printf("v%c-v%c  ",g.vexs[act[i].u],g.vexs[act[i].v]);
      printf("\n");
}
//以下是邻接表
void CritPath_Adj(struct MGraph_Adj g)//基于邻接表存储的关键路径推导
{
    int i,k=0;
    int ve[VEXNUM];//事件(顶点)的最早发生时间数组
    int vl[VEXNUM];//事件(顶点)的最迟发生时间数组
    struct Activity act[ARCNUM];//活 动(边)数组
    struct arcnode *p=NULL;

	for(i=0;i<=g.vexnum-1;i++)
	{
        ve[i]=0;//初始化各顶点事件最早发生时间
        vl[i]=INF;//初始化各顶点事件最迟发生时间
	}
    for(i=0;i<=g. vexnum-1;i++)//循环各顶点数组
	{
        p=g.vexarr[i].firstarc;
        while(p)//循环边表各结点，创建活动数组
		{
             act[k].u=i;//活动(边)起点
             act[k].v=p->adjvex;//活动(边)终点
             act[k].w=p->weight;//活动(边)权值
			 k++;
			 p=p->nextarc;
		}
	}

	for(i=0; i<=g.vexnum-1; i++)//循环各顶点数组
	{
         p=g.vexarr[i].firstarc;
         while(p)//循环边表各结点
		 {
              if(p->weight+ve[i]>ve[p->adjvex])//求各顶点事件的最早发生时间....
                                  //如果活动(边)起点最早发生时间+活动(边)权值>活动(边)的终点最早发生时间
                    ve[p->adjvex]=p->weight+ve[i];
                                 //则更新活动(边)终点的最早发生时间，若有多条路径取大的
               p=p->nextarc;
		 }
	}

    vl[g.vexnum-1]=ve[g.vexnum-1];
            //最后终点的最迟发生时间，初始为最后终点的最早发生时间
    for(i=g.arcnum-1;i>=0;i--) //从终点向前遍历各边-从后向前推导
        if(vl[act[i].v]-act[i].w<vl[act[i].u])//求各顶点事件的最迟发生时间
                 //如果活动(边)终点最迟发生时间-活动(边)权值<活动(边)起点最迟发生时间
             vl[act[i].u]=vl[act[i].v]-act[i].w;
		             //则更新活动(边)起点的最迟发生时间
     printf("\n各事件的最早开始时间/最迟开始时间: \n");
     for(i=0;i<=g.vexnum-1;i++) //显示各顶点字符
         printf("v%c    ",g.vexarr[i]);
     printf("\n");
     for(i=0;i<=g.vexnum-1; i++)
          printf("%-6d",ve[i]);//显示各事件(顶点)最早发生时间
     printf("\n") ;
     for(i=0; i<=g.vexnum-1;i++)
          printf("%-6d",vl[i]);//显示各事件(顶点)最迟发生时间

	 for(i=0;i<=g.arcnum-1;i++) //从前往后推
	 {
          act[i].e=ve[act[i].u];
           //各活动(边)最早发生时间，就是各边起点的最早发生时间
          act[i].l=vl[act[i].v]-act[i].w;
           //各活动(边)最迟发生时间，就是各边终点的最迟发生时间-边权值
	 }
	 printf("\n各活动的最早开始时间/最迟开始时间: \n");
     for(i=0;i<=g.arcnum-1;i++) //显示各活动(边)
          printf("v%c-v%c ", g.vexarr[act[i].u].vexdata,g.vexarr[act[i].v].vexdata) ;
     printf("\n");
     for(i=0;i<=g.arcnum-1;i++) //显示各活动(边)的最早发生时间
         printf("%-6d",act[i].e);
     printf("\n");
     for(i=0;i<=g.arcnum-1;i++) //显示各活动(边)的最迟发生时间
         printf("%-6d",act[i].l);
     printf("\n关键路径:\n");
     for(i=0; i<=g.arcnum-1;i++)
          if(act[i].e==act[i].l)//若活动(边)的最早最迟发生时间相等,则是关键路径-显示
               printf("v%c-v%c  ",g.vexarr[act[i].u].vexdata,g.vexarr[act[i]. v]. vexdata);
     printf("\n");
}
//
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
	CritPath_Mat(g);
    create_Adj(&g1);
	CritPath_Adj(g1);

	printf("\n");
	funp("AOV图关键路径邻接矩阵邻接表的程序实现");
}










