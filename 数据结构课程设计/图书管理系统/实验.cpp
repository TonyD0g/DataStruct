#include<stdio.h>//如果读者成功借阅书籍，则利用“ReaderUser结构体”
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<time.h>
#define maxsize 10
int AdminKey=0;//检测管理员是否登陆成功，为1则登陆成功
int UserKey=0;//检测读者是否登陆成功，为1则登陆成功
char bookname1[10];
int MaxSize=0;//读者最大借阅书
typedef struct bookinformation//图书信息,只有管理员能访问
{
	char bookname[maxsize];//书名
	int bookstate;//书的状态 0：被借阅，1：没被借阅;
	int timelimit;//若该图书被借阅，则启动时间限制,时间限制默认为30天;
	bookinformation *next;//next指针
}bookinformation;
//读者账户文件结构：
//账号 密码

typedef struct ReaderUser//读者链表
{
	char UserName[10];
	int BookSore;
	int Maxsize;
	ReaderUser *next;
}ReaderUser;

ReaderUser *RdUserHd;//控制读者账户的单链表！(重要！)
bookinformation *hd;//控制书名的单链表！(重要！)
ReaderUser *p=(ReaderUser *)malloc(sizeof(ReaderUser));


void Actorfun(char s[])//输出版权信息
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	printf("%s\n",s);
	printf("%s",asctime(timeinfo));
}
void Timefun()//借书日期
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	printf("借书时间为%s\n借书期限为30天\n----------------------------------------------\n",asctime(timeinfo));
}
void CreateMyAccount()//创建账户	（success）
{	char StuUsername[10];
	char StuPassword[10];
	char code[10];//密钥
	char compare[10];//比较字符串（中间商）
	FILE *fpcode;//读密钥文件
	int flag,keyfile;//keyfile:用户选择要创建管理员账户还是读者账户
	printf("请选择你要创建的为管理员账户还是读者账户:\n输入1：创建管理员账户\n输入2：创建读者账户\n");scanf("%d",&keyfile);
	//文件操作：将账号，密码写入到文件	: Account.txt		中
	FILE *fp;
	if(keyfile==1)//x=1时，创建管理员账户
	{
		printf("创建管理员账户需要密匙！请输入你的密匙！\n");
		scanf("%s",&code);
		fpcode=fopen("code.txt","r");
		if(fpcode==NULL)
		{
			printf("密钥文件不存在！\n");flag=0;fclose(fpcode);
		}
				fscanf(fpcode,"%s",&compare);
		if(strcmp(compare,code)==0)
		{
			printf("密钥正确！欢迎注册管理员\n");
			flag=1;
		}
		else 
		{
			printf("密钥输入错误！\n");
				flag=0;
		}
		if(flag==1)
		{
			printf("请输入你的账号(数字)\n");scanf("%s",&StuUsername);printf("请输入你的账户密码(字母加数字)\n");scanf("%s",&StuPassword);
			fp=fopen("AdminAccount.txt","r+w");//文件格式： 用户名   用户密码
			if(fp==NULL){printf("Error！ File is no found!\n");fclose(fp);exit(0);}
			fseek(fp,0,SEEK_END);
			fprintf(fp,"%d %s",StuUsername,StuPassword);fprintf(fp,"\n");
			printf("您的管理员账户已创建完毕！\n");
				fclose(fp);
		}
	}
	else
		if(keyfile==2)
	{
			printf("请输入你的账号(数字)\n");scanf("%s",&StuUsername);printf("请输入你的账户密码(字母加数字)\n");scanf("%s",&StuPassword);
		fp=fopen("UserAccount.txt","r+w");//文件格式： 用户名   用户密码
		if(fp==NULL){printf("Error！UserAccount.txt File is no found!\n");exit(0);}
		fseek(fp,0,SEEK_END);
		fprintf(fp,"%d %s 0",StuUsername,StuPassword);fprintf(fp,"\n");
		printf("您的读者账户已创建完毕！\n----------------------------------------------\n");
			fclose(fp);
	}
		else
			printf("你输入的数字不对！\n----------------------------------------------\n");return ;

}

