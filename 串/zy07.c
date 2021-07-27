#include <stdio.h>
#include <stdlib.h>
void sort(int *a ,int size) {
	int i = 0;
	int j = size-1;
	for(i=0; i!=j; i++) {

		if(a[i]%2==0)
			continue;
		else {
			int t = a[i];
			a[i] = a[j];
			a[j] = t;
			if(a[j]%2!=0)
				j--;
			i--;
		}
	}
}
int main() {
	int a[10];
	int i;int size = sizeof(a)/sizeof(a[0]);
	printf("«Î ‰»Î¬“–Ú ˝◊÷£∫\n");
	for(i=0; i<10; i++)
	{
		scanf("%d",&a[i]);
	}
	
	sort(a,size);
	for(i=0; i<size ; i++) {

		printf("%d ",a[i]);
	}
	return 0;
}

