#include<iostream>
#include<stdio.h>
#include<string.h>
#include <malloc.h>
#include <stdlib.h>
#define TRUE 1  
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIABLE -1
#define OVERFLOW -2
using namespace std;
typedef char TElemType;
typedef int Status; 
typedef struct BiTNode{
	TElemType data;     //���ؼ��� 
	struct BiTNode *lchild,*rchild;     //���Һ���ָ�� 
	int index;     //������� 
}BiTNode,*BiTree;

BiTree Find(BiTree T, char key) {
	BiTree T1;
	if (T == NULL) return NULL;     //������Ϊ�գ����ؿ�ָ��
	if (T->data == key) return T;     //�ҵ�Ŀ��ؼ��֣�����ָ�� 
	else {
		T1 = Find(T->lchild, key);     //�ݹ����������
		if (T1 != NULL) return T1;
		T1 = Find(T->rchild, key);      //�ݹ����������
		if (T1 != NULL) return T1;
	}
	return NULL;     //δ�ҵ�Ŀ��ؼ��֣����ؿ�ָ��
}//����Find��������λ�ؼ��� 
BiTree QZBiTree(char *a,char *b,int *c,int *d,int size){
	if(size==0) return NULL;     //���г���Ϊ0�����ؿ�ָ�� 
	int i;int r=-1;
	for(i=0;i<size;i++)
	if(b[i]==a[0]) {r=i;break;}     //�������������ҵ����ڵ��λ�� 
	BiTree T=(BiTNode*)malloc(sizeof(BiTNode));
	T->data=b[r];
	T->index=d[r];
	T->lchild=QZBiTree(a+1,b,c+1,d,r);     //�ݹ鴴�������� 
	T->rchild=QZBiTree(a+r+1,b+r+1,c+r+1,d+r+1,size-r-1);     //�ݹ鴴�������� 	
	return T;	
}//����ǰ��+���򴴽���������������CreateBiTree���� 
BiTree HZBiTree(char *a,char *b,int *c,int *d,int size){
	if(size==0) return NULL;     //���г���Ϊ0�����ؿ�ָ�� 
	int i;int r=-1;
	for(i=0;i<size;i++)
	if(b[i]==a[size-1]) {r=i;break;}     //�������������ҵ����ڵ��λ�� 
	BiTree T=(BiTNode*)malloc(sizeof(BiTNode));
	T->data=b[r];
	T->index=d[r];
	T->lchild=HZBiTree(a,b,c,d,r);     //�ݹ鴴�������� 
	T->rchild=HZBiTree(a+r,b+r+1,c+r,d+r+1,size-r-1);     //�ݹ鴴�������� 		
	return T;	
}//����+���򴴽�����������CreateBiTree����  
Status CreateBiTree(BiTree &T,int definition){
	TElemType ch;
	if(definition==1) {     //definitionֵΪ1������ǰ�����д��������� 
	printf("��������ؼ��֣�\n");
	scanf("%c", &ch);
	getchar();
	if (ch == '#') T = NULL;     //'#'����ָ��Ϊ�� 
	else {
		if (!(T = (BiTNode*)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
		T->data = ch;
		printf("�����������ݣ�\n");
		scanf("%d", &T->index);
		getchar();
		CreateBiTree(T->lchild,definition);     //�ݹ鴴��������  
		CreateBiTree(T->rchild,definition);     //�ݹ鴴�������� 	
	}return OK;
}     //ǰ�򴴽�������  
	else if(definition==2){     //definitionֵΪ2������ǰ��+�������д��������� 
	char a[100],b[100];int c[100];int d[100];int size,i;
	printf("�������г��ȣ�\n");
	scanf("%d",&size);      
	if(size<0) printf("���г��Ȳ��Ϸ���\n");     //���г���С��0�����Ϸ�
	else if(size==0) {printf("������Ϊ�գ�\n");T=NULL;     //���г���Ϊ0��������Ϊ��
	}
	else{
	printf("����ǰ�����йؼ��֣�\n");
	scanf("%s",a);
	printf("����ǰ���������ݣ�\n");
	for(i=0;i<size;i++)
	scanf("%d",&c[i]);
	printf("�����������йؼ��֣�\n");
	scanf("%s",b);
	printf("���������������ݣ�\n");
	for(i=0;i<size;i++)
	scanf("%d",&d[i]);
	if(T=QZBiTree(a,b,c,d,size)) printf("ǰ��+���򹹽��������ɹ���\n");     //����QZBiTree���� 
	else printf("ǰ��+���򹹽�������ʧ�ܣ�\n"); 
}}     //ǰ��+���򴴽������� 
	else{     //definitionֵΪ3���������+�������д��������� 
	char a[100],b[100];int c[100];int d[100];int size,i;
	printf("�������г��ȣ�\n");
	scanf("%d",&size);
	if(size<0) printf("���г��Ȳ��Ϸ���\n");     //���г���С��0�����Ϸ�
	else if(size==0) {printf("������Ϊ�գ�\n");T=NULL;     //���г���Ϊ0��������Ϊ��
	}
	else{
	printf("����������йؼ��֣�\n");
	scanf("%s",a);
	printf("��������������ݣ�\n");
	for(i=0;i<size;i++)
	scanf("%d",&c[i]);
	printf("�����������йؼ��֣�\n");
	scanf("%s",b);
	printf("���������������ݣ�\n");
	for(i=0;i<size;i++)
	scanf("%d",&d[i]);
	if(T=HZBiTree(a,b,c,d,size)) printf("����+���򹹽��������ɹ���\n");     //����HZBiTree���� 
	else printf("����+���򹹽�������ʧ�ܣ�\n");	
	}}//����+���򴴽������� 
}     
Status DestroyBiTree(BiTree &T){
	if(T==NULL) return ERROR;     //�����������ڣ�����ʧ�� 
	else{
		if (T->lchild)
			DestroyBiTree(T->lchild);     //�ݹ����������� 
		if (T->rchild)
			DestroyBiTree(T->rchild);     //�ݹ����������� 
		free(T);
		T = NULL;
	}
	return OK;
}//���ٶ����� 
Status ClearBiTree(BiTree &T){
	if(T==NULL) return ERROR; 
	else{
		T->lchild = NULL;     //��������� 
		T->rchild = NULL;     //��������� 
		T = NULL;
	}
	return OK;
}//��ն�����
Status BiTreeEmpty(BiTree T) {
	if (T) return FALSE;
	return TRUE;
}//�ж��ն����� 
int MAX(int a, int b) {
	if (a >= b) return a;
	else return b;
}//����MAX��������BiTreeDepth���� 
Status BiTreeDepth(BiTree T) {
	if (!T) return 0;     //������Ϊ�գ���ȷ���Ϊ0
	else {
		if ((T->lchild == NULL) && (T->rchild == NULL)) return 1;      //������ֻ��һ����㣬��ȷ���Ϊ1 
		else return 1+MAX(BiTreeDepth(T->lchild), BiTreeDepth(T->rchild));     //���������Ϊ����������ȵ����ֵ 
	}
}//���������� 
Status LocateNode(BiTree T,TElemType e){
	if(T==NULL) return ERROR;     //�����������ڣ����ش�����Ϣ  
	BiTree p =T;
    p=Find(T,e);     //����Find���������عؼ��ֵ�ָ�� 
    if(p==NULL) return ERROR;     //δ�ҵ��ؼ��֣����ش�����Ϣ 
    printf("���ҳɹ�����������Ϊ��%d",p->index);
	return OK;
}//���ҽ�� 
Status Assign(BiTree &T,TElemType e,int value){
	if(T==NULL) return ERROR;     //�����������ڣ���ֵʧ�� 
    BiTree p;
    p=Find(T,e);     //����Find���������عؼ��ֵ�ָ�� 
    if(p==NULL) return ERROR;     //δ�ҵ��ؼ��֣���ֵʧ�� 
    p->index=value;     //��㸳ֵ 
	printf("��ֵ�ɹ���\n");
}//��㸳ֵ 
Status LeftSibling(BiTree T,TElemType e){
    BiTree s[100];     //����ָ��ջ�����������������Ȳ�����100 
    int top=0;     //�ÿ�ջ��topΪջ��Ԫ����һ����Ԫ�ĵ�ַ 
    BiTree p =T;
    while (top || p)
    {
        if (p)     
        {
            s[top++]=p;     //��ָ���ջ 
            if(p->rchild!=NULL&&p->rchild->data==e) {printf("���ҳɹ����������ֵܵĹؼ���Ϊ��%c",p->lchild->data);break;return OK;
			}     //�������ֵܽ�� 
			p = p->lchild;     //���������� 
        }     //������ջ��Ԫ�ص�ָ��Ϊ�����Ķ������������� 
        else
        {
            p = s[--top];     //������ָ��
           if(p->rchild!=NULL&&p->rchild->data==e) {printf("���ҳɹ����������ֵܵĹؼ���Ϊ��%c",p->lchild->data);break;return OK;
			}     //�������ֵܽ��  
            p = p->rchild;     //���������� 
        }
    }
    if(!top) return ERROR;
}//������ֵܽ�� 
Status RightSibling(BiTree T,TElemType e){
    BiTree s[100];     //����ָ��ջ�����������������Ȳ�����100 
    int top=0;     //�ÿ�ջ��topΪջ��Ԫ����һ����Ԫ�ĵ�ַ 
    BiTree p =T;
    while (top || p)
    {
        if (p)
        {
            s[top++]=p;     //��ָ���ջ 
            if(p->lchild!=NULL&&p->lchild->data==e) {printf("���ҳɹ����������ֵܵĹؼ���Ϊ��%c",p->rchild->data);break;return OK;
			}     //�������ֵܽ��  
			p = p->lchild;     //���������� 
        }     //������ջ��Ԫ�ص�ָ��Ϊ�����Ķ������������� 
        else
        {
            p = s[--top];     //������ָ��
           if(p->lchild!=NULL&&p->lchild->data==e) {printf("���ҳɹ����������ֵܵĹؼ���Ϊ��%c",p->rchild->data);break;return OK;
			}     //�������ֵܽ��   
            p = p->rchild;     //���������� 
        }
    }
    if(!top) return ERROR;
}//������ֵܽ��
Status InsertNode(BiTree &T,TElemType e,int LR,BiTree &c){
	c=(BiTNode*)malloc(sizeof(BiTNode));     //������������ 
	printf("�������������Ĺؼ��֣�\n");
	scanf("%c",&c->data);
	printf("�����������������ݣ�\n");
	scanf("%d",&c->index);
	c->rchild=NULL;c->lchild=NULL;
	BiTree q;
	q=Find(T,e);     //����Find�������ҵ����д�����λ�õĽ�� 
	if(q==NULL) return ERROR;      //δ�ҵ�������λ�õĽ�� �����ش�����Ϣ 
    else if(LR==0) {     //LRΪ0����� 
    	if(q->lchild!=NULL) c->rchild=q->lchild;     //���e��ԭ��������Ϊ���c��������  
		q->lchild=c;     //������c��Ϊ�ؼ���Ϊe�Ľ������ӽ�� 
    	return OK;
	}
	else if(LR==1) {     //LRΪ1����� 
		if(q->rchild!=NULL) c->rchild=q->rchild;     //���e��ԭ��������Ϊ���c��������  
		q->rchild=c;     //������c��Ϊ�ؼ���Ϊe�Ľ����Һ��ӽ�� 
    	return OK;
	}
	else return ERROR;
}//������ 
Status DeleteNode(BiTree &T,TElemType e){
	if(T==NULL) return ERROR;     //�����������ڣ�ɾ��ʧ��  
	BiTree s[100];     //����ָ��ջ�����������������Ȳ�����100 
    int top=0;     //�ÿ�ջ��topΪջ��Ԫ����һ����Ԫ�ĵ�ַ 
    BiTree p =T;BiTree q,h,j,g;int k=0;
    if(T->data==e) k=3;     //ɾ�����Ϊ���ڵ㣬k��Ϊ3 
	else{
    while (top || p)
    {
        if (p)
        {
            s[top++]=p;     //��ָ���ջ 
            if(p->rchild!=NULL&&p->rchild->data==e) {k=1;q=p;break;return OK;
			}     //ɾ�����Ϊq���Һ��ӣ�k��Ϊ1 
            else if (p->lchild!=NULL&&p->lchild->data==e) {k=2;q=p;break;return OK;
			}     //ɾ�����Ϊq�����ӣ�k��Ϊ2  
			p = p->lchild;     //���������� 
        }
        else
        {
            p = s[--top];     //������ָ��
           if(p->rchild!=NULL&&p->rchild->data==e) {k=1;q=p;break;return OK;
			}      //ɾ�����Ϊq���Һ��ӣ�k��Ϊ1 
            else if(p->lchild!=NULL&&p->lchild->data==e) {k=2;q=p;break;return OK;
			}     //ɾ�����Ϊq�����ӣ�k��Ϊ2  
            p = p->rchild;     //���������� 
        }
    }
    if(!top) return ERROR;
}
    if(k==1){     //kΪ1��ɾ�����Ϊq���Һ��ӵ���� 
    	h=q->rchild;     
		if(h->rchild==NULL&&h->lchild==NULL) {free(h);q->rchild=NULL;
		}     //ɾ�����ؼ��ֵĶ�Ϊ0��ֱ��ɾ��
		else if(h->rchild!=NULL&&h->lchild!=NULL) {j=h->lchild;g=h->rchild;free(h);q->rchild=j;
		while(j->rchild!=NULL) j=j->rchild;j->rchild=g;
		}     //ɾ�����ؼ��ֵĶ�Ϊ2����e�����Ӵ��汻ɾ����eλ�ã�e����������Ϊe�������������ҽ���������
		else if(h->rchild==NULL&&h->lchild!=NULL){j=h->lchild;free(h);q->rchild=j;
		}     //ɾ�����ؼ��ֵĶ�Ϊ1��ֻ�����ӣ��ùؼ���Ϊe�Ľ�㺢�Ӵ��汻ɾ����eλ�� 
		else{j=h->rchild;free(h);q->rchild=j;
		}     //ɾ�����ؼ��ֵĶ�Ϊ1��ֻ���Һ��ӣ��ùؼ���Ϊe�Ľ�㺢�Ӵ��汻ɾ����eλ�� 
	}
	else if(k==2){     //kΪ2��ɾ�����Ϊq�����ӵ���� 
		h=q->lchild;
		if(h->rchild==NULL&&h->lchild==NULL) {free(h);q->lchild=NULL;
		}     //ɾ�����ؼ��ֵĶ�Ϊ0��ֱ��ɾ��
		else if(h->rchild!=NULL&&h->lchild!=NULL) {j=h->lchild;g=h->rchild;free(h);q->lchild=j;
		while(j->rchild!=NULL) j=j->rchild;j->rchild=g;
		}     //ɾ�����ؼ��ֵĶ�Ϊ2����e�����Ӵ��汻ɾ����eλ�ã�e����������Ϊe�������������ҽ���������
		else if(h->rchild==NULL&&h->lchild!=NULL){j=h->lchild;free(h);q->lchild=j;
		}     //ɾ�����ؼ��ֵĶ�Ϊ1��ֻ�����ӣ��ùؼ���Ϊe�Ľ�㺢�Ӵ��汻ɾ����eλ�� 
		else{j=h->rchild;free(h);q->lchild=j;
		}     //ɾ�����ؼ��ֵĶ�Ϊ1��ֻ���Һ��ӣ��ùؼ���Ϊe�Ľ�㺢�Ӵ��汻ɾ����eλ�� 
	}
	else if(k==3){     //kΪ3��ɾ�����Ϊ���ڵ����� 
		if(T->rchild==NULL&&T->lchild==NULL) {free(T);T=NULL;
		}     //ɾ�����ؼ��ֵĶ�Ϊ0��ֱ��ɾ��
		else if(T->rchild!=NULL&&T->lchild!=NULL){j=T->lchild;g=T->rchild;free(T);T=j;
		while(j->rchild!=NULL) j=j->rchild;j->rchild=g;
		}     //ɾ�����ؼ��ֵĶ�Ϊ2����e�����Ӵ��汻ɾ����eλ�ã�e����������Ϊe�������������ҽ���������
		else if(T->rchild==NULL&&T->lchild!=NULL){j=T->lchild;free(T);T=j;
		}     //ɾ�����ؼ��ֵĶ�Ϊ1��ֻ�����ӣ��ùؼ���Ϊe�Ľ�㺢�Ӵ��汻ɾ����eλ�� 
		else{j=T->rchild;free(T);T=j;
		}     //ɾ�����ؼ��ֵĶ�Ϊ1��ֻ���Һ��ӣ��ùؼ���Ϊe�Ľ�㺢�Ӵ��汻ɾ����eλ�� 
	}
	return OK;
	}//ɾ����� 
Status Visit(BiTNode a){
	printf("���ؼ���Ϊ��%c  �������Ϊ��%d\n",a.data,a.index);
	return OK;
}//����Visit�������������������� 
Status PreOrderTraverse(BiTree &T,Status(*Visit)(BiTNode)){
	if(T){if(Visit(*T))     //����Visit���� 
	if(PreOrderTraverse(T->lchild,Visit))     //�ݹ�ǰ����������� 
	if(PreOrderTraverse(T->rchild,Visit)) return OK;     //�ݹ�ǰ����������� 
	return ERROR;
	}else return OK;
}//ǰ����� 
Status InOrderTraverse(BiTree T,Status(*Visit)(BiTNode)){
    BiTree s[100];     //����ָ��ջ�����������������Ȳ�����100 
    int top=0;     //�ÿ�ջ��topΪջ��Ԫ����һ����Ԫ�ĵ�ַ 
    BiTree p =T;
    while (top || p)
    {
        if (p)
        {
            s[top++]=p;     //��ָ���ջ 
            p = p->lchild;     //���������� 
        }
        else
        {
            p = s[--top];     //������ָ�� 
            if(!Visit(*p)) return ERROR;     //����Visit���� 
            p = p->rchild;     //���������� 
        }
    }
    return OK;
}//������� 
Status PostOrderTraverse(BiTree &T,Status(*Visit)(BiTNode)){
	if(T){if(PostOrderTraverse(T->lchild,Visit))     //�ݹ������������� 
	if(PostOrderTraverse(T->rchild,Visit))     //�ݹ�������������  
	if(Visit(*T)) return OK;     //����Visit���� 
	return ERROR;
	}else return OK;
}//������� 
Status LevelOrderTraverse(BiTree &T,Status(*Visit)(BiTNode)){
    BiTree s[100];     //����ָ��ջ�����������������Ȳ�����100 
    int top=0;     //�ÿ�ջ��topΪջ��Ԫ����һ����Ԫ�ĵ�ַ 
	int rear=0;     //rearΪջ��Ԫ�صĵ�ַ 
    BiTree p=T;
	if(p!=NULL) s[top++]=p;     //��ָ���ջ 
	while(top!=rear){
		if(!Visit(*(s[rear]))) return ERROR;     //����Visit���� 
		if(p->lchild!=NULL) {s[top++]=p->lchild;
		}     //�����Ƚ�ջ 
		if(p->rchild!=NULL) {s[top++]=p->rchild;
		}     //�Һ��Ӻ��ջ 
        rear++;     //ջ��ָ������ 
		p=s[rear];
	}

    return OK;
}//������� 
Status LeftChild(BiTree T,TElemType e){
	BiTree p;
	p=Find(T,e);     //����Find�������ҵ��ؼ���Ϊe�Ľ�� 
	if(p==NULL||p->lchild==NULL||T==NULL) return ERROR;     //�����������ڣ���ؼ���Ϊe�Ľ��δ�ҵ��򲻴������ӣ����������Ϣ 
	else printf("���ҳɹ���������ӵĹؼ���Ϊ��%c",p->lchild->data);
}//������ӽ�� 
Status RightChild(BiTree T,TElemType e){
	BiTree p;
	p=Find(T,e);     //����Find�������ҵ��ؼ���Ϊe�Ľ�� 
	if(p==NULL||p->rchild==NULL||T==NULL) return ERROR;     //�����������ڣ���ؼ���Ϊe�Ľ��δ�ҵ��򲻴����Һ��ӣ����������Ϣ 
	else printf("���ҳɹ�������Һ��ӵĹؼ���Ϊ��%c",p->rchild->data);
}//����Һ��ӽ�� 
BiTree Parent(BiTree T,TElemType e){
	BiTree T1;
	if(T){
	if((T->lchild!=NULL&&T->lchild->data==e)||(T->rchild!=NULL&&T->rchild->data==e)) return T;     
	T1=Parent(T->lchild,e);     //�ݹ����������ĸ�ĸ��� 
	if(T1!=NULL) return T1;
	T1=Parent(T->rchild,e);     //�ݹ����������ĸ�ĸ��� 
	if(T1!=NULL) return T1;
	}
	return NULL;
}//��ø�ĸ��� 
Status BiTreeSave(BiTree T,char *filename){
	FILE  *fp; 
	if ((fp=fopen(filename,"wb"))==NULL)
	{
	printf("File open error\n ");
	return ERROR;
	}     //�ļ������ڣ���ʾ������Ϣ 	  
	BiTree s[100];     //����ָ��ջ�����������������Ȳ�����100 
    int top=0;     //�ÿ�ջ��topΪջ��Ԫ����һ����Ԫ�ĵ�ַ 
    BiTree p =T;
    while (top || p)
    {
        if (p)
        {
            s[top++]=p;     //��ָ���ջ 
			fprintf(fp,"%c: %d\t",p->data,p->index);     //���������еĽ��ؼ��ֺ����ݴ����ļ� 
			p = p->lchild;     //���������� 
			
        }
        else
        {
            p = s[--top];     //������ָ�� 
            p = p->rchild;     //���������� 
        }
    }
	fclose(fp);
	return OK;
}//�������������ļ� 
int main(void){
	BiTree T; int op=1;
	while(op){
	system("cls");	printf("\n\n");
	printf("      Menu for Bitree On chain Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. CreateBiTree          7. Assign\n");
	printf("    	  2. DestroyBiTree         8. LeftSibling\n");
	printf("    	  3. ClearBiTree           9. RightSibling \n");
	printf("    	  4. BiTreeEmpty          10. InsertNode\n");
	printf("    	  5. BiTreeDepth          11. DeleteNode\n");
	printf("    	  6. LocateNode           12. PreOrderTraverse \n");
	printf("    	  13. InOrderTraverse     14. PostOrderTraverse\n");
	printf("    	  15. LevelOrderTraverse  16. LeftChild\n");
	printf("    	  17. RightChild          18. Parent\n");
	printf("          19. BiTreeSave           0. exit \n");
	printf("-------------------------------------------------\n");
	printf("    ��ѡ����Ĳ���[0~19]:");     //�˵� 
	scanf("%d",&op);
    switch(op){     //��switch����ʵ�ֲ˵����� 
	   case 1:getchar();     //����������������CreateBiTree����   
	   printf("����defintionֵ(1��ǰ��(��������)2��ǰ��+����3������+����):\n");
	   int n;
	   scanf("%d",&n); getchar(); 
	   if(CreateBiTree(T,n)==OK) printf("ǰ�򹹽��������ɹ���\n");
	   getchar();getchar();
	   break;
	   case 2:getchar();     //���ٶ�����������DestroyBiTree���� 
	   if(DestroyBiTree(T)==ERROR) printf("����������ʧ�ܣ�\n");
	   else printf("���������ٳɹ���\n"); 
	   getchar();getchar();
	   break;
	   case 3:getchar();     //��ն�����������ClearBiTree���� 
	   if(ClearBiTree(T)==ERROR) printf("���������ʧ�ܣ�\n");
	   else printf("��������ճɹ���\n"); 
	   getchar();getchar();
	   break;
	   case 4:getchar();     //�ж�����������BiTreeEmpty���� 
	   if (BiTreeEmpty(T) == FALSE) printf("��������Ϊ�գ�\n");
	   else printf("������Ϊ�գ�\n");
	   getchar(); getchar(); 
	   break;
	   case 5:getchar();     //���������ȣ�����BiTreeDepth���� 
	   int a; 
	   a = BiTreeDepth(T);
	   if (BiTreeDepth(T)>0) printf("�����������Ϊ��%d\n", a);
	   else printf("������������ʧ�ܣ�\n"); 
	   getchar(); getchar(); 
	   break;
	   case 6:getchar();     //���ҽ�㣬����LocateNode���� 
	   char e;
	   printf("����������ҵĹؼ��֣�\n");
	   scanf("%c",&e); getchar(); 
	   if(LocateNode(T,e)==ERROR) printf("NULL\n");
	   getchar();getchar();
	   break;
	   case 7:getchar();     //��ֵ������Assign���� 
	   printf("���������ֵ�Ĺؼ��֣�\n");
	   scanf("%c",&e); getchar(); 
	   int value;
	   printf("���������ݣ�\n");
	   scanf("%d",&value); getchar(); 
	   if(Assign(T,e,value)==ERROR) printf("��ֵʧ�ܣ�\n");
	   getchar();getchar();
	   break;
	   case 8:getchar();     //������ֵܽ�㣬����LeftSibling���� 
	   printf("����������ҵĹؼ��֣�\n");
	   scanf("%c",&e); getchar(); 
	   if(LeftSibling(T,e)==ERROR) printf("NULL\n");
	   getchar();getchar();
	   break;
	   case 9:getchar();     //������ֵܽ�㣬����LeftSibling����  
	   printf("����������ҵĹؼ��֣�\n");
	   scanf("%c",&e); getchar(); 
	   if(RightSibling(T,e)==ERROR) printf("NULL\n");
	   getchar();getchar();
	   break;
	   case 10:getchar();      //����ڵ㣬����InsertNode���� 
	   int LR;
	   printf("�����������ķ���(0��1)��0��ʾ��ߣ�1��ʾ�ұߣ�\n");
	   scanf("%d",&LR); getchar(); 
	   printf("�����������λ�ý��Ĺؼ��֣�\n");
	   scanf("%c",&e); getchar();
	   BiTree c;
	   if(InsertNode(T,e,LR,c)==ERROR) printf("����ʧ�ܣ�\n");
	   else printf("����ɹ���\n");
	   getchar();getchar();
	   break;
	   case 11:getchar();     //ɾ����㣬����DeleteNode���� 
	   printf("�������ɾ���Ĺؼ��֣�\n");
	   scanf("%c",&e); getchar(); 
	   if(DeleteNode(T,e)==ERROR) printf("ɾ��ʧ�ܣ�\n");
	   else printf("ɾ���ɹ���\n");
	   getchar();getchar();
	   break;
	   case 12:getchar();     //ǰ�����������PreOrderTraverse���� 
	   if(PreOrderTraverse(T,Visit)==OK) printf("������ǰ������ɹ���\n");
	   else printf("������ǰ�����ʧ�ܣ�\n"); 
	   getchar();getchar();
	   break;	
	   case 13:getchar();     //�������������InOrderTraverse���� 
	   if(InOrderTraverse(T,Visit)==OK) printf("��������������ɹ���\n");
	   else printf("�������������ʧ�ܣ�\n"); 
	   getchar();getchar();
	   break;
	   case 14:getchar();     //�������������PostOrderTraverse���� 
	   if(PostOrderTraverse(T,Visit)==OK) printf("��������������ɹ���\n");
	   else printf("�������������ʧ�ܣ�\n"); 
	   getchar();getchar();
	   break;
	   case 15:getchar();     //�������������LevelOrderTraverse���� 
	   if(LevelOrderTraverse(T,Visit)==OK) printf("��������������ɹ���\n");
	   else printf("�������������ʧ�ܣ�\n"); 
	   getchar();getchar();
	   break;
	   case 16:getchar();     //�������ӣ�����LeftChild���� 
	   printf("����������ҵĹؼ��֣�\n");
	   scanf("%c",&e); getchar(); 
	   if(LeftChild(T,e)==ERROR) printf("���Ӳ���ʧ�ܣ�\n");
	   getchar();getchar();
	   break;
	   case 17:getchar();     //�����Һ��ӣ�����RightChild���� 
	   printf("����������ҵĹؼ��֣�\n");
	   scanf("%c",&e); getchar(); 
	   if(RightChild(T,e)==ERROR) printf("�Һ��Ӳ���ʧ�ܣ�\n");
	   getchar();getchar();
	   break;
	   case 18:getchar();     //���Ҹ�ĸ��㣬����Parent���� 
	   printf("����������ҵĹؼ��֣�\n");
	   scanf("%c",&e); getchar();
	   c=Parent(T,e);
	   if(c==NULL) printf("��������ʧ�ܣ�\n");
	   else printf("�����Ϊ��%c",c->data);
	   getchar();getchar();
	   break;
	   case 19:getchar();     //�������������ļ�������BiTreeSave���� 
	   char filename[100];
	   printf("input file name: ");
	   scanf("%s",filename);
	   if(BiTreeSave(T,filename)==OK) printf("�����������ļ��ɹ���\n"); 
	   else printf("�����������ļ�ʧ�ܣ�\n");
	   getchar();getchar();
	   break;
	   case 0:
	   break;
	   }//end of switch
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	return 0;
}//end of main() 