void DisplayAlltheUser()//显示所有读者	(success)
{	char Username[10];
	char Password[10];
	FILE *fp;
	fp=fopen("UserAccount.txt","r");
	if(fp==NULL){printf("UserAccount is no found!\n");fclose(fp);exit(0);}
	printf("账户为:   密码为：\n");
			fscanf(fp,"%s %s",&Username,&Password);fprintf(fp,"\n");
	while(!feof(fp))
	{	
		printf("%s   %s\n",Username,Password);
		fscanf(fp,"%s %s",&Username,&Password);
	}
	printf("所有账户已经全部输出完毕！\n----------------------------------------------\n");
}
void BookInformationDisplay()//输出全部图书信息		(succss)
{
	char bookname1[maxsize];//书名
	int bookstate1;//书的状态
	int timelimit1;//书的借书界限
	FILE *fp;
	fp=fopen("BookInformation.txt","r");
	if(fp==NULL){printf(" BookInformation.txt is no found!\n");fclose(fp);exit(0);}

	/*
	char bookname[maxsize];//书名
	int bookstate;//书的状态 0：被借阅，1：没被借阅;
	int timelimit;//若该图书被借阅，则启动时间限制,时间限制默认为30天;
	*/
	//文件格式： 
	printf("书名  书的状态(1可借/0不可借) 书的时间界限(天):\n");
	fscanf(fp,"%s %d %d",&bookname1,&bookstate1,&timelimit1);
	while(!feof(fp))
	{
		if(feof(fp))break;
	
		printf("%s   %d\t\t\t %d\n",bookname1,bookstate1,timelimit1);
		fscanf(fp,"%s %d %d",&bookname1,&bookstate1,&timelimit1);
	}
	printf("图书信息全部输出完毕！\n----------------------------------------------\n");

}
void display()//显示出所有图书信息：书名，书的状态，书的期限		单链表遍历函数
{	
	bookinformation *p;p=hd->next;//进入第一个节点
	printf("----------------------------------------------\n");
	while(p)//链表遍历
	{	
		printf("%s %d %d\n",p->bookname,p->bookstate,p->timelimit);
		p=p->next;
	}
	printf("\n----------------------------------------------\n");
}

bookinformation* search(bookinformation *hd1,int sum)//查找图书		(success)
{
	int i=1;
	bookinformation *p;
	p=hd1->next ;//进入第一个节点
	if(sum==0)return hd;//如果编号为0，表示该读者没有借阅      
	while(p&&i<sum)//没找到就一直往下找
	{	p=p->next;
		++i;
	}
	return p;

}
void BookInformationInit()//					图书信息初始化操作	
{
	bookinformation *p;	
	bookinformation *hd1;	hd1=(bookinformation *)malloc(sizeof(bookinformation));
	hd1=hd;
	printf("正在初始化导入程序！\n");
	char bookname1[maxsize];//书名
	int bookstate1;//书的状态
	int timelimit1;//书的时间界限
	FILE *fp;
	fp=fopen("BookInformation.txt","r+w");
	if(fp==NULL){printf("BookInformation.txt is no found!\n");fclose(fp);exit(0);}
	fscanf(fp,"%s %d %d",&bookname1,&bookstate1,&timelimit1);//fscanf(fp,"\n");
	int sum=0;//计算图书数量
	while(!feof(fp))
	{		
		sum++;
		p=(bookinformation *)malloc(sizeof(bookinformation));
		strcpy(p->bookname,bookname1);//字符串赋值
		p->bookstate=bookstate1;//状态赋值
		p->timelimit=timelimit1;//时间赋值
		
		hd1->next=p;//尾插法,插入到单链表
		hd1=p;//尾插法
			fscanf(fp,"%s %d %d",&bookname1,&bookstate1,&timelimit1);
	}

	hd1->next=NULL;//尾插法
	printf("\n目前图书共有%d本\n\n",sum);
	printf("程序初始化完毕!\n----------------------------------------------\n");
	display();
	fclose(fp);
}
void BookInformationInput()//图书信息导入	(success)
{	char Input[maxsize];//信息录入
	FILE *fp;
	fp=fopen("BookInformation.txt","r+w");
	if(fp==NULL){printf("BookInformation.txt is no found!\n");fclose(fp);exit(0);}
	printf("请不断输入书的书名(书名字长必须一致！)，直到输入null\n");
	while(1)
	{	scanf("%s",&Input);
		if(strcmp(Input,"null")==0)
		{fclose(fp);	break;}
		fseek(fp,0,SEEK_END);//写入到文件末尾
		fprintf(fp,"%s 1 00",Input);fprintf(fp,"\n");
		printf("成功录入此图书\n");
	}
	BookInformationInit();
}



