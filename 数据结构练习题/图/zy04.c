# include <stdio.h>
# include <stdlib.h>
# define VEXNUM 8
# define INF 9999
# include <time.h>//Í¼»ùÓÚÁÚ½Ó¾ØÕó/ÁÚ½Ó±í´æ´¢µÄÆÕÀûÄ·Ëã·¨ÊµÏÖ£¬»ùÓÚÁÚ½Ó¾ØÕó/ÁÚ½Ó±í´æ´¢µÄ¿ËÂ³Ë¹¿¨¶ûËã·¨ÊµÏÖ
struct Graph{
	int vexnum,arcnum,kind;  
	char vexs[VEXNUM+1];
	int arcs[30]; 
}graph={8,9,2,"ABCDEFGH",{0,1,0,0,2,0,0,5,0,1,3,0,2,6,0,5,6,0,5,7,0,6,7,0,3,6}};

struct MGraph_Mat{
	int vexnum,arcnum;  
	char vexs[VEXNUM];
	int arcs[VEXNUM][VEXNUM];
	int kind;
};

void create_Mat(struct MGraph_Mat *g){
	int i,j;
	g->vexnum=graph.vexnum;
	g->arcnum=graph.arcnum;
	g->kind=graph.kind;
	
	for(i=0;i<=g->vexnum-1;i++){
		g->vexs[i]=graph.vexs[i];
	}
	for(i=1;i<=g->vexnum;i++){
		for(j=1;j<=g->vexnum;j++){
			if(g->kind==1||g->kind==2){
				g->arcs[i-1][j-1]=0;
			}
			else{
				g->arcs[i-1][j-1]=INF;
			}
		}
	}
	for(i=0;i<=g->arcnum-1;i++){
		if(g->kind==1){
			g->arcs[graph.arcs[i*3]][graph.arcs[i*3+1]]=1;
			g->arcs[graph.arcs[i*3+1]][graph.arcs[i*3]]=1;
		}
		else if(g->kind==2){
			g->arcs[graph.arcs[i*3]][graph.arcs[i*3+1]]=1;
		}
		else if(g->kind==3){
			g->arcs[graph.arcs[i*3]][graph.arcs[i*3+1]]=graph.arcs[i*3+2];
			g->arcs[graph.arcs[i*3+1]][graph.arcs[i*3]]=graph.arcs[i*3+2];
		}
		else if(g->kind==4){
			g->arcs[graph.arcs[i*3]][graph.arcs[i*3+1]]=graph.arcs[i*3+2];
		}
	}
}
void fun(char s[]){
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	printf("%s\n",s);
	printf("%s",asctime(timeinfo));
}

void print_Mat(struct MGraph_Mat g){
	int i,j;
	printf("     ");
	for(i=0;i<=(g.vexnum-1);i++){
		printf("%3c",graph.vexs[i]);
	}
	printf("\n");
	
	for(i=0;i<=g.vexnum-1;i++){
		printf("   %c   ",graph.vexs[i]);
		for(j=0;j<=g.vexnum-1;j++){
			if(g.kind==1||g.kind==2){
				printf("%d  ",g.arcs[i][j]);
			}
			else{
				if(g.arcs[i][j]==INF){
					printf("¡Ş ");
				}
				else{
					printf("%d  ",g.arcs[i][j]);
				}
			}
		}
		printf("\n");
	}
}


struct arcnode{
	int adjvex,weight;  
	struct arcnode *nextarc;
};
struct vexnode{
	char vexdata;
	struct arcnode *firstarc;  
};

struct MGraph_Adj{
	int vexnum,arcnum;
	struct vexnode vexarr[VEXNUM];
	int kind;
};

