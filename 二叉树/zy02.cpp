/** 哈夫曼树编码 **/
#include<stdio.h>
#include<stdlib.h> 
#include<time.h>
#define LENGTH 6

typedef int ElemType;  

typedef struct HuffmanTreeNode{  
    ElemType data;  //哈夫曼树中节点的权值
    struct HuffmanTreeNode* left;  
    struct HuffmanTreeNode* right;  
}HuffmanTreeNode,*PtrHuffman;  


/**
 * 创建哈夫曼树
 */
void fun(char s[]) 
{ 
time_t rawtime; 
struct tm * timeinfo; 
time ( &rawtime ); 
timeinfo = localtime ( &rawtime ); 
printf("%s\n",s); 
printf("%s", asctime (timeinfo) ); 
} 
PtrHuffman createHuffmanTree(ElemType arr[]){
    PtrHuffman ptrArr[LENGTH];
    PtrHuffman ptr,pRoot=NULL;  

    for (int i = 0; i < LENGTH; i++){  //初始化结构体指针数组,数组中每一个元素为一个结构体指针类型
        ptr = (PtrHuffman)malloc(sizeof(HuffmanTreeNode));  
        ptr->data = arr[i];  
        ptr->left = ptr->right = NULL; 
        ptrArr[i] = ptr;
    }
    
    for(i = 1; i < LENGTH; i++){  //进行 n-1 次循环建立哈夫曼树  
        //k1表示森林中具有最小权值的树根结点的下标,k2为次最小的下标
        int k1 = -1, k2;
        for(int j = 0; j < LENGTH; j++){  
            if (ptrArr[j] != NULL && k1 == -1){  
                k1 = j;  
                continue;  
            }  
            if (ptrArr[j] != NULL){  
                k2 = j;  
                break;  
            }  
        }  
        //将指针数组中的指针指向的最小值赋值给索引号为k1的,次小值赋值给索引号为k2的
        for (j = k2; j < LENGTH; j++){
            if(ptrArr[j] != NULL){
                if(ptrArr[j]->data < ptrArr[k1]->data){
                    k2 = k1;
                    k1 = j;
                }else if(ptrArr[j]->data < ptrArr[k2]->data){
                    k2 = j;
                }
            }
        }
        //由最小权值树和次最小权值树建立一棵新树,pRoot指向树根结点
        pRoot = (PtrHuffman)malloc(sizeof(HuffmanTreeNode));
        pRoot->data = ptrArr[k1]->data + ptrArr[k2]->data;
        pRoot->left = ptrArr[k1];
        pRoot->right = ptrArr[k2];

        ptrArr[k1] = pRoot; //将指向新树的指针赋给ptrArr指针数组中k1位置
        ptrArr[k2] = NULL; //k2位置为空
    }

    return pRoot;
}

/**
 * 哈夫曼树编码(叶子节点按中序方式依次打印其编码)
 */
void HuffmanCoding(PtrHuffman &ptrTree,int len){
    //静态局部变量相当于全局变量(只是只有在这个函数中能访问,但是生命周期是和全局变量差不多的)函数退出之后变量还在,而且只在第一次进入的时候做初始化,以后会跳过初始化语句,保留原来的值
    static int arr[20];  
    if(ptrTree != NULL){
        if(ptrTree->left==NULL && ptrTree->right==NULL){
           printf("结点权值为%d的编码: ", ptrTree->data); 
           for(int i = 0; i < len; i++){
               printf("%d", arr[i]);      
           }   
           printf("\n"); 
        }else{
            arr[len] = 0;
            HuffmanCoding(ptrTree->left,len+1);
            arr[len] = 1;
            HuffmanCoding(ptrTree->right,len+1);
        }
    }
}


/**
 * 打印哈夫曼树中各个节点的孩子节点
 * 若为叶子节点,则只显示提示信息
 * @param node 需要显示孩子节点的父节点
 */
void printHuffmanTreeChildNode(PtrHuffman node){
    if(node->left == NULL && node->right == NULL){
        printf("x=%d是哈夫曼树中的叶子节点",node->data);
        printf("\n\n");
        return;
    }
    if(node->left != NULL){
        printf("x=%d在哈夫曼树中的左孩子节点是lchild=%d",node->data,node->left->data);
        printf("\n");
    }
    if(node->right != NULL){
        printf("x=%d在哈夫曼树中的右孩子节点是rchild=%d",node->data,node->right->data);
        printf("\n");
    }
    printf("\n");
}


/**
 * 中序打印哈夫曼树的节点
 */
void midOrderprintHuffmanTreeNode(PtrHuffman &pRoot){
    if(pRoot==NULL){
        return;
    }else{
        midOrderprintHuffmanTreeNode(pRoot->left);
        printf("%d ",pRoot->data);
        midOrderprintHuffmanTreeNode(pRoot->right);
    }
}



/**
 * 测试程序入口
 */
int main(){
    ElemType arr[] = {1,3,11,12,6,13};
    PtrHuffman pRoot = createHuffmanTree(arr);  //返回指向哈夫曼树根节点的指针

    printf("==========中序打印哈夫曼树节点数据==========\n");
    midOrderprintHuffmanTreeNode(pRoot);
    printf("\n\n");

    printf("==========各节点的哈夫曼树编码==========\n");
    HuffmanCoding(pRoot,0);

    fprintf(stdout,"\n");
    fun("网安B203朱晋宏，链式存储哈夫曼二叉树\n");
    return 0;
}