void BookInformationDelete()//图书信息删除			(success!)
{	int sum=0,flag=0;//计数器,标志位
	char bookname1[maxsize];
	bookinformation *q;
	printf("请输入你想要删除的图书书名！\n");
	scanf("%s",&bookname1);
	bookinformation *p,*w,*L;
	p=(bookinformation *)malloc(sizeof(bookinformation));
	L=(bookinformation *)malloc(sizeof(bookinformation));
	p=hd->next;//进入第一个节点

//	printf("第一个是%s\n",p->bookname);
	while(p)//单链表遍历
	{	
		sum=sum+1;
			if(strcmp(p->bookname,bookname1)==0)//如果相等，就删除他!
		{
			w=search(hd,sum-1);
			q=w->next;printf("要删除的是%s书籍\n",q->bookname);
			w->next=q->next;//删除算法
			free(q);//把q删除
			flag=1;
			printf("haven delete!\n");sum--;
			display();
			break;
		}
			p=p->next;
			
	}
	L=hd->next;
	if(flag==0)printf("\n----------------------------------------------\n要删除的书籍未找到！\n----------------------------------------------\n");
	FILE *fp;
	fp=fopen("BookInformation.txt","w");
	if(fp==NULL){printf("BookInformation.txt未找到！\n");fclose(fp);exit(0);}
//	fseek(fp,0,SEEK_SET);
	while(L)
	{
		fprintf(fp,"%s %d %d",L->bookname,L->bookstate,L->timelimit);fprintf(fp,"\n");
		L=L->next;
	}
	fclose(fp);
	printf("图书数据库已更新!\n----------------------------------------------\n");
//	BookInformationInit();
	
}

