#include "stdio.h"
#define maxsize 100
#define MAXRC 10//矩阵M、Q行数+1
typedef struct { //三元组元素结构定义
	int i,j;
	int e;
} triple;
typedef struct { //三元组存储定义
	triple data[maxsize+1];
	int rpos[MAXRC];
	int mu, nu,tu;
} RLtsmat;
void cjsyzRL(RLtsmat *s , int a[],int h,int l) { //创建三元组
	int i,j,k=1,num[MAXRC];
	s->mu=h;
	s->nu=l;
	for(i=0; i<=h-1; i++)
		for(j=0; j<=l-1; j++)
			if(a[i*l+j]!=0) {
				s->data[k].i=i+1;
				s->data[k].j=j+1;
				s->data[k].e=a[i*l+j];
				k++;
			}

	s->tu=k-1;
	for(i=1; i<=s->mu; i++)
		num[i]=0;
	for(i=1; i<=s->tu; i++)
		num[s->data[i].i]++;
	s->rpos[1]=1;
	for(i=2; i<=s->mu; i++)
		s->rpos[i]=s->rpos[i-1]+num[i-1];
}
void psyz(RLtsmat s) { //显示三元组

	int i;
	printf("hs:%d ls:%d flgs:%d\n",s.mu,s.nu,s.tu);
	printf("syz:\n");
	for (i=1; i<=s.tu; i++)
		printf("   %d   %d   %d\n",s.data[i].i,s.data[i].j, s.data[i].e);
	printf("rpos:\n");
	for(i=1; i<=s.mu; i++)
		printf("   %d  %d\n",i,s.rpos[i]);
}
int MultSmatrix(RLtsmat M,RLtsmat N,RLtsmat*Q) {
	int ctemp[MAXRC],arow,tp,p,q,ccol,t,brow,i;
	if(M.nu !=N.mu) return 0;
	if(M.tu*N.tu==0) return 0;//若有一个非零元素个数为0
	Q->mu=M.mu;
	Q->nu=N.nu;
	Q->tu=0;//行列数、非零元素个数初始化
	for(arow=1; arow<=M.mu; arow++) { //遍历M矩阵各行
		for(i=1; i<=M.nu; i++)//M中第arow行各列累加器清理
			ctemp[i]=0;
		Q->rpos[arow]=Q->tu+1;//计算结果Q矩阵三元组第arow行非零元素
		if (arow<M.mu)//计算M三元组第arow行在三元组中的结束位置(-1)
			tp=M.rpos[arow+1];
		else
			tp=M.tu+1;//取M三元组第arow+1行起始位置
		for (p=M.rpos[arow]; p<tp; p++) { //M中第arow行在三元组中的范围
			brow=M.data[p].j;//取M中第arow行p元素的列
			if(brow<N.mu)
				t=N.rpos[brow+1];
			else
				t=N.tu+1;//取N三元组第brow+1行起始位置
			for(q=N.rpos[brow]; q<t; q++) { //取N三元组第brow行各元素
				ccol=N.data[q].j;//取N矩阵三元组q元素列
				ctemp[ccol]+=M.data[p].e*N.data[q].e;
			}
		}
		for(ccol=1; ccol<=Q->nu; ccol++) {
			if(ctemp[ccol]!=0) {
				if(++Q->tu>maxsize) return 0;
				Q->data[Q->tu].i=arow;
				Q->data[Q->tu].j=ccol;
				Q->data[Q->tu].e=ctemp[ccol];
			}
		}
	}
	return 1;
}
void main() {

	//int s1[9]={1,0,3,0,2,4,3,4,3} ,s2[9]={3,2,0,2,3,2,0,2,3};
	int s1[12]= {3,0,0,5,0,-1,0,0,2,0,0,0} , s2[8]= {0,2,1,0,-2,4,0,0};
	RLtsmat c,d,e;
	cjsyzRL(&c,s1,3,4);
	cjsyzRL(&d,s2,4,2);
	MultSmatrix(c,d,&e);
	psyz(c);
	psyz(d);
	psyz(e);
}
