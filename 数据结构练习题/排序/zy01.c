#include<stdio.h>
#include "time.h" 
void ShellInsert(int a[], int gap, int k, int n)		//(数组a，增量gap，初始位置k，数组大小n)
{	//对当前数组做一次希尔插入排序。增量为gap
	int i, j, tmp;
	for(i = k + gap;i < n;i += gap)
	{
		tmp = a[i];
		j = i - gap;

		while(j >= 0 && a[j] > tmp)
		{
			a[j + gap] = a[j];
			j = j - gap;
		}
		a[j + gap] = tmp;
	}
}

void ShellSort(int a[], int n)
{
	int gap, i;
	for(gap = n / 2;gap > 0;gap /= 2)			//获取每次增量大小
	{
		for(i = 0;i < gap;i++)					//数组被分为gap组
			ShellInsert(a, gap, i, n);
	}
	printf("\n结果为：\n");
	for(i = 0;i < n;i++)
		printf("%d ", a[i]);
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
	int a[10] = {43, 3, 64, 97, 76, 13, 27, 49, 55, 47};
		int i;		int n=10;
	printf("初始化：\n");
	for(i=0;i<10;i++)
		printf("%d ",a[i]);

	//	int n = sizeof(a)/sizeof(*a);		//获取数组长度

ShellSort(a, n);

	getchar();
	fun("编程实现希尔排序实现");
	return 0;
}
