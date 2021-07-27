#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
	char data;
	struct node *next;	
}listnode;
listnode* INITLIST()
{
	listnode *hd=(listnode *)malloc(sizeof(listnode));
	hd->next=NULL;
	return hd;
}

void CREALISTWC(listnode *hd,char a[])
{
	int i=0;
	listnode *r=hd;
	while(a[i]!='\0')
	{
		listnode *p=(listnode*)malloc(sizeof(listnode));
		p->data=a[i];
		p->next=NULL;
		r->next=p;
		r=p;
		i++;
	}
}
void PRINTLIST(listnode *hd)
{
	listnode *p=hd->next;
	while(p!=NULL)
	{
		printf("%c ",p->data);
		p=p->next;
	}
	printf("\n");
}
void FREE(listnode *hd)
{
	while(hd->next!=NULL)
	{
		listnode *p=hd->next;
		hd->next=p->next;
		free(p);
	}
	free(hd);
}
void fun(listnode *hd1,listnode *hd2,listnode *hd3)
{
	listnode *p=hd1,*r2=hd2,*r3=hd3,*q=NULL;
	while(p->next!=NULL)
	{
		if(p->next->data>='A'&&p->next->data<='Z')
		{
			q=p->next;
			p->next=q->next;
			q->next=NULL;
			r2->next=q;
			r2=r2->next;
			
		}
		else if(p->next->data>='a'&&p->next->data<='z')
		{
			q=p->next;
			p->next=q->next;
			q->next=NULL;
			r3->next=q;
			r3=r3->next;
		}
		else
		{
			p=p->next;
		}
	}
	
}
int main()
{
	int i;
	listnode *hd1=NULL,*hd2=NULL,*hd3=NULL;
	hd1=INITLIST();
	hd2=INITLIST();
	hd3=INITLIST();
	CREALISTWC(hd1,"abADddDD23456a88Sd");
	PRINTLIST(hd1);
	fun(hd1,hd2,hd3);
	printf("hd1:\n");
	PRINTLIST(hd1);
	printf("hd2:\n");
	PRINTLIST(hd2);
	printf("hd3:\n");
	PRINTLIST(hd3);
	FREE(hd1);
	FREE(hd2);
	FREE(hd3);
	return 0;
	
}
