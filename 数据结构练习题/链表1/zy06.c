#include<stdio.h>
#include<stdlib.h>
int fun(int a[],int i,int j,int *w);

int main()
{
	int y,*w,z;
	int a[10]={3,2,1,6,5,4,9,8,7,10};
	z=0;
	w=&z;
	y=fun(a,0,9,w);
	printf("运行结果%d，运行次数%d\n",y,*w);
	return 0;
}
int fun(int a[],int i,int j,int *w)
{
	int t1,t2,m,t;
	*w=*w+1;
	if(i==j)
	{
		t=a[i];
	}
	else
	{
		m=(i+j)/2;
		t1=fun(a,i,m,w);
		t2=fun(a,m+1,j,w);
		t=t1>t2?t1:t2;
	}
	
	
	return t;

}
