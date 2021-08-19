//#include "string.h"
#include "stdio.h"    
#include "stdlib.h"   
//#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* 存储空间初始分配量 */

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码,如OK等 */
typedef char TElemType;
typedef  struct BiThrNode	/* 二叉线索存储结点结构 */
{
	TElemType data;	/* 结点数据 */
	struct BiThrNode *lchild, *rchild;	/* 左右孩子指针 */
	int LTag;
	int RTag;		/* 左右标志 */
} BiThrNode, *BiThrTree;

TElemType N='#'; /* 字符型以空格符为空 */

Status visit(TElemType e)
{
	printf("%c ",e);
	return OK;
}

/* 按前序输入二叉线索树中结点的值,构造二叉线索树T */
/* 0(整型)/空格(字符型)表示空结点 */
Status CreateBT(BiThrTree *T)
{ 
	TElemType h;
	scanf("%c",&h);

	if(h==N)
		*T=NULL;
	else
	{
		*T=(BiThrTree)malloc(sizeof(BiThrNode));
		if(!*T)
			exit(OVERFLOW);
		(*T)->data=h; /* 生成根结点(前序) */
		CreateBT(&(*T)->lchild); /* 递归构造左子树 */
		if((*T)->lchild) /* 有左孩子 */
			(*T)->LTag=0;
		CreateBT(&(*T)->rchild); /* 递归构造右子树 */
		if((*T)->rchild) /* 有右孩子 */
			(*T)->RTag=0;
	}
	return OK;
}

BiThrTree pre; /* 全局变量,始终指向刚刚访问过的结点 */
/* 中序遍历进行中序线索化 */
void InThreading(BiThrTree p)
{ 
	if(p)
	{
		InThreading(p->lchild); /* 递归左子树线索化 */
		if(!p->lchild) /* 没有左孩子 */
		{
			p->LTag=1; /* 前驱线索 */
			p->lchild=pre; /* 左孩子指针指向前驱 */
		}
		if(!pre->rchild) /* 前驱没有右孩子 */
		{
			pre->RTag=1; /* 后继线索 */
			pre->rchild=p; /* 前驱右孩子指针指向后继(当前结点p) */
		}
		pre=p; /* 保持pre指向p的前驱 */
		InThreading(p->rchild); /* 递归右子树线索化 */
	}
}

/* 中序遍历二叉树T,并将其中序线索化,Thrt指向头结点 */
Status InOrderThreading(BiThrTree *Thrt,BiThrTree T)
{ 
	*Thrt=(BiThrTree)malloc(sizeof(BiThrNode));
	if(!*Thrt)
		exit(OVERFLOW);
	(*Thrt)->LTag=0; /* 建头结点 */
	(*Thrt)->RTag=1;
	(*Thrt)->rchild=(*Thrt); /* 右指针回指 */
	if(!T) /* 若二叉树空,则左指针回指 */
		(*Thrt)->lchild=*Thrt;
	else
	{
		(*Thrt)->lchild=T;
		pre=(*Thrt);
		InThreading(T); /* 中序遍历进行中序线索化 */ 
		pre->rchild=*Thrt;
		pre->RTag=1; /* 最后一个结点线索化 */
		(*Thrt)->rchild=pre;
	}
	return OK;
}

/* 中序遍历二叉线索树T(头结点)的非递归算法 */
Status InOrderBT(BiThrTree T)
{ 
	BiThrTree p;
	p=T->lchild; /* p指向根结点 */
	while(p!=T)
	{ /* 空树或遍历结束时,p==T */
		while(p->LTag==0)
			p=p->lchild;
		if(!visit(p->data)) /* 访问其左子树为空的结点 */
			return ERROR;
		while(p->RTag==1&&p->rchild!=T)
		{
			p=p->rchild;
			visit(p->data); /* 访问后继结点 */
		}
		p=p->rchild;
	}
	return OK;
}
void fun(char s[]) 
{ 
time_t rawtime; 
struct tm * timeinfo; 
time ( &rawtime ); 
timeinfo = localtime ( &rawtime ); 
printf("%s\n",s); 
printf("%s", asctime (timeinfo) ); 
} 
int main()
{
	BiThrTree H,T;
	printf("请按前序输入二叉树(如:'ABDH##I##EJ###CF##G##')\n");
 	CreateBT(&T); /* 按前序产生二叉树 */
	InOrderThreading(&H,T); /* 中序遍历,并中序线索化二叉树 */
	printf("中序遍历(输出)二叉线索树:\n");
	InOrderBT(H); /* 中序遍历(输出)二叉线索树 */
	printf("\n");
	fun("中序线索二叉树的创建、线索化");
	
	return 0;
}


