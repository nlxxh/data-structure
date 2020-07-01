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

typedef int ElemType;
typedef int Status; 
typedef struct{
	ElemType *elem;     //�洢�ռ��ַ 
	int length;     //��ǰ���� 
	int listsize;     //��ǰ����Ĵ洢���� 
}SqList;
Status InitList(SqList &L){
	L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.elem) exit(OVERFLOW);     //�洢����ʧ�� 
	L.length=0;     //�ձ���Ϊ0 
	L.listsize=LIST_INIT_SIZE;     //��ʼ�洢���� 
	return OK;
}//����һ���յ����Ա� 
Status DestroyList(SqList &L){
	if(!L.elem) return ERROR;     //���Ա����ڣ�����ʧ�� 
	L.length=0;
	L.listsize=0;
	L.elem=NULL;      //���Ա�ռ��ַ�ÿ� 
	return OK;
}//�������Ա� 
Status ClearList(SqList &L){
	if(!L.elem) return ERROR;     //���Ա����ڣ��ÿ�ʧ�� 
	L.length=0;
	return OK;
}//�����Ա���Ϊ�ձ� 
Status ListEmpty(SqList &L){
	if(!L.elem) return INFEASIABLE;     //���Ա����ڣ��޷��ж� 
	else if(L.length==0) return TRUE;
	else return FALSE; 
}//�ж����Ա��Ƿ�Ϊ�ձ� 
Status ListLength(SqList &L){
	int k;
	if(!L.elem) return INFEASIABLE;     //���Ա����ڣ��޷��󳤶� 
	return L.length;
}//�����Ա�ĳ��� 
Status GetElem(SqList &L,int i,ElemType &e) {
	if((i<1)||(i>L.length)||(!L.elem)||(L.length==0)) return ERROR;     //iֵ���Ϸ������Ա����ڻ����Ա�Ϊ�ձ�ʱ��������Ч 
	e=L.elem[i-1];     //eΪ���Ա��i������Ԫ�ص�ֵ 
	return OK;
}//��e�������Ա��е�i������Ԫ�ص�ֵ 
Status compare(ElemType a,ElemType b)
{
	if(a==b) return OK;
	else return 0;
}//����compare��������LocateElem�������� 
Status LocateElem(SqList &L,ElemType e,Status(*compare)(ElemType,ElemType)){
	if(!L.elem) return INFEASIABLE;     //���Ա����ڣ�������Ч 
	int i=1;     //i�ĳ�ֵΪ��1��Ԫ�ص�λ�� 
	ElemType *p;
	p=L.elem;     //p�ĳ�ֵΪ��1��Ԫ�صĴ洢λ�� 
	while((i<=L.length)&&!(*compare)(*p++,e)) ++i;
	if(i<=L.length) return i;
	else return 0;     //û�ҵ�������0 
}//�����Ա��в��ҵ�1��ֵ��e����compare()��Ԫ�ص�λ�� 
Status PriorElem(SqList &L,ElemType &cur_e,ElemType &pre_e){
	if((!L.elem)||(L.length==0)) return ERROR;     //���Ա����ڻ����Ա�Ϊ�ձ�������Ч 
	int k=0;
	while(k<=L.length){
		if((L.elem[k]==cur_e)&&(k!=0)) break;     //kΪԪ��cur_e��λ�� 
		k++;}
		if(k<=L.length) pre_e=L.elem[k-1];     //pre_e��λ��Ϊk-1 
		else return ERROR;     //cur_e���������Ա���Ǳ��е�1��Ԫ�أ�������Ч 
	}//��pre_e�������Ա���Ԫ��cur_e��ǰ�� 
