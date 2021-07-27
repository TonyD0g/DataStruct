#include "stdio.h"
#include "stdlib.h"
#include "string.h"
struct str {
	char word[20];//单词最多19个字符
	int num;//单词出现的次数
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
		printf ("%s:%d\n",p->word,p->num);
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
		fprintf(fp,"%s:%d\n",p->word,p->num);
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
void find (struct str *hd, char s[]) {
	struct str *p=hd->next;
	while(p!=NULL) {
		if(strcmp(p->word,s)==0)
			break; //如果找到跳出
		p=p->next;
	}
	if(p==NULL) { //没找到单词，作为一个新结点加入链表
		struct str *p=(struct str *)malloc(sizeof(struct str));
		strcpy(p->word,s);
		p->num=1;
		p->next=hd->next;
		hd->next=p;
	} else //找到了个数加1
		p->num++;

}
void sclb(struct str *hd) {
	FILE*fp=fopen("D:\\1.txt ","r");
	int i=0,bz=0,k;
	char c,substr[20];//假设输入字符最多10000个，单词最大19个字符
	while(!feof(fp)) {
		c=fgetc(fp);
		if(c>='A'&&c<='Z')
			c=c+32;
		if(c>='a'&&c<='z') { //如果是字母
			if(bz==0) { //若bz=0表示新单词开始
				k=0;
				substr[k++]=c;
				bz=1;//标记单词开始
			} else //非新单词开始，在原单词后面加字符
				substr[k++]=c;
		} else { //如果是非字母字符，单词结束
			if(bz==1) { //若遇到的第一个空格，标记单词结束
				bz=0;//一个单词结束，新单词开始标志，再遇到非英文字母|字符重新生成新的单词
				substr[k]='\0';//手动加生成的子串结束符标志
				find (hd,substr) ;
			}//否则若连续的第2,3,4....个单词，什么也不做
		}
	}
	if(bz==1) {
		substr[k]='\0';//生成最后的单词
		find(hd,substr);
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










