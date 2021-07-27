#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 20
#define Q 40
//定义数据结构


struct CHENGKE//创建乘客结构体
{
    
    
    char xingming[10];//姓名
    char zhengjianhao[20];//证件号
    int dingpiaoshu;//订票数
    char hangbanhao[10];//乘坐航班号
    char bianhao[10];//编号
};


struct HANGBAN//创建航班结构体
{
	char hangbanming[10];//航班名
    char qifeichengshi[20];//起飞城市/
    char jiangluochengshi[20];//降落城市
    char qifeishijian[20];//起飞时间
    char jiangluoshijian[20];//降落时间
    int zuoweishu;//座位数
    char piaojia[5];//票价
    char zhekou[5];//折扣
	CHENGKE chengke[20];
    int sit;
};
int menu_select()
{
int c;
printf("请按任意键进入主菜单\n");//提示按任意键继续
getchar();//读入任意字符
printf("**********************************欢迎进入************************************\n");
printf("                            南方航空飞机订票管理系统\n\n");
printf(" ***********************************主菜单*************************************\n\n");
printf("                           0.输入航班信息\n");
printf("                           1.列出航班的信息\n");
printf("                           2.按航班号查询航班信息\n");
printf("                           3.按城市来查询航班\n");
printf("                           4.订票\n");
printf("                           5.退票\n");
printf("                           6.修改飞机航班的信息\n");
printf("                           7.保存文件\n");
printf("                           8.退出\n");
printf(" *************************欢迎下次使用，再见*****************************************\n\n");
do
{
printf("\n 请输入你要选择的功能选项(0~8):");
scanf("%d",&c);//输入选择项
}
while(c<0||c>8);
return c;//所输入的数字不在范围内
}





//输入函数
int enter(HANGBAN t[])
{
int i,k,n,m,w,j;
char *s;
printf("输入航线总数(n<=40):");//输入航线总数
scanf("%d",&n);
while(n>40||n<0)
{
printf("You  put  is   wrong,please  put  again(0<n<=40):");
scanf("%d",&n);
}
printf("                 请输入航班的信息\n\n");
printf("航班名       起飞城市        降落城市        出发时间        降落时间        剩下的座位       价格       折扣\n");
for(i=0;i<n;i++)
{
scanf("%s",t[i].hangbanming);
scanf("%s",t[i].qifeichengshi);
scanf("%s",t[i].jiangluochengshi);
scanf("%s",t[i].qifeishijian);
scanf("%s",t[i].jiangluoshijian);
scanf("%d",&t[i].zuoweishu);
scanf("%s",t[i].piaojia);
scanf("%s",t[i].zhekou);
}

printf("*****************************************************************************************\n");
for(i=0;i<n;i++)t[i].sit=0;
return n;//返回记录条数
}








//显示记录，参数为记录数组和记录条数
void list(HANGBAN t[],int n)
{
int i;
printf("航班名     起飞城市        降落城市         出发时间        降落时间     剩下的座位   价格    折扣\n");
printf("*************************************************航班信息如下**************************************************************\n");
for(i=0;i<n;i++)
printf("%-12s%-12s%-12s%-12s%-14s%-10d%-8s%-10s\n",t[i].hangbanming,t[i].qifeichengshi,t[i].jiangluochengshi,t[i].qifeishijian,t[i].jiangluoshijian,t[i].zuoweishu,t[i].piaojia,t[i].zhekou);
printf(" **************************************************end**********************************************************************\n");
}






//按航班号查找记录
void search1(HANGBAN t[],int n)
{char s[20];//保存待查找航班名字符串
int i;
printf("输入你想查找的航班名:");
scanf("%s",s);//输入待查找航班名
for(i=0;i<n;i++)//从第一条记录开始比较
{
if(strcmp(s,t[i].hangbanming)==0)//记录中的航班名和待比较的是否相等
break;//找到要找的航班，返回
}
if(i>n-1)//没有找到所要找的航班
printf("---------------------------很抱歉，没有找到您所要查找的航班-------------------------\n");
else
{
printf("航班名   起飞城市    降落城市      出发时间        降落时间     剩下的座位   价格     折扣\n");//显示记录
printf("------------------------------------------------------------------------------\n");
printf("%-12s%-12s%-12s%-12s%-14s%-10d%-8s%-10s\n",t[i].hangbanming,t[i].qifeichengshi,t[i].jiangluochengshi,t[i].qifeishijian,t[i].jiangluoshijian,t[i].zuoweishu,t[i].piaojia,t[i].zhekou);
}
}



