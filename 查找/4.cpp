#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct BSTNode//数据节点定义
{
	int data;
	struct BSTNode *lchild,*rchild;
};
struct BSTNode *CreateBST(int a[],int n)//根据数组a创建二叉排列树
{
	int i;
	struct BSTNode *root=(struct BSTNode *)malloc(sizeof(struct BSTNode)),*pre=NULL,*p=NULL;
	root->data=a[0];
	root->lchild=NULL;
	root->rchild=NULL;
	for(i=1;i<=n-1;i++)
	{
		p=root;
		while(p)
		{
			pre=p;//一直指向p结点的父节点
			if(a[i]<p->data)
				p=p->lchild;
			else if(a[i]>p->data)
				p=p->rchild;
			else
				break;//找到相等的break跳出，提前结束循环

		}
		if(!p)//如果p等于空，没找到相等节点
		{
			p=(struct BSTNode *)malloc(sizeof(struct BSTNode));
			p->data=a[i];
			p->lchild=NULL;
			p->rchild=NULL;//通过pre把p插入pre做孩子或右孩子位置
			if(a[i]<pre->data)//左孩子位置
				pre->lchild=p;
			else//右孩子位置
				pre->rchild=p;
		}
	}
	return root;
}
void InOrder(struct BSTNode *root)
{
	if(root!=NULL)
	{
		InOrder(root->lchild);
		printf(" %d ",root->data);
		InOrder(root->rchild);
	}
}
void FiOrder(struct BSTNode *root)
{
	if(root!=NULL)
	{
		printf(" %d ",root->data);
		FiOrder(root->lchild);
		FiOrder(root->rchild);
	}
}
void FreeBST(struct BSTNode *root)
{
	if(root!=NULL)
	{
		FreeBST(root->lchild);
		FreeBST(root->rchild);
		free(root);
	}
}
struct BSTNode *fat=NULL;
int bz=0;
struct BSTNode *IfBalance(struct BSTNode *root,int *h,int *hc)
{
	if(bz==1)
		return NULL;
	if(root!=NULL)
	{
		int lh,rh,lnhc,rnhc;
		struct BSTNode *phfl=IfBalance(root->lchild,&lh,&lnhc);
		struct BSTNode *phfr=IfBalance(root->rchild,&rh,&rnhc);
		*h=lh>rh?lh+1:rh+1;
		*hc=lh-rh;
		if(phfl)
		{
			if(bz==0)
			{
				fat=root;
				bz=1;
			}
			*hc=lnhc;
			return phfl;
		}
		else if(phfr)
		{
			if(bz==0)
			{
				fat=root;
				bz=1;
			}
			*hc=rnhc;
			return phfr;
		}
		else
		{
			if(*hc>=-1&&*hc<=1)
				return NULL;
			else
				return root;
		}
	}
	else
	{
		*h=0;
		*hc=0;
		return NULL;
	}
}
int qgd(struct BSTNode *t)
{
	if(t)
	{
		int k,r;
		k=qgd(t->lchild);
		r=qgd(t->rchild);
		if(k>r)
			return k+1;
		else
			return r+1;
	}
	else
		return 0;
}
void Bbt_Adjust(struct BSTNode **bst,struct BSTNode *pa,int hc)
{
	struct BSTNode *pb=NULL,*pc=NULL;
	if(hc==2)//LL/LR
	{
		pb=pa->lchild;
		if(qgd(pb->lchild)-qgd(pb->rchild)==-1)
		{
			pc=pb->rchild;
			pa->lchild=pc->rchild;
			pb->rchild=pc->lchild;
			pc->lchild=pb;
			pc->rchild=pa;
			if(pa==*bst)
				*bst=pc;
			else
			{
				if(fat->lchild==pa)
					fat->lchild=pc;
				else
					fat->rchild=pc;
			}
		}
		else//LL	
		{
			pa->rchild=pb->lchild;
			pb->lchild=pa;
			if(pa==*bst)
				*bst=pb;
			{
				if(fat->lchild==pa)
					fat->lchild=pb;
				else
					fat->rchild=pb;
			}
		}
	}
	else if(hc==-2)//RR/RL
	{
		pb=pa->rchild;
		if(qgd(pb->lchild)-qgd(pb->rchild)==1)
		{
			pc=pb->lchild;
			pa->rchild=pc->lchild;
			pb->lchild=pc->rchild;
			pc->lchild=pa;
			pc->rchild=pb;
			if(pa==*bst)
				*bst=pc;
		else
		{
			if(fat->lchild==pa)
				fat->lchild=pc;
			else
				fat->rchild=pc;
		}
	}

	else//RR
		{
			pa->rchild=pb->lchild;
			pb->lchild=pa;
			if(pa==*bst)
				*bst=pb;
			else
			{
				if(fat->lchild==pa)
					fat->lchild=pb;
				else
					fat->rchild=pb;
			}
		}
	}
}
int jdgs=0,zbjcs=0;
void qasl(struct BSTNode *t,int jdcs)
{
	if(t)
	{
		jdgs++;
		zbjcs=zbjcs+jdcs;
		qasl(t->lchild,jdcs+1);
		qasl(t->rchild,jdcs+1);
	}
}
int gy(int a,int b)
{
	int i;
	for(i=a<b?a:b;i>=1;i--)
		if(a%i==0&&b%i==0)
			return i;
		return 1;
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
	int a[12]={5,2,7,6,9,12,1,3,4,8,10,11},h,hc;
	struct BSTNode *bst=NULL,*p=NULL;
	int ys=1;
	bst=CreateBST(a,12);
	InOrder(bst);
	printf("\n");
	FiOrder(bst);
	printf("\n");
	qasl(bst,1);
	ys=gy(zbjcs,jdgs);
	printf("ASL:%d/%d\n",zbjcs/ys,jdgs/ys);
		bz=0;
	p=IfBalance(bst,&h,&hc);
	while(p)
	{
		Bbt_Adjust(&bst,p,hc);
		bz=0;
		p=IfBalance(bst,&h,&hc);
	}
	InOrder(bst);
	printf("\n");
	FiOrder(bst);
	printf("\n");
	zbjcs=0;
	jdgs=0;
	qasl(bst,1);
	ys=gy(zbjcs,jdgs);
	printf("ASL:%d/%d\n",zbjcs/ys,jdgs/ys);
	FreeBST(bst);
 funp("调试理解平衡二叉树判断及调整程序实现");
}

















































