#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct BSTNode//数据节点定义
{
	int data;
	struct BSTNode *lchild,*rchild;
};
void InsertBST(struct BSTNode **bst, int k)//二叉排列树-插入结点
{
	if(bst==NULL)//如果原树为空
	{
		*bst=(struct BSTNode *)malloc(sizeof(struct BSTNode));
		(*bst)->data=k;
		(*bst)->lchild=NULL;
		(*bst)->rchild=NULL;
	}
	else//如果原树不为空
	{
		struct BSTNode *s=*bst,*pre=NULL;
		while(s)//循环找插入结点位置
		{
			pre=s;//记录父结点
			if(k<s->data)
				s=s->lchild;
			else if(k>s->data)
				s=s->rchild;
			else//如果找到相等元素
				break;
		}
		if(!s)//如果没找到相同结点，找到插入位置
		{
		struct BSTNode *p=(struct BSTNode *)malloc(sizeof(struct BSTNode));
			p->data=k;
			p->lchild=NULL;
			p->rchild=NULL;
			if(k<pre->data)
				pre->lchild=p;
			else
				pre->rchild=p;
		}
	}
}
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

void InOrder(struct BSTNode *root)//中序遍历二叉排列树
{
	if(root!=NULL)
	{
		InOrder(root->lchild);
		printf(" %d ",root->data);
		InOrder(root->rchild);
	}
}
void FiOrder(struct BSTNode *root)//先序遍历二叉排序树
{
	if(root!=NULL)
	{
		printf(" %d ",root->data);
		FiOrder(root->lchild);
		FiOrder(root->rchild);
	}
}
void FreeBST(struct BSTNode *root)//释放二叉树空间
{
	if(root!=NULL)
	{
		FreeBST(root->lchild);
		FreeBST(root->rchild);
		free(root);
	}
}
struct BSTNode *SearchBST(struct BSTNode *bst,int key)//在二叉排列树中查找指定节点
{
	struct BSTNode *p=bst;
	while(p)
	{
		if(key==p->data)
			return p;//找到指定值结点，返回该结点指针
		else if(key<p->data)
			p=p->lchild;
		else
			p=p->rchild;
	}
	return NULL;//查找失败
}
void DeleteBST(struct BSTNode **bst,int key)//在二叉排列树中删除指定结点
{
	struct BSTNode *p=*bst,*pre=*bst,*s=NULL,*spre=NULL;
	while(p)//循环找值为key的结点
	{
		if(key==p->data)//找到结点值等于key的结点
			break;//提前跳出，p是找到结点的地址
		else if(key<p->data)
		{
			pre=p;//pre一直指向p的父节点
			p=p->lchild;
		}
		else
		{
			pre=p;//pre一直指向p的父节点
			p=p->rchild;
		}
	}
	if(p)//如果找到key结点
	{
		if(p->lchild==NULL&&p->rchild==NULL)//如果是叶子结点
		{
			if(p==*bst)//如果只有一个结点
				*bst=NULL;
			else if(p==pre->lchild)
				pre->lchild=NULL;
			else if(p==pre->rchild)
				pre->rchild=NULL;
		}
		else if(p->lchild!=NULL&&p->rchild==NULL)//如果p结点右子树空而左子树不为空
		{
			if(p==*bst)//如果p是树根结点
			*bst=p->lchild;
		else if(p==pre->lchild)//如果p不是根结点，且是父结点的左子树
			pre->lchild=p->rchild;
		else if(p==pre->rchild)//如果p不是根结点，且是父结点的右子树
			pre->rchild=p->lchild;
		}
		else if((p->lchild==NULL)&&(p->rchild!=NULL))//如果p结点左子树空而右子树不空
		{
			if(p==*bst)//如果p是树根结点
				*bst=p->rchild;
			else if(p==pre->lchild)//如果p不是根结点，且是父结点的左子树
				pre->lchild=p->rchild;
			else if(p==pre->rchild)//如果p不是根结点，且是父结点的右子树
				pre->rchild=p->rchild;
		}
		else//如果p结点左右子树均不空
		{
			s=p->lchild;
			if(s->rchild==NULL)
			{
				if(p==*bst)
					*bst=s;
				else if(p==pre->lchild)
					pre->lchild=s;
				else if(p==pre->rchild)
					pre->rchild=s;
				s->rchild=p->rchild;
			}
			else
			{
				while(s->rchild)
				{
					spre=s;
					s=s->rchild;
				}
				spre->rchild=s->lchild;
				if(p==*bst)
					*bst=s;
				else if(p==pre->lchild)
					pre->lchild=s;
				else if(p==pre->rchild)
					pre->rchild=s;
				s->lchild=p->lchild;
				s->rchild=p->rchild;
			}
		}
		free(p);
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
	//int a[12]={7,6,9,8,12,10},h,hc;//RR-根
	int a[12]={5,2,7,6,9,12,1,3,4,8,10,11};//RR非根
	//int a[12]=[7,6,19,11,22,12],h,hc;//RL-根
	//int a[12]={5,3,2,4,1,7,6,19,11,12,22},h,hc;//RL-根
	//int a[12]={27,19,11,22,12,32},h,hc;//LL-根
	//int a[12]={50,60,27,19,11,22,12,32},h,hc;//LL-非根
	//int a[12]={27,19,11,22,32,23},h,hc;//LR-根
	//int a[12]={50,60,27,19,11,22,32,23},h,hc;//LR-非根
	struct BSTNode *bst=NULL,*p=NULL;
	bst=CreateBST(a,12);
	InOrder(bst);
	printf("\n");
	InsertBST(&bst,16);
	InOrder(bst);
	printf("\n");
	DeleteBST(&bst,5);
	InOrder(bst);
	p=SearchBST(bst,16);
	if(p)
		printf("\n找到了! \n");
	else
		printf("\n没找到! \n");
	DeleteBST(&bst,5);
	InOrder(bst);
	qasl(bst,1);
	printf("\nASL:%d/%d\n",zbjcs,jdgs);
	FreeBST(bst);
	funp("调试理解二叉树的创建、插入、删除程序实现");
	}












































