void create_Adj(struct MGraph_Adj *g){
	int i;
	struct arcnode *p=NULL;
	g->vexnum=graph.vexnum;
	g->arcnum=graph.arcnum;
	g->kind=graph.kind;
	for(i=0;i<=g->vexnum-1;i++){
		g->vexarr[i].vexdata=graph.vexs[i];
		g->vexarr[i].firstarc=NULL;
	}
	for(i=0;i<=g->arcnum-1;i++){
		p=(struct arcnode *)(malloc(sizeof(struct arcnode)));
		p->adjvex=graph.arcs[i*3+1];
		p->weight=graph.arcs[i*3+2];
		
		p->nextarc=g->vexarr[graph.arcs[i*3]].firstarc;
		g->vexarr[graph.arcs[i*3]].firstarc=p;
		
		if(g->kind==1||g->kind==3){
			p=(struct arcnode *)(malloc(sizeof(struct arcnode)));
			p->adjvex=graph.arcs[i*3];
			p->weight=graph.arcs[i*3+2];
			
			p->nextarc=g->vexarr[graph.arcs[i*3+1]].firstarc;
			g->vexarr[graph.arcs[i*3+1]].firstarc=p;
		}
	}
}

void print_Adj(struct MGraph_Adj g){
	int i;
	struct arcnode *p=NULL;
	printf("\n\n");
	for(i=0;i<=g.vexnum-1;i++){
		printf("   %d %c",i,g.vexarr[i].vexdata);
		p=g.vexarr[i].firstarc;
		while(p){
			if(g.kind==1||g.kind==2){
				printf("->%d",p->adjvex);
			}
			else{
				printf("->%d|%d",p->adjvex,p->weight);
			}
			p=p->nextarc;
		}
		printf("\n");
	}
}

void TopSort_Mat(struct MGraph_Mat g){
	int i,j,k;
	int in[VEXNUM];
	for(i=0;i<=g.vexnum-1;i++)
	{
		in[i]=0;
	}
	for(i=0;i<g.vexnum;i++)
	{
		for(j=0;j<g.vexnum;j++)
		{
			if(g.arcs[i][j]!=0&&g.arcs[i][j]!=INF)
				in[j]++;     //Í³¼Æ¸÷¶¥µãµÄÈë¶È
		}
	}
	for(i=0;i<g.vexnum;i++){
		for(j=0;j<g.vexnum;j++){
			if(in[j]==0){
				printf(" %c",g.vexs[j]);
				in[j]=-1;
				for(k=0;k<g.vexnum;k++){
					if(g.arcs[j][k]!=0&&g.arcs[j][k]!=INF)
						in[k]--;
				}
				break;
			}
		}
	}
}

void TopSort_Adj(struct MGraph_Adj g)
{
	int i,j;
	int in[VEXNUM];
	struct arcnode *p=NULL;
	for(i=0;i<g.vexnum;i++){
		in[i]=0;
	}
	for(i=0;i<g.vexnum;i++){
		p=g.vexarr[i].firstarc;
		while(p){
			in[p->adjvex]++;
			p=p->nextarc;
		}
	}

	for(i=0;i<g.vexnum;i++){
		for(j=0;j<g.vexnum;j++){
			if(in[j]==0){
				printf(" %c",g.vexarr[j].vexdata);
				in[j]=-1;
				p=g.vexarr[j].firstarc;
				while(p!=NULL){
					in[p->adjvex]--;
					p=p->nextarc;
				}
				break;
			}
		}
	}
}

int main(){
	
	struct MGraph_Mat g;
	struct MGraph_Adj g1;
	create_Mat(&g);
	print_Mat(g);
	
	create_Adj(&g1);
	print_Adj(g1);
	printf("ÁÚ½Ó¾ØÕóµÄÍØÆËÅÅĞò£º");
	TopSort_Mat(g);
	printf("\nÁÚ½Ó±íµÄÍØÆËÅÅĞò£º");
	TopSort_Adj(g1);
	fun("\nÍØÆËĞòÁĞµÄ³ÌĞòÊµÏÖ");
	return 0;
}
