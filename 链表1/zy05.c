#include<stdio.h>
void fun(int n);
int main()
{
	fun(4);
	return 0;
}
void fun(int n)
{
	int i;
	if(n!=0)
	{
		fun(n-1);
		for(i=1;i<=n;i++)
			printf("%3d",n);
		printf("\n");

	}
}