Status NextElem(SqList &L,ElemType &cur_e,ElemType &next_e){
	if((!L.elem)||(L.length==0)) return ERROR;     //���Ա����ڻ����Ա�Ϊ�ձ�������Ч 
	int k=0;
	while(k<=L.length){
		if(L.elem[k]==cur_e) break;     //kΪԪ��cur_e��λ�� 
		k++;}
		if(k+1<L.length) next_e=L.elem[k+1];     //next_e��λ��Ϊk+1 
		else return ERROR;     //cur_e���������Ա���Ǳ������1��Ԫ�أ�������Ч 
}//��next_e�������Ա���Ԫ��cur_e�ĺ�� 
Status ListInsert(SqList &L,int i,ElemType e){
	if((i<1)||(i>L.length+1)||(!L.elem)||(L.length==0)) return ERROR;     //iֵ���Ϸ������Ա����ڻ����Ա�Ϊ�ձ�ʱ��������Ч 
	if(L.length>=L.listsize) {     //��ǰ�洢�ռ����������ӷ��� 
		ElemType *newbase;
		newbase=(ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
		if(!newbase) exit(OVERFLOW);     //�洢����ʧ�� 
		L.elem=newbase;     //�»�ַ 
		L.listsize+=LISTINCREMENT;     //���Ӵ洢���� 
}
	ElemType *q;ElemType *p;
	q=&(L.elem[i-1]);     //qΪ����λ�� 
	for(p=&(L.elem[L.length-1]);p>=q;--p) *(p+1)=*p;     //����λ�ü�֮���Ԫ������ 
	*q=e;     //����e 
	++L.length;     //����1 
	return OK;
}//�����Ա��е�i��λ��֮ǰ�����µ�Ԫ��e 
Status ListDelete(SqList &L,int i,ElemType &e){
	if((i<1)||(i>L.length)||(!L.elem)||(L.length==0)) return ERROR;     //iֵ���Ϸ������Ա����ڻ����Ա�Ϊ�ձ�ʱ��������Ч
	ElemType *q;ElemType *p;
	p=&(L.elem[i-1]);     //pΪ��ɾ��Ԫ�ص�λ�� 
	e=*p;     //��ɾ��Ԫ�ص�ֵ����e 
	q=L.elem+L.length-1;     //��βԪ�ص�λ�� 
	for(++p;p<=q;++p) *(p-1)=*p;     //��ɾ��Ԫ��֮���Ԫ������ 
	--L.length;     //����1 
	return OK;	
}//�����Ա���ɾ����i��Ԫ�أ�����e������ֵ 
Status CreateList(SqList &L,int n){
	int i;
	L.elem=(ElemType*)malloc(n*sizeof(ElemType));
	L.length=n;     //�������Ա�ĳ��� 
	L.listsize=LIST_INIT_SIZE;
	printf("Input elements:");
	for(i=0;i<n;i++)
	scanf("%d",&L.elem[i]);     //�������Ա��е�Ԫ�� 
}//����Ԫ�أ��������Ա� 
void visit(ElemType a){
	printf("%d ",a);
}//����visit��������ListTraverse�������� 
Status ListTraverse(SqList &L,void(*visit)(ElemType)){
	if(!L.elem) return ERROR;     //���Ա����ڣ�������Ч 
	printf("�����Ա�ĳ���Ϊ:%d\n",L.length);
	printf("�����Ա��Ԫ��Ϊ:\n");
	int i;
	for(i=0;i<L.length;i++)
	(*visit)(L.elem[i]);     // �Ա���ÿ��Ԫ�ص��ú���visit 
	return OK;
}//�������Ա��Ա���ÿ��Ԫ�ص��ú���visit���������ÿ��Ԫ�ؼ��� 
Status ListSort(SqList &L){
	if((!L.elem)||(L.length==0)) return ERROR;     //���Ա����ڻ����Ա�Ϊ�ձ�������Ч 
	int i,j;
	ElemType a;
	for(i=0;i<L.length-1;i++)
	{		
	    for(j=0;j<L.length-i-1;j++){
		if(L.elem[j]>L.elem[j+1]) {a=L.elem[j];L.elem[j]=L.elem[j+1];L.elem[j+1]=a;}
	}   }  //ð������ 
	return OK;
}//�����Ա�������Ԫ�ذ���С�������� 
int maximum(int a[],int N){
	int max=a[0];
	int i;
	for(i=0;i<N;i++) {if(a[i]>max) max=a[i];}
	return max;
}//����maximum��������ListMaxMin�������� 
int minimum(int a[],int N){
	int min=a[0];
    int i;
	for(i=0;i<N;i++) {if(a[i]<min) min=a[i];}
	return min;
}//����minimum��������ListMaxMin�������� 
Status ListMaxMin(SqList &L,int(*maximum)(int[],int),int(*minimum)(int[],int),ElemType &max,ElemType &min){
	if((!L.elem)||(L.length==0)) return ERROR;     //���Ա����ڻ����Ա�Ϊ�ձ�������Ч 
	max=maximum(L.elem,L.length);     //max�������Ա�������Ԫ�ص����ֵ 
	min=minimum(L.elem,L.length);     //min�������Ա�������Ԫ�ص���Сֵ 
	return OK;
}//�����Ա�������Ԫ�ص����ֵ����Сֵ 
Status ListSave(SqList &L,char *filename){
	FILE  *fp;int i; 
	if ((fp=fopen(filename,"wb"))==NULL)
	{
	printf("File open error\n ");
	return ERROR;
	}     //�ļ������ڣ���ʾ������Ϣ 
	for(i=0;i<L.length;i++)
		fprintf(fp,"%d\t",L.elem[i]);     //��fprintf���������Ա���ÿ��Ԫ�ش����ļ� 
    fclose(fp);
	return OK;
}//�����Ա�����ļ� 
Status ListLoad(SqList &L){
	FILE  *fp;int i=0;
	if ((fp=fopen("D:\\ryt.txt","rb"))==NULL)
	{
	printf("File open error\n ");
	return ERROR;
	}     //�ļ������ڣ���ʾ������Ϣ 
	InitList(L);     //�����ձ� 
	while(!feof(fp)){
		fscanf(fp,"%d",&L.elem[i]);     //��fscanf�������ļ���ÿ��Ԫ�ض������Ա� 
		i++;
		L.length++;
	}
	ListTraverse(L,visit); 
    fclose(fp);
	return OK;
}//���ļ��������Ա� 
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
	printf("    ��ѡ����Ĳ���[0~17]:");     //�˵� 
	scanf("%d",&op);
    switch(op){     //��switch����ʵ�ֲ˵����� 
	   case 1:     //�����ձ�����InitList���� 
		 if(InitList(L)==OK) printf("���Ա����ɹ���\n");
		     else printf("���Ա���ʧ�ܣ�\n");
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
		 if(GetElem(L,k,e)==OK) printf("��Ԫ����%d\n",e);
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
		 if(ListInsert(L,r,t)==OK) {
		 	printf("����ɹ���");printf("����Ԫ�غ�����Ա�Ϊ��\n"); ListTraverse(L,visit);
		 }
		 else printf("������Ч��\n");
		 getchar();getchar();
		 break;
	   case 11:     //ɾ��Ԫ�أ�����ListDelete���� 
		 printf("ɾ�����Ա�ĵڼ�������Ԫ�أ�\n");
		 int j;ElemType v;
		 scanf("%d",&j);    
		 if(ListDelete(L,j,v)==OK) {
		 	printf("ɾ���ɹ���ɾ��������Ԫ��Ϊ��%d",v);printf("ɾ��Ԫ�غ�����Ա�Ϊ��\n"); ListTraverse(L,visit);
		 }
		 else printf("������Ч��\n");
		 getchar();getchar();
		 break;
	   case 12:     //�������Ա�����ListTraverse����    
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
		 if(ListMaxMin(L,maximum,minimum,max,min)==OK) printf("���Ա�����ֵΪ%d\n���Ա����СֵΪ%d",max,min);
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
}

