#include<iostream>
#include<stdio.h>
#include<string.h>
#include <malloc.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 100     //线性表存储空间的初始分配量 
#define LISTINCREMENT 10     // 线性表存储空间的分配增量 
#define TRUE 1  
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIABLE -1
#define OVERFLOW -2
using namespace std;

typedef int ElemType;
typedef int Status; 
typedef struct{
	ElemType *elem;     //存储空间基址 
	int length;     //当前长度 
	int listsize;     //当前分配的存储容量 
}SqList;
Status InitList(SqList &L){
	L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.elem) exit(OVERFLOW);     //存储分配失败 
	L.length=0;     //空表长度为0 
	L.listsize=LIST_INIT_SIZE;     //初始存储容量 
	return OK;
}//构造一个空的线性表 
Status DestroyList(SqList &L){
	if(!L.elem) return ERROR;     //线性表不存在，销毁失败 
	L.length=0;
	L.listsize=0;
	L.elem=NULL;      //线性表空间基址置空 
	return OK;
}//销毁线性表 
Status ClearList(SqList &L){
	if(!L.elem) return ERROR;     //线性表不存在，置空失败 
	L.length=0;
	return OK;
}//将线性表置为空表 
Status ListEmpty(SqList &L){
	if(!L.elem) return INFEASIABLE;     //线性表不存在，无法判定 
	else if(L.length==0) return TRUE;
	else return FALSE; 
}//判定线性表是否为空表 
Status ListLength(SqList &L){
	int k;
	if(!L.elem) return INFEASIABLE;     //线性表不存在，无法求长度 
	return L.length;
}//求线性表的长度 
Status GetElem(SqList &L,int i,ElemType &e) {
	if((i<1)||(i>L.length)||(!L.elem)||(L.length==0)) return ERROR;     //i值不合法或线性表不存在或线性表为空表时，操作无效 
	e=L.elem[i-1];     //e为线性表第i个数据元素的值 
	return OK;
}//用e返回线性表中第i个数据元素的值 
Status compare(ElemType a,ElemType b)
{
	if(a==b) return OK;
	else return 0;
}//定义compare函数，供LocateElem函数调用 
Status LocateElem(SqList &L,ElemType e,Status(*compare)(ElemType,ElemType)){
	if(!L.elem) return INFEASIABLE;     //线性表不存在，操作无效 
	int i=1;     //i的初值为第1个元素的位序 
	ElemType *p;
	p=L.elem;     //p的初值为第1个元素的存储位置 
	while((i<=L.length)&&!(*compare)(*p++,e)) ++i;
	if(i<=L.length) return i;
	else return 0;     //没找到，返回0 
}//在线性表中查找第1个值与e满足compare()的元素的位序 
Status PriorElem(SqList &L,ElemType &cur_e,ElemType &pre_e){
	if((!L.elem)||(L.length==0)) return ERROR;     //线性表不存在或线性表为空表，操作无效 
	int k=0;
	while(k<=L.length){
		if((L.elem[k]==cur_e)&&(k!=0)) break;     //k为元素cur_e的位序 
		k++;}
		if(k<=L.length) pre_e=L.elem[k-1];     //pre_e的位序为k-1 
		else return ERROR;     //cur_e不存在线性表或是表中第1个元素，操作无效 
	}//用pre_e返回线性表中元素cur_e的前驱 
