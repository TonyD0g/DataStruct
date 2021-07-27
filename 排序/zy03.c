#include<stdio.h>
#include "time.h" 
#define N 6
 int fun(int arr[],int low,int high)
 {
  int key;
  key=arr[low];
  while(low<high)
  {
    while(low<high && arr[high]>=key)
      high--;
    if(low<high)
      arr[low++]=arr[high];
    while(low<high && arr[low]<=key)
      low++;
    if(low<high)
      arr[high--]=arr[low];
   }
   arr[low]=key;
   return low;
 } 
void quick_sort(int arr[],int start,int end)
{
  int pos;
  if(start<end)
  {
  pos=fun(arr,start,end);
  quick_sort(arr,start,pos-1);
  quick_sort(arr,pos+1,end);
  }
}
void fun1(char s[]) 
{ 
time_t rawtime; 
struct tm * timeinfo; 
time ( &rawtime ); 
timeinfo = localtime ( &rawtime ); 
printf("%s\n",s); 
printf("%s", asctime (timeinfo) ); 
} 
int main()
{
  int i;
  int arr[N]={35,12,74,73,23,45};
  printf("初始化：\n");
  for(i=0;i<N;i++)
  {
    printf("%d ",arr[i]);
  }
  printf("\n结果为：");
  quick_sort(arr,0,N-1);
  for(i=0;i<N;i++)
  {
    printf("%d ",arr[i]);
  }
  	fun1("编程实现快速排序实现"); 
  return 0;
 }