#include<iostream>
#include<stdio.h>
#include<string.h>
#include <malloc.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 100     //���Ա�洢�ռ�ĳ�ʼ������ 
#define LISTINCREMENT 10     // ���Ա�洢�ռ�ķ������� 
#define TRUE 1  
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIABLE -1
#define OVERFLOW -2
using namespace std;
typedef int status; 
typedef int ElemType;     //����Ԫ�����Ͷ���

typedef struct LNode{ 
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;     //˳���˳��ṹ���Ķ���
void InitList(LinkList &L){
	L=(LinkList)malloc(sizeof(LNode));
	L->next=NULL;     //�ձ�ͷָ���ָ���򸳿� 
}//����һ���յ����Ա� 
status DestroyList(LinkList &L){
	if(!L) return ERROR;     //���Ա����ڣ�����ʧ�� 
	LinkList p;
	while(L!=NULL)
	{
		p=L->next;
		free(L);
		L=p;
	}     //�������Ա��ÿ����� 
	return OK;
}//�������Ա� 
status ClearList(LinkList &L){
	if(!L) return ERROR;     //���Ա����ڣ��ÿ�ʧ�� 
	LinkList p;
	while(L->next!=NULL)
	{
		p=L->next;
		free(L);
		L=p;
	}     //�������Ա��ͷ��������ÿ����� 
	return OK;
}//�����Ա���Ϊ�ձ� 
status ListEmpty(LinkList &L){
	if(!L) return INFEASIABLE;     //���Ա����ڣ��޷��ж� 
	if(L->next==NULL) return TRUE;
	else return FALSE;
}//�ж����Ա��Ƿ�Ϊ�ձ� 
status ListLength(LinkList L){
	if(!L) return INFEASIABLE;     //���Ա����ڣ��޷��󳤶�  
	LinkList p;
	p=L;int i=0;
	while(p->next!=NULL)
	{
		p=p->next;
		i++;
	}     //ͨ���������Ա��󳤶� 
	return i;	
}//�����Ա�ĳ��� 
status GetElem(LinkList L,int i,ElemType &e,status (*ListLength)(LinkList)){
	int length;
	length=(*ListLength)(L);     //���� ListLength�����������Ա��� 
	if((i<1)||(i>length)||(length==-1)||(length==0)) return ERROR;     //iֵ���Ϸ������Ա����ڻ����Ա�Ϊ�ձ�ʱ��������Ч 
	LinkList p;
	p=L;int k=0;
	while(k<i){
		p=p->next;
		k++; 
	}      //ͨ���������ҵ����Ա��i��Ԫ�أ���ָ��pָ�� 
	e=p->data;     //pָ�������Ϊ���� 
	return OK;
}//��e�������Ա��е�i������Ԫ�ص�ֵ 
status compare(ElemType a,ElemType b)
{
	if(a==b) return OK;
	else return 0;
}//����compare��������LocateElem�������� 
status LocateElem(LinkList L,ElemType e,status(*compare)(ElemType,ElemType)){
	if(!L) return INFEASIABLE;     //���Ա����ڣ�������Ч 	
	LinkList p;p=L;int i=0;
	while(p->next!=NULL)
	{
		p=p->next;
		i++;
		if((*compare)(e,p->data)) break;      
	}     //ͨ���������ҵ�Ԫ��e����ָ��pָ��ͬʱ����i 
	if((*compare)(e,p->data)) return i;     //iΪԪ��e��λ�� 
	else return 0;
}
status PriorElem(LinkList L,ElemType cur_e,ElemType &pre_e){
	if((!L)||(L->next==NULL)) return ERROR;     //���Ա����ڻ����Ա�Ϊ�ձ�������Ч 
	LinkList p,q;p=L;q=L;
	while(p->next!=NULL)
	{
		p=p->next;
		if(p->data==cur_e) break;
    }     //ͨ���������ҵ�Ԫ��cur_e,��ָ��pָ�� 
    if((p!=L->next)&&(p->data==cur_e)) {
    	while(q->next!=p) q=q->next;
    	pre_e=q->data;
	}     //�ٴα������ҵ�p��ǰ��ָ�룬ǰ��ָ����ָԪ��Ϊpre_e 
	else return ERROR;     //cur_e���������Ա���Ǳ��е�1��Ԫ�أ�������Ч 
}
status NextElem(LinkList L,ElemType cur_e,ElemType &next_e){
	if((!L)||(L->next==NULL)) return ERROR;     //���Ա����ڻ����Ա�Ϊ�ձ�������Ч 
	LinkList p;p=L;
	while(p->next!=NULL)
	{
		p=p->next;
		if(p->data==cur_e) break;
    }     //ͨ���������ҵ�Ԫ��cur_e,��ָ��pָ�� 
    if((p->next!=NULL)&&(p->data==cur_e)) next_e=p->next->data;     //p�ĺ��ָ����ָԪ��Ϊnext_e 
	else return ERROR;     //cur_e���������Ա���Ǳ������һ��Ԫ�أ�������Ч 
}
status ListInsert(LinkList &L,int i,ElemType e,status (*ListLength)(LinkList)){
	int length;
	length=(*ListLength)(L);     //����ListLength������lengthΪL�ĳ��� 
	if((i<1)||(i>length)||(length==-1)) return ERROR;     //iֵ���Ϸ������Ա�����ʱ��������Ч 
	LinkList p,q;p=L;int k=0;
	while(k<i-1){
		p=p->next;
		k++;
	}     //ͨ���������ҵ�������λ�õ�ǰһ��Ԫ�أ���ָ��pָ�� 
	q=(LinkList)malloc(sizeof(LNode));     //�����½�㣬��ָ��qָ�� 
	q->data=e;     //�������Ԫ��ֵΪe 
	q->next=p->next;     //qָ��p�ĺ�̽�� 
	p->next=q;     //pָ��q 
	return OK;
}
status ListDelete(LinkList &L,int i,ElemType &e,status (*ListLength)(LinkList)){
	int length;
	length=(*ListLength)(L);     //����ListLength������lengthΪL�ĳ��� 
	if((i<1)||(i>length)||(!L)||(length==0)) return ERROR;     //iֵ���Ϸ������Ա����ڻ����Ա�Ϊ�ձ�ʱ��������Ч
	LinkList p,q;p=L;int k=0;
	while(k<i-1){
		p=p->next;
		k++;
	}     //ͨ���������ҵ���ɾ��Ԫ�ص�ǰ��Ԫ�أ���ָ��pָ�� 
	q=p->next;     //qΪ��ɾ��Ԫ�ص�ָ�� 
	p->next=q->next;     //pָ��q�ĺ�̽�� 
	e=q->data;     //ɾ��Ԫ�ص�ֵΪe 
	free(q);     //�ͷ�ɾ�����Ŀռ� 
	return OK;
}
void visit(ElemType a){
	printf("%d ",a);
}//����visit��������ListTraverse�������� 
status ListTraverse(LinkList &L,void(*visit)(ElemType)){
	if(!L) return ERROR;     //���Ա����ڣ�������Ч 
	LinkList p;
	p=L;int i=0;
	printf("�����Ա��Ԫ��Ϊ:\n");
	while(p->next!=NULL)
	{
		p=p->next;
		(*visit)(p->data); 
	}     //�����Ա��е�ÿһ��Ԫ�ص���visit���� 
	return OK;
}//�������Ա��Ա���ÿ��Ԫ�ص��ú���visit���������ÿ��Ԫ�ؼ��� 
status CreateList(LinkList &L,int n){
	L=(LinkList)malloc(sizeof(LNode));     //������ͷ��� 
	L->next=NULL;
	LinkList p,tail;int i;
	tail=L;
	printf("Input elements:\n");
	for(i=n;i>0;--i){
		p=(LinkList)malloc(sizeof(LNode));
		scanf("%d",&p->data);
		tail->next=p;tail=p;
	}     //����ÿһ����㣬��ÿ�������������
	tail->next=NULL;     //β����ָ�����ÿ� 
}//��������n��Ԫ�ص����Ա��Ƚ��ȳ� 
status ListSort(LinkList &L){
	if((!L)||(L->next==NULL)) return ERROR;      //���Ա����ڻ����Ա�Ϊ�ձ�������Ч 
	LinkList p,q;ElemType a; 
	for(p=L->next;p!=NULL;p=p->next)
	{		
	    for(q=p->next;q!=NULL;q=q->next){
		if(p->data>q->data) {a=p->data;p->data=q->data;q->data=a;}
	}  
    }     //ѡ������ 
	return OK;
}//�����Ա�������Ԫ�ذ���С�������� 
status ListMaxMin(LinkList &L,ElemType &max,ElemType &min){
	if((!L)||(L->next==NULL)) return ERROR;      //���Ա����ڻ����Ա�Ϊ�ձ�������Ч 
	LinkList p;p=L->next;
	max=p->data;min=p->data;
	while(p!=NULL){
		if(p->data>max) max=p->data;
		if(p->data<min) min=p->data;
		p=p->next;
	}     //maxΪ���Ա���Ԫ�ص����ֵ��minΪ��Сֵ 
		return OK;
}//�����Ա�������Ԫ�ص����ֵ����Сֵ 
status ListSave(LinkList &L,char *filename){
	FILE  *fp;LinkList p;p=L->next;
	if ((fp=fopen(filename,"wb"))==NULL)
	{
	printf("File open error\n ");
	return ERROR;
	}     //�ļ������ڣ���ʾ������Ϣ 
	while(p!=NULL){
		fprintf(fp,"%d  ",p->data);     //��fprintf���������Ա���ÿ��Ԫ�ش����ļ� 
		p=p->next;
	}
    fclose(fp);
	return OK;
}//�����Ա�����ļ�  
status ListLoad(LinkList &L){
	FILE  *fp;
	if ((fp=fopen("D:\\ryt.txt","rb"))==NULL)
	{
	printf("File open error\n ");
	return ERROR;
	}     //�ļ������ڣ���ʾ������Ϣ 
	InitList(L);     //�����ձ� 
	LinkList p,q;
	p=L;
	while(!feof(fp)){
		q=(LinkList)malloc(sizeof(LNode));
		q->next=NULL;
		p->next=q;
		fscanf(fp,"%d",&q->data);     //��fscanf�������ļ���ÿ��Ԫ�ض������Ա� 
		p=q;
	}
    fclose(fp);
	return OK;
}//���ļ��������Ա�
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
	printf("    ��ѡ����Ĳ���[0~17]:");     //�˵� 
	scanf("%d",&op);     
    switch(op){     //��switch����ʵ�ֲ˵����� 
	   case 1:     //�����ձ�����InitList���� 
		 InitList(L); printf("���Ա����ɹ���\n");
		 getchar();getchar();
		 break;
	   case 2:     //�������Ա����� DestroyList���� 
		 if(DestroyList(L)==OK) printf("���Ա����ٳɹ���\n");
		     else printf("���Ա�����ʧ�ܣ�\n");
		 getchar();getchar();
		 break;
	   case 3:     //������Ա�����ClearList���� 
		if(ClearList(L)==OK) printf("���Ա���ճɹ���\n");
		     else printf("���Ա����ʧ�ܣ�\n");   
		 getchar();getchar();
		 break;
	   case 4:     //�ж����Ա��Ƿ�Ϊ�ձ�����ListEmpty���� 
		 if(ListEmpty(L)==TRUE) printf("���Ա��ǿձ�\n");
		     else if(ListEmpty(L)==INFEASIABLE) printf("���Ա����ڣ�\n");
		     else printf("���Ա��ǿձ�\n");
		 getchar();getchar();
		 break;
	    case 5:     //���������ListLength���� 
	    int a;
	   	 a=ListLength(L);
	   	 if(a==INFEASIABLE) printf("���Ա����ڣ�\n");
			else  printf("���Ա�ĳ�����:%d",a);    
		 getchar();getchar();
		 break;
	   case 6:     //�������Ա���ĳһԪ�أ�����GetElem���� 
		 printf("Ҫ�������Ա��еڼ���Ԫ�أ�\n");
		 int k;ElemType e;
		 scanf("%d",&k);
		 if(GetElem(L,k,e,ListLength)==OK) printf("��Ԫ����%d\n",e);
		     else printf("������Ч��\n");       
		 getchar();getchar();
		 break;
	   case 7:     //��λԪ�أ�����LocateElem���� 
	   int m,i;
	   	printf("����Ҫ��λ��Ԫ�أ�\n");
		 scanf("%d",&m); 
		 k=LocateElem(L,m,compare);
		 if(k>0) printf("��Ԫ�������Ա��еĵ�һ��λ����:%d",k);
		     else if(LocateElem(L,m,compare)==INFEASIABLE) printf("���Ա����ڣ�\n");
		     else printf("0");  
		 getchar();getchar();
		 break;
	   case 8:     //��ǰ��������PriorElem���� 
	   	ElemType cur_e,pre_e;
		printf("�������Ա��е�ĳһԪ��:\n");
		scanf("%d",&cur_e); 
	   	if(PriorElem(L,cur_e,pre_e)) printf("��Ԫ�ص�ǰ����%d",pre_e);
	   	else printf("������Ч��\n");    
		 getchar();getchar();
		 break;
	   case 9:     //���̣�����NextElem���� 
	   	ElemType p,q;
		 printf("�������Ա��е�ĳһԪ��:\n");
		scanf("%d",&p);  
		if(NextElem(L,p,q)) printf("��Ԫ�صĺ����%d",q);
	   	else printf("������Ч��\n");   
		 getchar();getchar();
		 break;
	   case 10:     //����Ԫ�أ�����ListInsert���� 
		 printf("Ҫ�����Ա�ĵڼ���λ��֮ǰ����ʲô����Ԫ�أ�\n");
		 int r,t;
		 scanf("%d\t%d",&r,&t);    
		 if(ListInsert(L,r,t,ListLength)==OK) {
		 	printf("����ɹ���");printf("����Ԫ�غ�����Ա�Ϊ��\n"); ListTraverse(L,visit);
		 }
		 else printf("������Ч��\n");
		 getchar();getchar();
		 break;
	   case 11:     //ɾ��Ԫ�أ�����ListDelete���� 
		 printf("ɾ�����Ա�ĵڼ�������Ԫ�أ�\n");
		 int j;ElemType v;
		 scanf("%d",&j);    
		 if(ListDelete(L,j,v,ListLength)==OK) {
		 	printf("ɾ���ɹ���ɾ��������Ԫ��Ϊ��%d",v);printf("ɾ��Ԫ�غ�����Ա�Ϊ��\n"); ListTraverse(L,visit);
		 }
		 else printf("������Ч��\n");  
		 getchar();getchar();
		 break;
	   case 12:    //�������Ա�����ListTraverse����    
		if(!ListTraverse(L,visit)) printf("���Ա����ڣ�\n");
		getchar();getchar();
		 break;
	   case 13:     //�������Ա�����CreateList���� 
	   	printf("Input the number of elements:");
	    scanf("%d",&n);
	   	CreateList(L,n);
	   	printf("����%d��Ԫ�ص����Ա����ɹ���\n",n);
	   	getchar();getchar();
	   	break;
	   case 14:     //���򣬵���ListSort���� 
	     if(ListSort(L)==OK) {
	     	printf("����ɹ���\n");ListTraverse(L,visit);
		 }
		 else printf("������Ч��\n");
		 getchar();getchar();
		 break; 
	   	case 15:     //�����ֵ��Сֵ������ListMaxMin���� 
		 int max,min;
		 if(ListMaxMin(L,max,min)==OK) printf("���Ա�����ֵΪ%d\n���Ա����СֵΪ%d",max,min);
		 else printf("������Ч��\n");
		 getchar();getchar();
		 break; 
		 case 16:     //�����Ա�����ļ�������ListSave���� 
		 char filename[100];
	     printf("input file name: ");
	     scanf("%s",filename);
	     if(ListSave(L,filename)==OK) printf("���Ա�����ļ��ɹ���\n"); 
		 else printf("���Ա�����ļ�ʧ�ܣ�\n");
		 getchar();getchar();
		 break;
         case 17:     //���ļ���ȡ���Ա�����ListLoad���� 
	     if(ListLoad(L)==OK) printf("���ļ���ȡ���Ա�ɹ���\n");
		 else printf("���ļ���ȡ���Ա�ʧ�ܣ�\n");
		 getchar();getchar();
		 break;
	    case 0:
	    	break;
	}//end of switch
  }//end of while
printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
return 0;
}//end of main()

