#include<stdio.h>
#include<math.h>
#define N 10000

int main() {
	int a, a1,len,c ;
	int i, j;
	int b[N]= { 0 };
	printf("输入要计算阶乘的数字：");
	scanf("%d", &a);
	a1 = a;
	len = floor(log10(a)) + 1;
	for (i = 0; i<len; i++) {
		b[i] = (int)a1%10;
		a1 = floor(a1 / 10);
	}
	for (j = a - 1; j > 0; j--) {
		i = N;
		while (b[i - 1] == 0) {
			i--;
			if (b[i] != 0)
				break;
		}
		len = i;
		for (i = 0; i < len; i++) {
			b[i] = b[i] * j;
		}
		for (i = 0; i < N-1 ; i++) {
			if (b[i] >= 10) {
				b[i + 1] = b[i + 1] + floor(b[i] / 10);
				b[i] = b[i]%10;
			}
		}
	}
	i = N;
	while (b[i - 1] == 0) {
		i--;
		if (b[i] != 0)
			break;
	}
	len = i;
	for (i=len-1; i>=0; i--) {
		printf("%d", b[i]);
	}
}