void AdminKeyControl()//管理员控制面板
{	int x;//控制相应的功能！
	printf("管理员控制面板：\n请输入相应的数字进入相应的功能！\n\n");

	printf("功能1：显示出所有读者账户和密码\n");
	printf("功能2：显示所有图书信息\n");
	printf("功能3：图书信息录入\n");
	printf("功能4：删除图书信息\n");
	printf("功能5：退出账号\n");

	//printf("功能1：\n");
	scanf("%d",&x);printf("----------------------------------------------\n");
	switch(x)
	{
		case 1:DisplayAlltheUser();break;//显示出所有读者账户和密码	
		case 2:BookInformationDisplay();break;//显示所有图书信息
		case 3:BookInformationInput();break;//图书信息录入		
		case 4:BookInformationDelete();break;//删除图书信息
		case 5:AdminKey=0;break;//退出账号
	}
}
void AdminSearch(char username[],char password[])//根据账号和密码查询管理员，若存在，则登陆		//(success)
{	char username1[10];char password1[10];
	int outcome;
	FILE *fp;int flag=0;
	fp=fopen("AdminAccount.txt","r");//文件格式：用户名		用户密码
	if(fp==NULL){printf("AdminAccount.txt未找到！\n");fclose(fp);exit(0);}
	printf("----------------------------------------------\n");
	while(!feof(fp))
	{
		fscanf(fp,"%s %s",&username1,&password1);
		outcome=strcmp(password,password1);//字符串比较函数，当outcome=0时，代表两个字符串相等
		if(strcmp(username,username1)==0&&outcome==0)
		{
			printf("欢迎登陆！\n");
			flag=1;AdminKey=1;
			break;
		}
	}
	if(flag==0)
		printf("此账号不存在,请重新登陆！\n");
	while(AdminKey)
		AdminKeyControl();
}
void BookInformationSearch()//图书信息查找	(success)
{
	char bookname1[maxsize];
	int bookstate1;
	int timelimit1;
	int flag=0,sore=0;//标志位，书的编号
	char search[maxsize];
	FILE *fp;
	fp=fopen("BookInformation.txt","r");
	if(fp==NULL){printf("BookInformation.txt is no found!\n");fclose(fp);exit(0);}
	printf("请输入你想要查询的图书\n");scanf("%s",&search);printf("查询结果:\n");
	fscanf(fp,"%s %d %d",&bookname1,&bookstate1,&timelimit1);fprintf(fp,"\n");
	while(!feof(fp))
	{	sore++;
		if(strcmp(bookname1,search)==0)
		{	flag=1;
			printf("\n该书信息如下：\n书名：%s\t是否可借(1可借/0不可借):%d\n",bookname1,bookstate1);
			break;
			
		}
		fscanf(fp,"%s %d %d",&bookname1,&bookstate1,&timelimit1);
	}
	
		if(flag==0)printf("该图书不存在！\n");
	else
		printf("书的编号：%d\n",sore);
	printf("----------------------------------------------\n");
}
void ReaderDatabaseInput(char string[])//用户数据库写入 (BUG,无法写入)
{
	FILE *fp;
	char filename[10];

	strcpy(filename,string);
	strcat(filename,".txt");//用户名.txt
	fp=fopen(filename,"r+w");	//(bug!)


	if(fp==NULL){printf("ReaderDatabaseInput  %s未找到！\n",filename);fclose(fp);exit(0);}
	fseek(fp,0,SEEK_END);
	fprintf(fp,"%d\n",p->BookSore);//将书籍的编号写入用“读者账户”命名的.txt文件中
	

//	fprintf(fp,"\n");
	printf("\n\n写入完毕！！！\n\n");
	fclose(fp);

}
char* BookSearch(int sore)//编号导入,利用编号查找图书名称并返回
{		
	FILE *fp;
	static	char bookname1[10];
	int bookstate1,timelimit1,sore1=0;//书的状态，书的时间限制,书的编号
	fp=fopen("BookInformation.txt","r+w");

	if(fp==NULL){printf("BookSearch	：BookInformation.txt未找到！\n");fclose(fp);exit(0);}
	if(sore!=0)
	{
		fscanf(fp,"%s %d %d",&bookname1,&bookstate1,&timelimit1);fprintf(fp,"\n");sore1++;
			while(!feof(fp)&&sore1<sore)
		{	sore1++;
			fscanf(fp,"%s %d %d",&bookname1,&bookstate1,&timelimit1);
			fprintf(fp,"\n");
			
		}
		fclose(fp);
	return bookname1;//返回字符串
	}

	fclose(fp);
//	strcpy(bookname1,"");
//	return NULL;
	return bookname1;
}
void BookReturn()//还书算法
{
	FILE *fp,*fp1;
	char BookName[10],filename[10];
	int Booksore1,Booksore,flag=0;
	char bookname1[maxsize];//书名
	int bookstate1;//书的状态
	int timelimit1;//书的时间界限
	printf("请输入你想要归还的图书编号！\n");
	scanf("%d",&Booksore);
	strcpy(BookName,BookSearch(Booksore));//根据图书编号返回图书名称，并赋值给BookName

	strcpy(filename,p->UserName);
	strcat(filename,".txt");
	fp=fopen(filename,"r+w");//fp指向的是	用户名.txt
	fp1=fopen("BookInformation.txt","r+w");//fp1指向的是 BookInformation.txt

	if(fp1==NULL){printf("还书算法1：BookInformation.txt is no found!\n");fclose(fp1);exit(0);}
	if(fp==NULL){printf("还书算法2：%s is no found!\n",filename);fclose(fp);exit(0);}

	fscanf(fp,"%d",&Booksore1);
	while(!feof(fp))//查询算法
	{	
		if(Booksore1==Booksore)//如果想要归还的图书编号和你已借阅的书籍的编号一致时
		{
			printf("编号为%d 书名为  %s已经成功归还!\n",Booksore1,BookName);
			flag=1;
			break;//查询完毕，开始退出查询算法
		}
		fscanf(fp,"%d",&Booksore1);
	}
	if(flag==0)printf("你并没有借阅这本编号为%d的书籍！\n",Booksore);
	else
	{	
		for(int i=0;i<Booksore;i++)//在BookInformation.txt文件中进行搜索编号为Booksore的 位置
			fscanf(fp1,"%s %d %d",&bookname1,&bookstate1,&timelimit1);
				
			fseek(fp1,-4,SEEK_CUR);//成功归还后，开始对BookInformation.txt文件进行恢复和更改！
			fprintf(fp1," 1 00");//(BUG!!!!)
			printf("图书信息库已经更新完毕！（BookReturn）\n");

/*				fseek(fp,-4,SEEK_CUR);//x=30;				
	fprintf(fp," 0 30");								
*/

			fseek(fp,-1,SEEK_CUR);	//并把 用户.txt文件进行删除此 被归还的图书编号
			fprintf(fp,"0");
	}
						
					

	fclose(fp);
	fclose(fp1);
	printf("----------------------------------------------\n");
}
void BookBorrow()//图书借阅			(BUG!!!!!)
{	BookInformationSearch();//调用查找图书的函数
	char bookname1[maxsize];//书名
	int bookstate1;//书的状态
	int timelimit1;//书的时间界限
	int sore;
	FILE *fp;
	fp=fopen("BookInformation.txt","r+w");
	if(fp==NULL){printf("BookInformation.txt is no found!\n");fclose(fp);exit(0);}
	printf("请输入你要借阅书籍的编号！\n");scanf("%d",&sore);printf("----------------------------------------------\n");
		for(int x=0;x<sore;x++)	
			fscanf(fp,"%s %d %d",&bookname1,&bookstate1,&timelimit1);
		if(bookstate1==0)
		{
			printf("该图书库藏有限，均已全部借阅完毕，请换本书进行借阅！\n----------------------------------------------\n");
			return ;
		}
		else
			
			if(p->Maxsize>5)
			{	
				printf("你已达到最多借阅量!\n");
				return ;
			}
					//如果读者成功借阅书籍，则利用“ReaderUser结构体”
					//将书籍的编号写入用“读者账户”命名的.txt文件中
					//RdUserHd
	printf("你已经成功借阅编号为%d,书名为  %s的图书！该图书的状态变为0\n",sore,bookname1);
	Timefun();
//

		p->Maxsize++;//借阅量++，最高为5
		p->BookSore=sore;//图书编号导入
		ReaderDatabaseInput(p->UserName);
		
	fseek(fp,-4,SEEK_CUR);//x=30;				
	fprintf(fp," 0 30");								

printf("状态已更改！\n----------------------------------------------\n");	
fclose(fp);

}
void CreateReaderBookDatabase(char string[])//创建用户自己的数据库！
{
	FILE *fp;
	char filename[10];
	
	strcpy(filename,string);
	strcat(filename,".txt");
	fp=fopen(filename,"w");
	printf("创建用户数据库完成，请重新启动本程序进行加载！\n文件格式为：用户名.txt\n----------------------------------------------\n");
	fclose(fp);
	Actorfun("图书管理系统！");
//	if(fp==NULL){printf("CreateReaderBookDatabase:%s未找到！\n",filename);fclose(fp);exit(0);}
	
}