Status NextElem(SqList &L,ElemType &cur_e,ElemType &next_e){
	if((!L.elem)||(L.length==0)) return ERROR;     //线性表不存在或线性表为空表，操作无效 
	int k=0;
	while(k<=L.length){
		if(L.elem[k]==cur_e) break;     //k为元素cur_e的位序 
		k++;}
		if(k+1<L.length) next_e=L.elem[k+1];     //next_e的位序为k+1 
		else return ERROR;     //cur_e不存在线性表或是表中最后1个元素，操作无效 
}//用next_e返回线性表中元素cur_e的后继 
Status ListInsert(SqList &L,int i,ElemType e){
	if((i<1)||(i>L.length+1)||(!L.elem)||(L.length==0)) return ERROR;     //i值不合法或线性表不存在或线性表为空表时，操作无效 
	if(L.length>=L.listsize) {     //当前存储空间已满，增加分配 
		ElemType *newbase;
		newbase=(ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase) exit(OVERFLOW);     //存储分配失败 
		L.elem=newbase;     //新基址 
		L.listsize+=LISTINCREMENT;     //增加存储容量 
}
	ElemType *q;ElemType *p;
	q=&(L.elem[i-1]);     //q为插入位置 
	for(p=&(L.elem[L.length-1]);p>=q;--p) *(p+1)=*p;     //插入位置及之后的元素右移 
	*q=e;     //插入e 
	++L.length;     //表长增1 
	return OK;
}//在线性表中第i个位置之前插入新的元素e 
Status ListDelete(SqList &L,int i,ElemType &e){
	if((i<1)||(i>L.length)||(!L.elem)||(L.length==0)) return ERROR;     //i值不合法或线性表不存在或线性表为空表时，操作无效
	ElemType *q;ElemType *p;
	p=&(L.elem[i-1]);     //p为被删除元素的位置 
	e=*p;     //被删除元素的值赋给e 
	q=L.elem+L.length-1;     //表尾元素的位置 
	for(++p;p<=q;++p) *(p-1)=*p;     //被删除元素之后的元素左移 
	--L.length;     //表长减1 
	return OK;	
}//在线性表中删除第i个元素，并用e返回其值 
Status CreateList(SqList &L,int n){
	int i;
	L.elem=(ElemType*)malloc(n*sizeof(ElemType));
	L.length=n;     //定义线性表的长度 
	L.listsize=LIST_INIT_SIZE;
	printf("Input elements:");
	for(i=0;i<n;i++)
	scanf("%d",&L.elem[i]);     //输入线性表中的元素 
}//输入元素，创建线性表 
void visit(ElemType a){
	printf("%d ",a);
}//定义visit函数，供ListTraverse函数调用 
Status ListTraverse(SqList &L,void(*visit)(ElemType)){
	if(!L.elem) return ERROR;     //线性表不存在，操作无效 
	printf("此线性表的长度为:%d\n",L.length);
	printf("此线性表的元素为:\n");
	int i;
	for(i=0;i<L.length;i++)
	(*visit)(L.elem[i]);     // 对表中每个元素调用函数visit 
	return OK;
}//遍历线性表，对表中每个元素调用函数visit，输出表中每个元素及表长 
Status ListSort(SqList &L){
	if((!L.elem)||(L.length==0)) return ERROR;     //线性表不存在或线性表为空表，操作无效 
	int i,j;
	ElemType a;
	for(i=0;i<L.length-1;i++)
	{		
	    for(j=0;j<L.length-i-1;j++){
		if(L.elem[j]>L.elem[j+1]) {a=L.elem[j];L.elem[j]=L.elem[j+1];L.elem[j+1]=a;}
	}   }  //冒泡排序 
	return OK;
}//将线性表中数据元素按从小到大排列 
int maximum(int a[],int N){
	int max=a[0];
	int i;
	for(i=0;i<N;i++) {if(a[i]>max) max=a[i];}
	return max;
}//定义maximum函数，供ListMaxMin函数调用 
int minimum(int a[],int N){
	int min=a[0];
    int i;
	for(i=0;i<N;i++) {if(a[i]<min) min=a[i];}
	return min;
}//定义minimum函数，供ListMaxMin函数调用 
Status ListMaxMin(SqList &L,int(*maximum)(int[],int),int(*minimum)(int[],int),ElemType &max,ElemType &min){
	if((!L.elem)||(L.length==0)) return ERROR;     //线性表不存在或线性表为空表，操作无效 
	max=maximum(L.elem,L.length);     //max返回线性表中数据元素的最大值 
	min=minimum(L.elem,L.length);     //min返回线性表中数据元素的最小值 
	return OK;
}//求线性表中数据元素的最大值和最小值 
Status ListSave(SqList &L,char *filename){
	FILE  *fp;int i; 
	if ((fp=fopen(filename,"wb"))==NULL)
	{
	printf("File open error\n ");
	return ERROR;
	}     //文件不存在，显示错误信息 
	for(i=0;i<L.length;i++)
		fprintf(fp,"%d\t",L.elem[i]);     //用fprintf函数将线性表中每个元素存入文件 
    fclose(fp);
	return OK;
}//将线性表存入文件 
Status ListLoad(SqList &L){
	FILE  *fp;int i=0;
	if ((fp=fopen("D:\\ryt.txt","rb"))==NULL)
	{
	printf("File open error\n ");
	return ERROR;
	}     //文件不存在，显示错误信息 
	InitList(L);     //建立空表 
	while(!feof(fp)){
		fscanf(fp,"%d",&L.elem[i]);     //用fscanf函数将文件中每个元素读入线性表 
		i++;
		L.length++;
	}
	ListTraverse(L,visit); 
    fclose(fp);
	return OK;
}//将文件读入线性表 
int main(void){
	SqList L,Lnew;  int op=1;
	int n;
	while(op){
	system("cls");	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. InitList       7. LocateElem\n");
	printf("    	  2. DestroyList    8. PriorElem\n");
	printf("    	  3. ClearList      9. NextElem \n");
	printf("    	  4. ListEmpty      10. ListInsert\n");
	printf("    	  5. ListLength     11. ListDelete\n");
	printf("    	  6. GetElem        12. ListTraverse\n");
	printf("    	  13. CreateList    14. ListSort\n");
	printf("    	  15. ListMaxMin    16.ListSave \n");
	printf("    	  17. ListLoad      0. exit \n");
	printf("-------------------------------------------------\n");
	printf("    请选择你的操作[0~17]:");     //菜单 
	scanf("%d",&op);
    switch(op){     //用switch函数实现菜单功能 
	   case 1:     //创建空表，调用InitList函数 
		 if(InitList(L)==OK) printf("线性表创建成功！\n");
		     else printf("线性表创建失败！\n");
		 getchar();getchar();
		 break;
	   case 2:     //销毁线性表，调用 DestroyList函数 
		if(DestroyList(L)==OK) printf("线性表销毁成功！\n");
		     else printf("线性表销毁失败！\n");    
		 getchar();getchar();
		 break;
	   case 3:     //清空线性表，调用ClearList函数 
		if(ClearList(L)==OK) printf("线性表清空成功！\n");
		     else printf("线性表清空失败！\n");   
		 getchar();getchar();
		 break;
	   case 4:     //判定线性表是否为空表，调用ListEmpty函数 
		 if(ListEmpty(L)==TRUE) printf("线性表是空表！\n");
		     else if(ListEmpty(L)==INFEASIABLE) printf("线性表不存在！\n");
		     else printf("线性表不是空表！\n");
		 getchar();getchar();
		 break;
	   case 5:     //求表长，调用ListLength函数 
	    int a;
	   	 a=ListLength(L);
	   	 if(a==INFEASIABLE) printf("线性表不存在！\n");
			else  printf("线性表的长度是:%d",a);    
		 getchar();getchar();
		 break;
	   case 6:     //返回线性表中某一元素，调用GetElem函数 
		 printf("要返回线性表中第几个元素？\n");
		 int k;ElemType e;
		 scanf("%d",&k);
		 if(GetElem(L,k,e)==OK) printf("此元素是%d\n",e);
		     else printf("操作无效！\n");     
		 getchar();getchar();
		 break;
	   case 7:     //定位元素，调用LocateElem函数 
	   int m,i;
	   	printf("输入要定位的元素：\n");
		 scanf("%d",&m); 
		 k=LocateElem(L,m,compare);
		 if(k>0) printf("此元素在线性表中的第一个位序是:%d",k);
		     else if(LocateElem(L,m,compare)==INFEASIABLE) printf("线性表不存在！\n");
		     else printf("0");  
		 getchar();getchar();
		 break;
	   case 8:     //求前驱，调用PriorElem函数 
	   	ElemType cur_e,pre_e;
		printf("输入线性表中的某一元素:\n");
		scanf("%d",&cur_e); 
	   	if(PriorElem(L,cur_e,pre_e)) printf("此元素的前驱是%d",pre_e);
	   	else printf("操作无效！\n");
		 getchar();getchar();
		 break;
	   case 9:     //求后继，调用NextElem函数 
	   	ElemType p,q;
		 printf("输入线性表中的某一元素:\n");
		scanf("%d",&p);  
		if(NextElem(L,p,q)) printf("此元素的后继是%d",q);
	   	else printf("操作无效！\n");
		 getchar();getchar();
		 break;
	   case 10:     //插入元素，调用ListInsert函数 
		 printf("要在线性表的第几个位置之前插入什么数据元素？\n");
		 int r,t;
		 scanf("%d\t%d",&r,&t);    
		 if(ListInsert(L,r,t)==OK) {
		 	printf("插入成功！");printf("插入元素后的线性表为：\n"); ListTraverse(L,visit);
		 }
		 else printf("操作无效！\n");
		 getchar();getchar();
		 break;
	   case 11:     //删除元素，调用ListDelete函数 
		 printf("删除线性表的第几个数据元素？\n");
		 int j;ElemType v;
		 scanf("%d",&j);    
		 if(ListDelete(L,j,v)==OK) {
		 	printf("删除成功！删除的数据元素为：%d",v);printf("删除元素后的线性表为：\n"); ListTraverse(L,visit);
		 }
		 else printf("操作无效！\n");
		 getchar();getchar();
		 break;
	   case 12:     //遍历线性表，调用ListTraverse函数    
		if(!ListTraverse(L,visit)) printf("线性表不存在！\n");
		getchar();getchar();
		 break;
	   case 13:     //创建线性表，调用CreateList函数 
	   	printf("Input the number of elements:");
	    scanf("%d",&n);
	   	CreateList(L,n);
	   	printf("含有%d个元素的线性表创建成功！\n",n);
	   	getchar();getchar();
		 break;
	   case 14:     //排序，调用ListSort函数 
	     if(ListSort(L)==OK) {
	     	printf("排序成功！\n");ListTraverse(L,visit);
		 }
		 else printf("操作无效！\n");
		 getchar();getchar();
		 break; 
		case 15:     //求最大值最小值，调用ListMaxMin函数 
		 int max,min;
		 if(ListMaxMin(L,maximum,minimum,max,min)==OK) printf("线性表的最大值为%d\n线性表的最小值为%d",max,min);
		 else printf("操作无效！\n");
		 getchar();getchar();
		 break; 
		case 16:     //将线性表存入文件，调用ListSave函数 
		 char filename[100];
	     printf("input file name: ");
	     scanf("%s",filename);
	     if(ListSave(L,filename)==OK) printf("线性表存入文件成功！\n"); 
		 else printf("线性表存入文件失败！\n");
		 getchar();getchar();
		 break;
		 case 17:     //从文件读取线性表，调用ListLoad函数 
	     if(ListLoad(L)==OK) printf("从文件读取线性表成功！\n");
		 else printf("从文件读取线性表失败！\n");
		 getchar();getchar();
		 break;
	   case 0:
	    	break;
	}//end of switch
  }//end of while
printf("欢迎下次再使用本系统！\n");
return 0;
}