//按起降城市查找记录
void search2(HANGBAN t[],int n)
{
char s1[20];
char s2[20];
int i;
printf("输入起飞城市名称:");
scanf("%s",s1);//输入起飞城市名
printf("输入降落城市名称:");
scanf("%s",s2);//输入降落城市名
for(i=0;i<n;i++)//从第一条记录开始比较
{
if((strcmp(s1,t[i].qifeichengshi)==0)&&(strcmp(s2,t[i].jiangluochengshi)==0))//记录中的城市和待比较的是否相等
break;//相等，程序结束
}
if(i>n-1)//没有找到所要找的航班
printf("-------------------------------------很抱歉，没有找到您所要查找的航班---------------------------------------\n");
else
{
printf("航班名     起飞城市     降落城市     出发时间       降落时间     剩下的座位     价格     折扣\n");//找到,显示记录
printf("------------------------------------------------------------------------------\n");
printf("%-12s%-12s%-12s%-12s%-14s%-10d%-8s%-10s\n",t[i].hangbanming,t[i].qifeichengshi,t[i].jiangluochengshi,t[i].qifeishijian,t[i].jiangluoshijian,t[i].zuoweishu,t[i].piaojia,t[i].zhekou);
}
}




//订票
void book(HANGBAN t[],int n)
{
char s[20],bianhao1[10],xingming1[10],zhengjianhao1[20],hangbanhao1[10];
int i,j=0,m,k,dingpiaoshu1;
printf("输入你想预订的票数:");
scanf("%d",&m);
printf("--------------------------------------------------------------------------------------------------------------\n");
printf("编号       姓名       证件号          订的票数             航班号\n");//提示信息
for(k=0;k<m;k++)
{
scanf("%s",bianhao1);
scanf("%s",xingming1);
scanf("%s",zhengjianhao1);
scanf("%d",&dingpiaoshu1);
scanf("%s",hangbanhao1);
for(i=0;i<n;i++)//从第一条记录比较，是否有要找的航班
{
if(strcmp(hangbanhao1,t[i].hangbanming)==0)//记录中的航班名和待比较的是否相等
{
j=t[i].sit;
strcpy(t[i].chengke[j].bianhao,bianhao1);
strcpy(t[i].chengke[j].xingming,xingming1);
strcpy(t[i].chengke[j].zhengjianhao,zhengjianhao1);
t[i].chengke[j].dingpiaoshu=dingpiaoshu1;
strcpy(t[i].chengke[j].hangbanhao,hangbanhao1);
t[i].zuoweishu=t[i].zuoweishu-dingpiaoshu1;
t[i].sit++;
break;//相等，程序结束
}
}
if(i>n-1)//没有找到所要找的航班
{
printf("-------------------------------------------很抱歉，没有您要找的航班---------------------------------------\n");
m=m+2;
k++;
}
}
}



void save(HANGBAN t[],int lenght)//保存文件
{
	
	 const char* filename1 = "E:/X.txt";
    int dataindex =lenght;//文件的长度
    FILE* fp1 = fopen(filename1 , "w");
	if (fp1 == NULL)//文件已满
	{
	    puts("Fail to open file!");//打开文件失败
	    exit(1);
	}
	for (int i = 0; i < dataindex; i++)
	{
	  fprintf(fp1, "%-12s%-12s%-12s%-12s%-14s%-10d%-8s%-10s\n",t[i].hangbanming,t[i].qifeichengshi,t[i].jiangluochengshi,t[i].qifeishijian,t[i].jiangluoshijian,t[i].zuoweishu,t[i].piaojia,t[i].zhekou);
	}//保存的数据内容
	fclose(fp1);
        printf("Data saved.\n");//数据已保存

}



