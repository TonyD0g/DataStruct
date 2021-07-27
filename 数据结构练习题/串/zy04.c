#include "stdio.h"
#include "stdlib.h"
#include "string.h"
struct str {
	char word;
	int num;//字母出现的次数
	struct str *next;
};//定义链表节点类型
struct str *init() {
	struct str *hd=(struct str *)malloc(sizeof(struct str));
	hd->next=NULL;
	return hd;
}
void SF(struct str *hd) {
	struct str *p=hd->next;
	while(p!=NULL) {
		hd->next=p->next;
		free(p);
		p=hd->next;
	}
	free(hd);
}
void print (struct str *hd) {
	struct str *p=hd->next;
	int i=0;
	while(p!=NULL) {
		printf ("%c:%d\n",p->word,p->num);
		p=p->next;
		i++;
		if(i>=20)
			break;
	}
}
void savetofile(struct str *hd) {
	struct str *p=hd->next;
	FILE *fp=fopen ("D:\\2.txt","w" );
	while(p!=NULL) {
		fprintf(fp,"%c:%d\n",p->word,p->num);
		p=p->next;
	}
	fclose(fp);
}
void px (struct str *hd) {
	struct str *p=hd->next->next,*r,*t;
	hd->next->next=NULL;
	while(p!=NULL) {
		r=p;
		p=p->next;
		t=hd;
		while(t->next!=NULL&&t->next->num>r->num)
			t=t->next;
		r->next=t->next;
		t->next=r;
	}
}
void find (struct str *hd, char s) {
	struct str *p=hd->next;
	while(p!=NULL) {
		if(p->word==s)
			break; //如果找到跳出
		p=p->next;
	}
	if(p==NULL) { //没找到单词，作为一个新结点加入链表
		struct str *p=(struct str *)malloc(sizeof(struct str));
		p->word=s;
		p->num=1;
		p->next=hd->next;
		hd->next=p;
	} else //找到了个数加1
		p->num++;

}
void sclb(struct str *hd) {
	FILE*fp=fopen("D:\\1.txt ","r");
	char c;
	while(!feof(fp)) {
		c=fgetc(fp);
		find(hd,c);
		}
	fclose(fp);
}
void main() {
	struct str *head=init();
	sclb(head) ;
	px(head);
	print(head) ;
	savetofile(head);
	SF(head);
}

