#include<stdio.h>
#include<math.h>
#define M 100000
#define N 100000
int main() {
	int a[M]={0},i,j,n,l=0,jw;
	int h[N]={0},h1=0,hjw;
	scanf("%d",&n);
	a[0]=1;
	for(i=1; i<=n; i++) {
		jw=0;
		for(j=0; j<=l; j++) {
			jw=jw+a[j]*i;
			a[j]=jw%10;
			jw=jw/10;
		}
		while(jw!=0) {
			l++;
			a[l]=jw%10;
			jw=jw/10;
		}
		hjw=0;
		h1=l>h1?l:h1;
		for(j=0; j<=h1; j++) {
			h[j]=h[j]+a[j]+hjw;
			hjw=h[j]/10;
			h[j]=h[j]%10;
		}
		if(jw!=0)
			h[++h1]=jw;
	}
	for(i=h1; i>=0; i--) {
		printf("%d",h[i]);
	}
	return 0;
}
