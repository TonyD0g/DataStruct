#include<stdio.h>
struct xs{
	int data;
	struct xs *next;
};
void main()
{
	int i;
	struct xs s[10],*p=NULL;
	for(i=0;i<=9;i++)
	s[i].data=i*i;
	p=s;
	for(i=0;i<=9;i++)
	{
		printf("%d %x\n",p->data,p);
		p++;
	}
}