void HaveBorrowBookDisplay(char string[])//显示读者已借阅的图书！
{
	int Booksore1;//书籍编号
	FILE *fp;
	char BookName[10];
	char filename[10];
/*
	strcpy(filename,string);
	strcat(filename,".txt");//用户名.txt
	fp=fopen(filename,"r+w");
*/
	strcpy(filename,string);
	strcat(filename,".txt");
	fp=fopen(filename,"r+w");

	if(fp==NULL){printf("HaveBorrowBookDisplay  %s未找到！\n",filename);fclose(fp);exit(0);}
	printf("你已借阅的书籍有：\n");
	fscanf(fp,"%d",&Booksore1);//fscanf(fp,"\n");
	//printf("%d\n\n",Booksore1);
	while(!feof(fp))
	{	
		strcpy(BookName,BookSearch(Booksore1));//字符串赋值给BookName;
		if(strcmp(BookName,"NULL")==0)
		{fscanf(fp,"%d",&Booksore1);continue;		}

		if(Booksore1!=0)
			printf("编号为%d 书名为  %s\n",Booksore1,BookName);
		fscanf(fp,"%d",&Booksore1);//fscanf(fp,"\n");
	
	}
	
		
	fclose(fp);
	printf("----------------------------------------------\n");
	return ;
}
void UserKeyControl()//读者服务面板
{
	int x;//控制相应的功能！
	printf("读者服务面板：\n请输入相应的数字进入相应的功能！\n\n");

	//printf("功能1：显示出所有读者账户和密码\n");
	printf("功能1：借阅图书\n");
	printf("功能2：查询图书\n");	
	printf("功能3：显示所有图书信息\n");
	printf("功能4：显示所有已借阅书籍\n");
	printf("功能5：还书\n");
	printf("功能6：退出账号\n");
	//printf("功能1：\n");
	scanf("%d",&x);printf("----------------------------------------------\n");
	switch(x)
	{
		case 1:BookBorrow();break;//图书借阅
		case 2:BookInformationSearch();break;//图书信息查找	
		case 3:BookInformationDisplay();break;//显示所有图书信息
		case 4:HaveBorrowBookDisplay(p->UserName);break;//显示所有已借阅书籍
		case 5:BookReturn();break;//还书
		case 6:UserKey=0;break;//退出账号
	}
}
/*
void ScanfMaxSize()
{
	FILE *fp;
	char filename[10];
	strcpy(filename,p->UserName);
	strcat(filename,".txt");
	fp=fopen(filename,"r+w");
		fscanf(fp,"%d",&Booksore1);//fscanf(fp,"\n");//printf("%d\n\n",Booksore1);
	while(!feof(fp))
	{	
		strcpy(BookName,BookSearch(Booksore1));//字符串赋值给BookName;
		if(Booksore1!=0)
			MaxSize++;
	}
}
*/
void UserSearch(char username[],char password[])//根据账号和密码查询读者，若存在，则登陆	//(success)
{
	char username1[10];char password1[10];
	int outcome;
	FILE *fp,*fp1;int flag=0;
	fp=fopen("UserAccount.txt","r");//文件格式：用户名		用户密码
	if(fp==NULL){printf("AdminAccount.txt未找到！\n");fclose(fp);exit(0);}
	printf("----------------------------------------------\n");
	while(!feof(fp))
	{	fscanf(fp,"%s %s",&username1,&password1);
		outcome=strcmp(password,password1);//字符串比较函数，当outcome=0时，代表两个字符串相等
		if(strcmp(username,username1)==0&&outcome==0)
		{
			printf("欢迎登陆！\n");
			flag=1;UserKey=1;	strcpy(p->UserName,username1);
			char filename[10];
			strcpy(filename,p->UserName);
			strcat(filename,".txt");//用户名.txt
			//printf("请先创建该用户的数据库！文件格式用户名.txt\n");exit(0);
			fp1=fopen(filename,"r+w");
			if(fp1==NULL){CreateReaderBookDatabase(p->UserName);fclose(fp1);}
		//	ScanfMaxSize();
			fclose(fp1);
			break;
		}
	}
	if(flag==0)
		printf("此账号不存在,请重新登陆！\n");
		while(UserKey)
		UserKeyControl();
}
void Login()//登陆函数				(success)
{	int usernamecontrol;
	char username[10];
	char password[10];
	printf("请选择你的身份:\n输入1:管理员账号登陆\n输入2:读者账号登陆\n");
	scanf("%d",&usernamecontrol);//用户身份控制：控制用户是属于哪一类的账户;
	switch(usernamecontrol)
{
case 1:printf("请输入你的管理员账号(均为数字):\n");scanf("%s",&username);printf("请输入你的管理员密码(均为数字):\n");scanf("%s",&password);break;
case 2:printf("请输入你的读者账号(均为数字):\n");scanf("%s",&username);printf("请输入你的读者密码(均为数字):\n");scanf("%s",&password);break;
default:printf("错误！你选择的身份不存在！\n");break;
}
	if(usernamecontrol==1)
	AdminSearch(username,password);//查找是否存在该管理员账号
	else
	UserSearch(username,password);//查找是否存在该读者账号 
}


int  main()
{	hd=(bookinformation *)malloc(sizeof(bookinformation));
	hd->next=NULL;//头结点
	RdUserHd=(ReaderUser *)malloc(sizeof(ReaderUser));
	RdUserHd->next=NULL;//头结点
	p->Maxsize=0;
	BookInformationInit();
//	CreateReaderBookDatabase();
	int x;
	while(1)//菜单功能
	{	printf("欢迎进入图书管理系统！\n输入1,创建账户\n");
		printf("输入2,用户身份登陆\n输入3,退出系统\n----------------------------------------------\n");	scanf("%d",&x);
		switch(x)
		{
		case 1:CreateMyAccount();break;//输入1,创建账户
		case 2:Login();break;	//输入2,用户身份登陆
		case 3:printf("你已经成功退出图书管理系统！\n");Actorfun("图书管理系统");exit(0);break;//退出系统
		default:printf("不存在的功能！请重新输入！\n");break;
		}
	}

//	CreateMyAccount();
//	Login();
return 0;
}
