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
typedef int status; 
typedef int ElemType;     //数据元素类型定义

typedef struct LNode{ 
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;     //顺序表（顺序结构）的定义
void InitList(LinkList &L){
	L=(LinkList)malloc(sizeof(LNode));
	L->next=NULL;     //空表头指针的指针域赋空 
}//构造一个空的线性表 
status DestroyList(LinkList &L){
	if(!L) return ERROR;     //线性表不存在，销毁失败 
	LinkList p;
	while(L!=NULL)
	{
		p=L->next;
		free(L);
		L=p;
	}     //销毁线性表的每个结点 
	return OK;
}//销毁线性表 
status ClearList(LinkList &L){
	if(!L) return ERROR;     //线性表不存在，置空失败 
	LinkList p;
	while(L->next!=NULL)
	{
		p=L->next;
		free(L);
		L=p;
	}     //销毁线性表除头结点以外的每个结点 
	return OK;
}//将线性表置为空表 
status ListEmpty(LinkList &L){
	if(!L) return INFEASIABLE;     //线性表不存在，无法判定 
	if(L->next==NULL) return TRUE;
	else return FALSE;
}//判定线性表是否为空表 
status ListLength(LinkList L){
	if(!L) return INFEASIABLE;     //线性表不存在，无法求长度  
	LinkList p;
	p=L;int i=0;
	while(p->next!=NULL)
	{
		p=p->next;
		i++;
	}     //通过遍历线性表，求长度 
	return i;	
}//求线性表的长度 
status GetElem(LinkList L,int i,ElemType &e,status (*ListLength)(LinkList)){
	int length;
	length=(*ListLength)(L);     //调用 ListLength函数，得线性表长度 
	if((i<1)||(i>length)||(length==-1)||(length==0)) return ERROR;     //i值不合法或线性表不存在或线性表为空表时，操作无效 
	LinkList p;
	p=L;int k=0;
	while(k<i){
		p=p->next;
		k++; 
	}      //通过遍历，找到线性表第i个元素，用指针p指向 
	e=p->data;     //p指向的数据为所求 
	return OK;
}//用e返回线性表中第i个数据元素的值 
status compare(ElemType a,ElemType b)
{
	if(a==b) return OK;
	else return 0;
}//定义compare函数，供LocateElem函数调用 
status LocateElem(LinkList L,ElemType e,status(*compare)(ElemType,ElemType)){
	if(!L) return INFEASIABLE;     //线性表不存在，操作无效 	
	LinkList p;p=L;int i=0;
	while(p->next!=NULL)
	{
		p=p->next;
		i++;
		if((*compare)(e,p->data)) break;      
	}     //通过遍历，找到元素e，用指针p指向，同时递增i 
	if((*compare)(e,p->data)) return i;     //i为元素e的位序 
	else return 0;
}
status PriorElem(LinkList L,ElemType cur_e,ElemType &pre_e){
	if((!L)||(L->next==NULL)) return ERROR;     //线性表不存在或线性表为空表，操作无效 
	LinkList p,q;p=L;q=L;
	while(p->next!=NULL)
	{
		p=p->next;
		if(p->data==cur_e) break;
    }     //通过遍历，找到元素cur_e,用指针p指向 
    if((p!=L->next)&&(p->data==cur_e)) {
    	while(q->next!=p) q=q->next;
    	pre_e=q->data;
	}     //再次遍历，找到p的前驱指针，前驱指针所指元素为pre_e 
	else return ERROR;     //cur_e不存在线性表或是表中第1个元素，操作无效 
}
status NextElem(LinkList L,ElemType cur_e,ElemType &next_e){
	if((!L)||(L->next==NULL)) return ERROR;     //线性表不存在或线性表为空表，操作无效 
	LinkList p;p=L;
	while(p->next!=NULL)
	{
		p=p->next;
		if(p->data==cur_e) break;
    }     //通过遍历，找到元素cur_e,用指针p指向 
    if((p->next!=NULL)&&(p->data==cur_e)) next_e=p->next->data;     //p的后继指针所指元素为next_e 
	else return ERROR;     //cur_e不存在线性表或是表中最后一个元素，操作无效 
}
status ListInsert(LinkList &L,int i,ElemType e,status (*ListLength)(LinkList)){
	int length;
	length=(*ListLength)(L);     //调用ListLength函数，length为L的长度 
	if((i<1)||(i>length)||(length==-1)) return ERROR;     //i值不合法或线性表不存在时，操作无效 
	LinkList p,q;p=L;int k=0;
	while(k<i-1){
		p=p->next;
		k++;
	}     //通过遍历，找到待插入位置的前一个元素，用指针p指向 
	q=(LinkList)malloc(sizeof(LNode));     //创建新结点，用指针q指向 
	q->data=e;     //插入结点的元素值为e 
	q->next=p->next;     //q指向p的后继结点 
	p->next=q;     //p指向q 
	return OK;
}
status ListDelete(LinkList &L,int i,ElemType &e,status (*ListLength)(LinkList)){
	int length;
	length=(*ListLength)(L);     //调用ListLength函数，length为L的长度 
	if((i<1)||(i>length)||(!L)||(length==0)) return ERROR;     //i值不合法或线性表不存在或线性表为空表时，操作无效
	LinkList p,q;p=L;int k=0;
	while(k<i-1){
		p=p->next;
		k++;
	}     //通过遍历，找到待删除元素的前驱元素，用指针p指向 
	q=p->next;     //q为待删除元素的指针 
	p->next=q->next;     //p指向q的后继结点 
	e=q->data;     //删除元素的值为e 
	free(q);     //释放删除结点的空间 
	return OK;
}
void visit(ElemType a){
	printf("%d ",a);
}//定义visit函数，供ListTraverse函数调用 
status ListTraverse(LinkList &L,void(*visit)(ElemType)){
	if(!L) return ERROR;     //线性表不存在，操作无效 
	LinkList p;
	p=L;int i=0;
	printf("此线性表的元素为:\n");
	while(p->next!=NULL)
	{
		p=p->next;
		(*visit)(p->data); 
	}     //对线性表中的每一个元素调用visit函数 
	return OK;
}//遍历线性表，对表中每个元素调用函数visit，输出表中每个元素及表长 
status CreateList(LinkList &L,int n){
	L=(LinkList)malloc(sizeof(LNode));     //创建表头结点 
	L->next=NULL;
	LinkList p,tail;int i;
	tail=L;
	printf("Input elements:\n");
	for(i=n;i>0;--i){
		p=(LinkList)malloc(sizeof(LNode));
		scanf("%d",&p->data);
		tail->next=p;tail=p;
	}     //创建每一个结点，对每个结点输入数据
	tail->next=NULL;     //尾结点的指针域置空 
}//创建含有n个元素的线性表，先进先出 
status ListSort(LinkList &L){
	if((!L)||(L->next==NULL)) return ERROR;      //线性表不存在或线性表为空表，操作无效 
	LinkList p,q;ElemType a; 
	for(p=L->next;p!=NULL;p=p->next)
	{		
	    for(q=p->next;q!=NULL;q=q->next){
		if(p->data>q->data) {a=p->data;p->data=q->data;q->data=a;}
	}  
    }     //选择排序 
	return OK;
}//将线性表中数据元素按从小到大排列 
status ListMaxMin(LinkList &L,ElemType &max,ElemType &min){
	if((!L)||(L->next==NULL)) return ERROR;      //线性表不存在或线性表为空表，操作无效 
	LinkList p;p=L->next;
	max=p->data;min=p->data;
	while(p!=NULL){
		if(p->data>max) max=p->data;
		if(p->data<min) min=p->data;
		p=p->next;
	}     //max为线性表中元素的最大值，min为最小值 
		return OK;
}//求线性表中数据元素的最大值和最小值 
status ListSave(LinkList &L,char *filename){
	FILE  *fp;LinkList p;p=L->next;
	if ((fp=fopen(filename,"wb"))==NULL)
	{
	printf("File open error\n ");
	return ERROR;
	}     //文件不存在，显示错误信息 
	while(p!=NULL){
		fprintf(fp,"%d  ",p->data);     //用fprintf函数将线性表中每个元素存入文件 
		p=p->next;
	}
    fclose(fp);
	return OK;
}//将线性表存入文件  
status ListLoad(LinkList &L){
	FILE  *fp;
	if ((fp=fopen("D:\\ryt.txt","rb"))==NULL)
	{
	printf("File open error\n ");
	return ERROR;
	}     //文件不存在，显示错误信息 
	InitList(L);     //建立空表 
	LinkList p,q;
	p=L;
	while(!feof(fp)){
		q=(LinkList)malloc(sizeof(LNode));
		q->next=NULL;
		p->next=q;
		fscanf(fp,"%d",&q->data);     //用fscanf函数将文件中每个元素读入线性表 
		p=q;
	}
    fclose(fp);
	return OK;
}//将文件读入线性表
int main(void){
LinkList L;  int op=1,n;
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
	printf("    	  13.CreateList     14. ListSort\n");
	printf("    	  15. ListMaxMin    16.ListSave\n");	
	printf("    	  17. ListLoad      0. Exit\n");
	printf("-------------------------------------------------\n");
	printf("    请选择你的操作[0~17]:");     //菜单 
	scanf("%d",&op);     
    switch(op){     //用switch函数实现菜单功能 
	   case 1:     //创建空表，调用InitList函数 
		 InitList(L); printf("线性表创建成功！\n");
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
		 if(GetElem(L,k,e,ListLength)==OK) printf("此元素是%d\n",e);
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
		 if(ListInsert(L,r,t,ListLength)==OK) {
		 	printf("插入成功！");printf("插入元素后的线性表为：\n"); ListTraverse(L,visit);
		 }
		 else printf("操作无效！\n");
		 getchar();getchar();
		 break;
	   case 11:     //删除元素，调用ListDelete函数 
		 printf("删除线性表的第几个数据元素？\n");
		 int j;ElemType v;
		 scanf("%d",&j);    
		 if(ListDelete(L,j,v,ListLength)==OK) {
		 	printf("删除成功！删除的数据元素为：%d",v);printf("删除元素后的线性表为：\n"); ListTraverse(L,visit);
		 }
		 else printf("操作无效！\n");  
		 getchar();getchar();
		 break;
	   case 12:    //遍历线性表，调用ListTraverse函数    
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
		 if(ListMaxMin(L,max,min)==OK) printf("线性表的最大值为%d\n线性表的最小值为%d",max,min);
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
}//end of main()

