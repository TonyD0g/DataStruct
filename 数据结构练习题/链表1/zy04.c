#include<stdio.h>
void fun(int n);
int main()
{
	fun(1234);
	return 0;
}
void fun(int n)
{
	printf("%d",n%10);
	if(n/10!=0)
		fun(n/10);
}