#include<stdio.h>
#include<stdlib.h>
struct xs{
	int data;
	struct xs *next;
};
void main()
{
	int i;
	struct xs *head=NULL,*p=NULL,*r=NULL;
	head=(struct xs *)malloc(sizeof(struct xs));
	head->next=NULL;
	r=head;
	for(i=0;i<=9;i++)
	{
		p=(struct xs *)malloc(sizeof(struct xs));
		p->data=i*i;
		p->next=NULL;
		r->next=p;
		r=p;
	}
	p=head->next;
	while(p!=NULL)
	{
		printf("%d %x\n",p->data,p);
		p=p->next;
	}

}