//退票
void quit(HANGBAN t[],int n)
{
char s1[20],s2[20];//保存待查找航班名和证件号字符串
int i,k,j,h,l,ch;
printf("请输入你想退订的航班号:");
scanf("%s",s1);//输入待查找航班名
printf("请输入你的证件号:");
scanf("%s",s2);//输入待查找证件号
printf("编号     姓名       证件号        订的票数  航班号\n");//显示提示
printf("------------------------------------------------------------\n");
for(i=0;i<n;i++)//从第一条记录开始，直到最后一条
{
for(j=0;j<t[i].sit;j++)
if((strcmp(s1,t[i].chengke[j].hangbanhao)==0)&&(strcmp(s2,t[i].chengke[j].zhengjianhao)==0))
{
printf("%-11s%-16s%-16s%-14d%-10s\n",t[i].chengke[j].bianhao,t[i].chengke[j].xingming,t[i].chengke[j].zhengjianhao,t[i].chengke[j].dingpiaoshu,t[i].chengke[j].hangbanhao);
t[i].zuoweishu=t[i].zuoweishu+t[i].chengke[j].dingpiaoshu;
l=j;
h=i;
break;
}
}
i=h;
if(i>n-1)//如果整数i值大于n-1,说明没找到
printf("没有找到\n");
else
{
printf("你是否确认删除(1/0)\n");//确认是否要删除
scanf("%d",&ch);//输入一个整数或
if(ch==1)//如果确认删除整数为
{
for(k=l+1;k<t[i].sit;k++)
{
strcpy(t[i].chengke[k-1].bianhao,t[i].chengke[k].bianhao);//将后一条记录的姓名拷贝到前一条
strcpy(t[i].chengke[k-1].xingming,t[i].chengke[k].xingming);
strcpy(t[i].chengke[k-1].zhengjianhao,t[i].chengke[k].zhengjianhao);
t[i].chengke[k-1].dingpiaoshu=t[i].chengke[k].dingpiaoshu;
strcpy(t[i].chengke[k-1].hangbanhao,t[i].chengke[k].hangbanhao);
}
t[i].sit--;
}
printf("退票成功!!\n");//提示退票成功
}
}

//修改航班信息
void channge(HANGBAN t[],int n)
{
char s[20];//要修改乘客的姓名
int i,j;
printf("请输入你要修改的航班号:");//提示信息
scanf("%s",s);//输入航班名
for(i=0;i<n;i++)//从第一条记录开始，直到最后一条
{
if(strcmp(s,t[i].hangbanming)==0)//记录中的航班名和所要查找的航班是否相等
break;//相等，程序结束
}
if(i>n-1)//没找到
printf("-------------------------很抱歉，没有找到您要找的航班-------------------------------\n");
else
{
printf("--------------------------------------------------------------------------------------\n");
printf("航班名    起飞城市   降落城市        出发时间         降落时间    剩下的座位   价格    折扣\n");//找到，显示原先记录
printf("%-12s%-12s%-12s%-12s%-14s%-10d%-8s%-10s\n",t[i].hangbanming,t[i].qifeichengshi,t[i].jiangluochengshi,t[i].qifeishijian,t[i].jiangluoshijian,t[i].zuoweishu,t[i].piaojia,t[i].zhekou);
printf("please input the new information:\n");
scanf("%s",t[i].hangbanming);//输入航班名
scanf("%s",t[i].qifeichengshi);//输入起飞城市
scanf("%s",t[i].jiangluochengshi);//输入降落城市
scanf("%s",t[i].qifeishijian);//输入起飞时间
scanf("%s",t[i].jiangluoshijian);//输入降落时间
scanf("%d",t[i].zuoweishu);//输入座位号
scanf("%s",t[i].piaojia);//输入票价
scanf("%s",t[i].zhekou);//输入折扣
}
}

void main()
{
int i;
HANGBAN flight[Q];
int length;//保存记录长度
for(i=0;i>-1;i++)
{
switch(menu_select())//调用主菜单函数，返回值整数作开关语句的条件
{
case 0:length=enter(flight);break;
case 1:list(flight,length);break;
case 2:search1(flight,length);break;
case 3:search2(flight,length);break;
case 4:book(flight,length);break;
case 5:quit(flight,length);break;
case 6:channge(flight,length);break;
case 7:save(flight,length);break;
case 8:exit(0);//退出，程序结束
}
}
}