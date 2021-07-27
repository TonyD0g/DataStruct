#include "stdio.h"
#include <time.h>
int c=0;//全局变量，用于记录交换次数
void swap(int a[],int i,int j)//交换a[i]和a[j]的值并计数
{
	int temp;
	temp=a[i];
	a[i]=a[j];
	a[j]=temp;
	c++;
}
void fun(char s[])
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	printf("%s\n",s);
	printf("%s",asctime(timeinfo));
}
void heapadjust(int a[],int m,int n)//调整a[m]到a[n]为大根堆
{
	int i;
	for(i=2*m;i<=n;i*=2)
	{
		if(i+1>n)//如果m没有右孩子,只有左孩子,i+1为m的右孩子
		{
			if(a[i]>a[m])//如果左孩子大于根，交换左孩子和根
			{
				swap(a,i,m);
				m=i;//为子树连锁交换做准备
			}
			else 
				break;
		}
		else if(i+1<=n)//如果m有 左右两个孩子,i+1为m的右孩子
		{
			if(a[i+1]>a[i])//如果右孩子大于左孩子
			{
				if(a[i+1]>a[m])//如果大的右孩子大于根，交换根和右孩子
				{
					swap(a,i+1,m);
					i++;
				    m=i;
				}
				else//否则如果大的孩子都小于等于根，则小的更小于根，跳出不用调整
					break; 
			}
			else//如果左孩子大于等于右孩子
			{
				if(a[i]>a[m])//如果大的(或相等的)左孩子大于根，交换根和左孩子
				{
					swap(a,i,m);
					m=i;//为子树连锁交换做准备
				}
				else
					break; 
			}
		}
	}
}
					
void crtheap(int a[],int n)//初始化创建一个大顶堆
{
	int i;
	for(i=n/2;i>=1;i--)//n/2为最后一个双亲节点，依次向前建立大顶堆
	{
		heapadjust(a,i,n);
	}
}
void heapsort(int a[],int n)
{
	int i;
	crtheap(a,n);//第一次调整为大根堆
	for(i=n;i>=2;i--)//n-1趟交换/调整
	{
		swap(a,1,i);//将堆顶最大数(第一个数)，放到a[i]位置
		heapadjust(a,1,i-1);//对剩下的a[1]到a[i-1],再次调整为大根堆
	}
}



void main()
{
	int i;

	int a[11]={-1,75,54,22,63,04,33,97,16,75,44};//为方便树左右孩子处理，a[0]未使用
	heapsort(a,10);

	for(i=1;i<=10;i++)
		printf(" %d",a[i]);	printf("交换数据%d次\n",c);
	printf("\n");
	fun("堆排序程序实现");
}
