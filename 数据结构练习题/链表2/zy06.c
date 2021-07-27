#include <stdio.h>
#include <stdlib.h>
typedef struct xs
{
    int data;
    struct xs *next;
}link;
 
int creat(int n, int m)
{
 link *head, *p, *s, *q;
 int i,t;int data1;

    head = (link *) malloc(sizeof(link));
    p = head;
    p->data = 1;
    p->next = p;
    for (i = 2; i <= n; i++)
    {
        s = (link*) malloc(sizeof(link));
        s->data = i;
        s->next = p->next;
        p->next = s;
        p = p->next;
    }
    p = head;
    t = n;
    q = head;
    while (t != 1)
    {

        for (i = 1; i < m; i++)
        {
            p = p->next;
        }
 

        while (q->next != p)
        {
            q = q->next;
        }
        q->next = p->next;
        s = p;
        p = p->next;
        free(s);
        t--;
    }
    data1=p->data;
    free(p);
    return data1;
 
}
int  main()
{
    int  n, m;
    int k,ii,i;
	printf("请输入猴子个数：\n");
	scanf("%d",&n);
	printf("请输入规定的出圈数：\n");
	scanf("%d",&m);
	printf("----------\n");
      printf("%d\n",creat(n,m));
 
    return 0;
}