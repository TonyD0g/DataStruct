#include<stdio.h>
#include<stdlib.h>
#include <time.h>
void fun1(char s[])
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	printf("%s\n",s);
	printf("%s",asctime(timeinfo));
}
struct BSTNode//数据结构类型
{
	int data;
	struct BSTNode *lchild,*rchild;
};
struct BSTNode *CreateBST(int a[],int n)//根据数组a创建二叉树排序树
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
			pre=p;
			if(a[i]<p->data)
				p=p->lchild;
			else if(a[i]>p->data)
				p=p->rchild;
			else
				break;
		}
		if(!p)//如果p等于空，没找到相等结点
		{
			p=(struct BSTNode *)malloc(sizeof(struct BSTNode));
			p->data=a[i];
			p->lchild=NULL;
			p->rchild=NULL;
			if(a[i]<pre->data)
				pre->lchild=p;
			else
				pre->rchild=p;
		}
	}
	return root;
}
void InOrder(struct BSTNode *root)//中序遍历二叉排序树
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
void FreeBST(struct BSTNode *root)//释放二叉排序树空间
{
	if(root!=NULL)
	{
		FreeBST(root->lchild);
		FreeBST(root->rchild);
		free(root);
	}
}

void main()
{
	//int a[12]={7,6,9,8,12,10},h,hc;//RR-根
	int a[12]={5,2,7,6,9,12,1,3,4,8,10,11};//RR-非根
	//int a[12]={7,6,19,11,22,12},h,hc;//RL-根
	//int a[12]={5,3,2,4,1,7,6,19,11,12,22},h,hc;//RL-非根
	//int a[12]={27,19,11,22,12,32},h,hc;//LL-根
	//int a[12]={50,60,27,19,11,22,12,32},h,hc;//LL-非根
	//int a[12]={27,19,11,22,32,23},h,hc;//LR-根
	//int a[12]={50,60,27,19,11,22,32,23},h,hc;//LR-非根
	struct BSTNode *bst=NULL,*p=NULL;
	int ys=1;
	bst=CreateBST(a,12);
	InOrder(bst);
	printf("\n");
	FiOrder(bst);
	printf("\n");


	FreeBST(bst);

	fun1("平衡二叉树判断及调整程序实现");
}
