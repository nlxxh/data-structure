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
	TElemType data;     //结点关键字 
	struct BiTNode *lchild,*rchild;     //左右孩子指针 
	int index;     //结点数据 
}BiTNode,*BiTree;

BiTree Find(BiTree T, char key) {
	BiTree T1;
	if (T == NULL) return NULL;     //二叉树为空，返回空指针
	if (T->data == key) return T;     //找到目标关键字，返回指针 
	else {
		T1 = Find(T->lchild, key);     //递归查找左子树
		if (T1 != NULL) return T1;
		T1 = Find(T->rchild, key);      //递归查找右子树
		if (T1 != NULL) return T1;
	}
	return NULL;     //未找到目标关键字，返回空指针
}//定义Find函数，定位关键字 
BiTree QZBiTree(char *a,char *b,int *c,int *d,int size){
	if(size==0) return NULL;     //序列长度为0，返回空指针 
	int i;int r=-1;
	for(i=0;i<size;i++)
	if(b[i]==a[0]) {r=i;break;}     //在中序序列中找到根节点的位置 
	BiTree T=(BiTNode*)malloc(sizeof(BiTNode));
	T->data=b[r];
	T->index=d[r];
	T->lchild=QZBiTree(a+1,b,c+1,d,r);     //递归创建左子树 
	T->rchild=QZBiTree(a+r+1,b+r+1,c+r+1,d+r+1,size-r-1);     //递归创建右子树 	
	return T;	
}//定义前序+中序创建二叉树函数，供CreateBiTree调用 
BiTree HZBiTree(char *a,char *b,int *c,int *d,int size){
	if(size==0) return NULL;     //序列长度为0，返回空指针 
	int i;int r=-1;
	for(i=0;i<size;i++)
	if(b[i]==a[size-1]) {r=i;break;}     //在中序序列中找到根节点的位置 
	BiTree T=(BiTNode*)malloc(sizeof(BiTNode));
	T->data=b[r];
	T->index=d[r];
	T->lchild=HZBiTree(a,b,c,d,r);     //递归创建左子树 
	T->rchild=HZBiTree(a+r,b+r+1,c+r,d+r+1,size-r-1);     //递归创建右子树 		
	return T;	
}//后序+中序创建二叉树，供CreateBiTree调用  
Status CreateBiTree(BiTree &T,int definition){
	TElemType ch;
	if(definition==1) {     //definition值为1，输入前序序列创建二叉树 
	printf("请输入结点关键字：\n");
	scanf("%c", &ch);
	getchar();
	if (ch == '#') T = NULL;     //'#'代表指针为空 
	else {
		if (!(T = (BiTNode*)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
		T->data = ch;
		printf("请输入结点数据：\n");
		scanf("%d", &T->index);
		getchar();
		CreateBiTree(T->lchild,definition);     //递归创建左子树  
		CreateBiTree(T->rchild,definition);     //递归创建右子树 	
	}return OK;
}     //前序创建二叉树  
	else if(definition==2){     //definition值为2，输入前序+中序序列创建二叉树 
	char a[100],b[100];int c[100];int d[100];int size,i;
	printf("输入序列长度：\n");
	scanf("%d",&size);      
	if(size<0) printf("序列长度不合法！\n");     //序列长度小于0，不合法
	else if(size==0) {printf("二叉树为空！\n");T=NULL;     //序列长度为0，二叉树为空
	}
	else{
	printf("输入前序序列关键字：\n");
	scanf("%s",a);
	printf("输入前序序列数据：\n");
	for(i=0;i<size;i++)
	scanf("%d",&c[i]);
	printf("输入中序序列关键字：\n");
	scanf("%s",b);
	printf("输入中序序列数据：\n");
	for(i=0;i<size;i++)
	scanf("%d",&d[i]);
	if(T=QZBiTree(a,b,c,d,size)) printf("前序+中序构建二叉树成功！\n");     //调用QZBiTree函数 
	else printf("前序+中序构建二叉树失败！\n"); 
}}     //前序+中序创建二叉树 
	else{     //definition值为3，输入后序+中序序列创建二叉树 
	char a[100],b[100];int c[100];int d[100];int size,i;
	printf("输入序列长度：\n");
	scanf("%d",&size);
	if(size<0) printf("序列长度不合法！\n");     //序列长度小于0，不合法
	else if(size==0) {printf("二叉树为空！\n");T=NULL;     //序列长度为0，二叉树为空
	}
	else{
	printf("输入后序序列关键字：\n");
	scanf("%s",a);
	printf("输入后序序列数据：\n");
	for(i=0;i<size;i++)
	scanf("%d",&c[i]);
	printf("输入中序序列关键字：\n");
	scanf("%s",b);
	printf("输入中序序列数据：\n");
	for(i=0;i<size;i++)
	scanf("%d",&d[i]);
	if(T=HZBiTree(a,b,c,d,size)) printf("后序+中序构建二叉树成功！\n");     //调用HZBiTree函数 
	else printf("后序+中序构建二叉树失败！\n");	
	}}//中序+后序创建二叉树 
}     
Status DestroyBiTree(BiTree &T){
	if(T==NULL) return ERROR;     //二叉树不存在，销毁失败 
	else{
		if (T->lchild)
			DestroyBiTree(T->lchild);     //递归销毁左子树 
		if (T->rchild)
			DestroyBiTree(T->rchild);     //递归销毁右子树 
		free(T);
		T = NULL;
	}
	return OK;
}//销毁二叉树 
Status ClearBiTree(BiTree &T){
	if(T==NULL) return ERROR; 
	else{
		T->lchild = NULL;     //清空左子树 
		T->rchild = NULL;     //清空右子树 
		T = NULL;
	}
	return OK;
}//清空二叉树
Status BiTreeEmpty(BiTree T) {
	if (T) return FALSE;
	return TRUE;
}//判定空二叉树 
int MAX(int a, int b) {
	if (a >= b) return a;
	else return b;
}//定义MAX函数，供BiTreeDepth调用 
Status BiTreeDepth(BiTree T) {
	if (!T) return 0;     //二叉树为空，深度返回为0
	else {
		if ((T->lchild == NULL) && (T->rchild == NULL)) return 1;      //二叉树只有一个结点，深度返回为1 
		else return 1+MAX(BiTreeDepth(T->lchild), BiTreeDepth(T->rchild));     //二叉树深度为左右子树深度的最大值 
	}
}//求二叉树深度 
Status LocateNode(BiTree T,TElemType e){
	if(T==NULL) return ERROR;     //二叉树不存在，返回错误信息  
	BiTree p =T;
    p=Find(T,e);     //调用Find函数，返回关键字的指针 
    if(p==NULL) return ERROR;     //未找到关键字，返回错误信息 
    printf("查找成功！结点的数据为：%d",p->index);
	return OK;
}//查找结点 
Status Assign(BiTree &T,TElemType e,int value){
	if(T==NULL) return ERROR;     //二叉树不存在，赋值失败 
    BiTree p;
    p=Find(T,e);     //调用Find函数，返回关键字的指针 
    if(p==NULL) return ERROR;     //未找到关键字，赋值失败 
    p->index=value;     //结点赋值 
	printf("赋值成功！\n");
}//结点赋值 
Status LeftSibling(BiTree T,TElemType e){
    BiTree s[100];     //定义指针栈，并假设二叉树的深度不超过100 
    int top=0;     //置空栈，top为栈顶元素上一个单元的地址 
    BiTree p =T;
    while (top || p)
    {
        if (p)     
        {
            s[top++]=p;     //根指针进栈 
            if(p->rchild!=NULL&&p->rchild->data==e) {printf("查找成功！结点的左兄弟的关键字为：%c",p->lchild->data);break;return OK;
			}     //查找左兄弟结点 
			p = p->lchild;     //移向左子树 
        }     //遍历以栈顶元素的指向为根结点的二叉树的左子树 
        else
        {
            p = s[--top];     //弹出根指针
           if(p->rchild!=NULL&&p->rchild->data==e) {printf("查找成功！结点的左兄弟的关键字为：%c",p->lchild->data);break;return OK;
			}     //查找左兄弟结点  
            p = p->rchild;     //移向右子树 
        }
    }
    if(!top) return ERROR;
}//获得左兄弟结点 
Status RightSibling(BiTree T,TElemType e){
    BiTree s[100];     //定义指针栈，并假设二叉树的深度不超过100 
    int top=0;     //置空栈，top为栈顶元素上一个单元的地址 
    BiTree p =T;
    while (top || p)
    {
        if (p)
        {
            s[top++]=p;     //根指针进栈 
            if(p->lchild!=NULL&&p->lchild->data==e) {printf("查找成功！结点的右兄弟的关键字为：%c",p->rchild->data);break;return OK;
			}     //查找右兄弟结点  
			p = p->lchild;     //移向左子树 
        }     //遍历以栈顶元素的指向为根结点的二叉树的左子树 
        else
        {
            p = s[--top];     //弹出根指针
           if(p->lchild!=NULL&&p->lchild->data==e) {printf("查找成功！结点的右兄弟的关键字为：%c",p->rchild->data);break;return OK;
			}     //查找右兄弟结点   
            p = p->rchild;     //移向右子树 
        }
    }
    if(!top) return ERROR;
}//获得右兄弟结点
Status InsertNode(BiTree &T,TElemType e,int LR,BiTree &c){
	c=(BiTNode*)malloc(sizeof(BiTNode));     //创建待插入结点 
	printf("请输入待插入结点的关键字：\n");
	scanf("%c",&c->data);
	printf("请输入待插入结点的数据：\n");
	scanf("%d",&c->index);
	c->rchild=NULL;c->lchild=NULL;
	BiTree q;
	q=Find(T,e);     //调用Find函数，找到树中待插入位置的结点 
	if(q==NULL) return ERROR;      //未找到待插入位置的结点 ，返回错误信息 
    else if(LR==0) {     //LR为0的情况 
    	if(q->lchild!=NULL) c->rchild=q->lchild;     //结点e的原有左子树为结点c的右子树  
		q->lchild=c;     //插入结点c作为关键字为e的结点的左孩子结点 
    	return OK;
	}
	else if(LR==1) {     //LR为1的情况 
		if(q->rchild!=NULL) c->rchild=q->rchild;     //结点e的原有右子树为结点c的右子树  
		q->rchild=c;     //插入结点c作为关键字为e的结点的右孩子结点 
    	return OK;
	}
	else return ERROR;
}//插入结点 
Status DeleteNode(BiTree &T,TElemType e){
	if(T==NULL) return ERROR;     //二叉树不存在，删除失败  
	BiTree s[100];     //定义指针栈，并假设二叉树的深度不超过100 
    int top=0;     //置空栈，top为栈顶元素上一个单元的地址 
    BiTree p =T;BiTree q,h,j,g;int k=0;
    if(T->data==e) k=3;     //删除结点为根节点，k改为3 
	else{
    while (top || p)
    {
        if (p)
        {
            s[top++]=p;     //根指针进栈 
            if(p->rchild!=NULL&&p->rchild->data==e) {k=1;q=p;break;return OK;
			}     //删除结点为q的右孩子，k改为1 
            else if (p->lchild!=NULL&&p->lchild->data==e) {k=2;q=p;break;return OK;
			}     //删除结点为q的左孩子，k改为2  
			p = p->lchild;     //移向左子树 
        }
        else
        {
            p = s[--top];     //弹出根指针
           if(p->rchild!=NULL&&p->rchild->data==e) {k=1;q=p;break;return OK;
			}      //删除结点为q的右孩子，k改为1 
            else if(p->lchild!=NULL&&p->lchild->data==e) {k=2;q=p;break;return OK;
			}     //删除结点为q的左孩子，k改为2  
            p = p->rchild;     //移向右子树 
        }
    }
    if(!top) return ERROR;
}
    if(k==1){     //k为1，删除结点为q的右孩子的情况 
    	h=q->rchild;     
		if(h->rchild==NULL&&h->lchild==NULL) {free(h);q->rchild=NULL;
		}     //删除结点关键字的度为0，直接删除
		else if(h->rchild!=NULL&&h->lchild!=NULL) {j=h->lchild;g=h->rchild;free(h);q->rchild=j;
		while(j->rchild!=NULL) j=j->rchild;j->rchild=g;
		}     //删除结点关键字的度为2，用e的左孩子代替被删除的e位置，e的右子树作为e的左子树中最右结点的右子树
		else if(h->rchild==NULL&&h->lchild!=NULL){j=h->lchild;free(h);q->rchild=j;
		}     //删除结点关键字的度为1，只有左孩子，用关键字为e的结点孩子代替被删除的e位置 
		else{j=h->rchild;free(h);q->rchild=j;
		}     //删除结点关键字的度为1，只有右孩子，用关键字为e的结点孩子代替被删除的e位置 
	}
	else if(k==2){     //k为2，删除结点为q的左孩子的情况 
		h=q->lchild;
		if(h->rchild==NULL&&h->lchild==NULL) {free(h);q->lchild=NULL;
		}     //删除结点关键字的度为0，直接删除
		else if(h->rchild!=NULL&&h->lchild!=NULL) {j=h->lchild;g=h->rchild;free(h);q->lchild=j;
		while(j->rchild!=NULL) j=j->rchild;j->rchild=g;
		}     //删除结点关键字的度为2，用e的左孩子代替被删除的e位置，e的右子树作为e的左子树中最右结点的右子树
		else if(h->rchild==NULL&&h->lchild!=NULL){j=h->lchild;free(h);q->lchild=j;
		}     //删除结点关键字的度为1，只有左孩子，用关键字为e的结点孩子代替被删除的e位置 
		else{j=h->rchild;free(h);q->lchild=j;
		}     //删除结点关键字的度为1，只有右孩子，用关键字为e的结点孩子代替被删除的e位置 
	}
	else if(k==3){     //k为3，删除结点为根节点的情况 
		if(T->rchild==NULL&&T->lchild==NULL) {free(T);T=NULL;
		}     //删除结点关键字的度为0，直接删除
		else if(T->rchild!=NULL&&T->lchild!=NULL){j=T->lchild;g=T->rchild;free(T);T=j;
		while(j->rchild!=NULL) j=j->rchild;j->rchild=g;
		}     //删除结点关键字的度为2，用e的左孩子代替被删除的e位置，e的右子树作为e的左子树中最右结点的右子树
		else if(T->rchild==NULL&&T->lchild!=NULL){j=T->lchild;free(T);T=j;
		}     //删除结点关键字的度为1，只有左孩子，用关键字为e的结点孩子代替被删除的e位置 
		else{j=T->rchild;free(T);T=j;
		}     //删除结点关键字的度为1，只有右孩子，用关键字为e的结点孩子代替被删除的e位置 
	}
	return OK;
	}//删除结点 
Status Visit(BiTNode a){
	printf("结点关键字为：%c  结点数据为：%d\n",a.data,a.index);
	return OK;
}//定义Visit函数，供遍历函数调用 
Status PreOrderTraverse(BiTree &T,Status(*Visit)(BiTNode)){
	if(T){if(Visit(*T))     //调用Visit函数 
	if(PreOrderTraverse(T->lchild,Visit))     //递归前序遍历左子树 
	if(PreOrderTraverse(T->rchild,Visit)) return OK;     //递归前序遍历右子树 
	return ERROR;
	}else return OK;
}//前序遍历 
Status InOrderTraverse(BiTree T,Status(*Visit)(BiTNode)){
    BiTree s[100];     //定义指针栈，并假设二叉树的深度不超过100 
    int top=0;     //置空栈，top为栈顶元素上一个单元的地址 
    BiTree p =T;
    while (top || p)
    {
        if (p)
        {
            s[top++]=p;     //根指针进栈 
            p = p->lchild;     //移向左子树 
        }
        else
        {
            p = s[--top];     //弹出根指针 
            if(!Visit(*p)) return ERROR;     //调用Visit函数 
            p = p->rchild;     //移向右子树 
        }
    }
    return OK;
}//中序遍历 
Status PostOrderTraverse(BiTree &T,Status(*Visit)(BiTNode)){
	if(T){if(PostOrderTraverse(T->lchild,Visit))     //递归后序遍历左子树 
	if(PostOrderTraverse(T->rchild,Visit))     //递归后序遍历右子树  
	if(Visit(*T)) return OK;     //调用Visit函数 
	return ERROR;
	}else return OK;
}//后序遍历 
Status LevelOrderTraverse(BiTree &T,Status(*Visit)(BiTNode)){
    BiTree s[100];     //定义指针栈，并假设二叉树的深度不超过100 
    int top=0;     //置空栈，top为栈顶元素上一个单元的地址 
	int rear=0;     //rear为栈底元素的地址 
    BiTree p=T;
	if(p!=NULL) s[top++]=p;     //根指针进栈 
	while(top!=rear){
		if(!Visit(*(s[rear]))) return ERROR;     //调用Visit函数 
		if(p->lchild!=NULL) {s[top++]=p->lchild;
		}     //左孩子先进栈 
		if(p->rchild!=NULL) {s[top++]=p->rchild;
		}     //右孩子后进栈 
        rear++;     //栈底指针上移 
		p=s[rear];
	}

    return OK;
}//层序遍历 
Status LeftChild(BiTree T,TElemType e){
	BiTree p;
	p=Find(T,e);     //调用Find函数，找到关键字为e的结点 
	if(p==NULL||p->lchild==NULL||T==NULL) return ERROR;     //二叉树不存在，或关键字为e的结点未找到或不存在左孩子，输出错误信息 
	else printf("查找成功，结点左孩子的关键字为：%c",p->lchild->data);
}//获得左孩子结点 
Status RightChild(BiTree T,TElemType e){
	BiTree p;
	p=Find(T,e);     //调用Find函数，找到关键字为e的结点 
	if(p==NULL||p->rchild==NULL||T==NULL) return ERROR;     //二叉树不存在，或关键字为e的结点未找到或不存在右孩子，输出错误信息 
	else printf("查找成功，结点右孩子的关键字为：%c",p->rchild->data);
}//获得右孩子结点 
BiTree Parent(BiTree T,TElemType e){
	BiTree T1;
	if(T){
	if((T->lchild!=NULL&&T->lchild->data==e)||(T->rchild!=NULL&&T->rchild->data==e)) return T;     
	T1=Parent(T->lchild,e);     //递归获得左子树的父母结点 
	if(T1!=NULL) return T1;
	T1=Parent(T->rchild,e);     //递归获得右子树的父母结点 
	if(T1!=NULL) return T1;
	}
	return NULL;
}//获得父母结点 
Status BiTreeSave(BiTree T,char *filename){
	FILE  *fp; 
	if ((fp=fopen(filename,"wb"))==NULL)
	{
	printf("File open error\n ");
	return ERROR;
	}     //文件不存在，显示错误信息 	  
	BiTree s[100];     //定义指针栈，并假设二叉树的深度不超过100 
    int top=0;     //置空栈，top为栈顶元素上一个单元的地址 
    BiTree p =T;
    while (top || p)
    {
        if (p)
        {
            s[top++]=p;     //根指针进栈 
			fprintf(fp,"%c: %d\t",p->data,p->index);     //将二叉树中的结点关键字和数据存入文件 
			p = p->lchild;     //移向左子树 
			
        }
        else
        {
            p = s[--top];     //弹出根指针 
            p = p->rchild;     //移向右子树 
        }
    }
	fclose(fp);
	return OK;
}//将二叉树存入文件 
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
	printf("    请选择你的操作[0~19]:");     //菜单 
	scanf("%d",&op);
    switch(op){     //用switch函数实现菜单功能 
	   case 1:getchar();     //创建二叉树，调用CreateBiTree函数   
	   printf("输入defintion值(1：前序(单个输入)2：前序+中序3：后序+中序):\n");
	   int n;
	   scanf("%d",&n); getchar(); 
	   if(CreateBiTree(T,n)==OK) printf("前序构建二叉树成功！\n");
	   getchar();getchar();
	   break;
	   case 2:getchar();     //销毁二叉树，调用DestroyBiTree函数 
	   if(DestroyBiTree(T)==ERROR) printf("二叉树销毁失败！\n");
	   else printf("二叉树销毁成功！\n"); 
	   getchar();getchar();
	   break;
	   case 3:getchar();     //清空二叉树，调用ClearBiTree函数 
	   if(ClearBiTree(T)==ERROR) printf("二叉树清空失败！\n");
	   else printf("二叉树清空成功！\n"); 
	   getchar();getchar();
	   break;
	   case 4:getchar();     //判定空树，调用BiTreeEmpty函数 
	   if (BiTreeEmpty(T) == FALSE) printf("二叉树不为空！\n");
	   else printf("二叉树为空！\n");
	   getchar(); getchar(); 
	   break;
	   case 5:getchar();     //求二叉树深度，调用BiTreeDepth函数 
	   int a; 
	   a = BiTreeDepth(T);
	   if (BiTreeDepth(T)>0) printf("二叉树的深度为：%d\n", a);
	   else printf("求二叉树的深度失败！\n"); 
	   getchar(); getchar(); 
	   break;
	   case 6:getchar();     //查找结点，调用LocateNode函数 
	   char e;
	   printf("请输入待查找的关键字：\n");
	   scanf("%c",&e); getchar(); 
	   if(LocateNode(T,e)==ERROR) printf("NULL\n");
	   getchar();getchar();
	   break;
	   case 7:getchar();     //赋值，调用Assign函数 
	   printf("请输入待赋值的关键字：\n");
	   scanf("%c",&e); getchar(); 
	   int value;
	   printf("请输入数据：\n");
	   scanf("%d",&value); getchar(); 
	   if(Assign(T,e,value)==ERROR) printf("赋值失败！\n");
	   getchar();getchar();
	   break;
	   case 8:getchar();     //获得左兄弟结点，调用LeftSibling函数 
	   printf("请输入待查找的关键字：\n");
	   scanf("%c",&e); getchar(); 
	   if(LeftSibling(T,e)==ERROR) printf("NULL\n");
	   getchar();getchar();
	   break;
	   case 9:getchar();     //获得右兄弟结点，调用LeftSibling函数  
	   printf("请输入待查找的关键字：\n");
	   scanf("%c",&e); getchar(); 
	   if(RightSibling(T,e)==ERROR) printf("NULL\n");
	   getchar();getchar();
	   break;
	   case 10:getchar();      //插入节点，调用InsertNode函数 
	   int LR;
	   printf("请输入待插入的方向(0或1)，0表示左边，1表示右边：\n");
	   scanf("%d",&LR); getchar(); 
	   printf("请输入待插入位置结点的关键字：\n");
	   scanf("%c",&e); getchar();
	   BiTree c;
	   if(InsertNode(T,e,LR,c)==ERROR) printf("插入失败！\n");
	   else printf("插入成功！\n");
	   getchar();getchar();
	   break;
	   case 11:getchar();     //删除结点，调用DeleteNode函数 
	   printf("请输入待删除的关键字：\n");
	   scanf("%c",&e); getchar(); 
	   if(DeleteNode(T,e)==ERROR) printf("删除失败！\n");
	   else printf("删除成功！\n");
	   getchar();getchar();
	   break;
	   case 12:getchar();     //前序遍历，调用PreOrderTraverse函数 
	   if(PreOrderTraverse(T,Visit)==OK) printf("二叉树前序遍历成功！\n");
	   else printf("二叉树前序遍历失败！\n"); 
	   getchar();getchar();
	   break;	
	   case 13:getchar();     //中序遍历，调用InOrderTraverse函数 
	   if(InOrderTraverse(T,Visit)==OK) printf("二叉树中序遍历成功！\n");
	   else printf("二叉树中序遍历失败！\n"); 
	   getchar();getchar();
	   break;
	   case 14:getchar();     //后序遍历，调用PostOrderTraverse函数 
	   if(PostOrderTraverse(T,Visit)==OK) printf("二叉树后序遍历成功！\n");
	   else printf("二叉树后序遍历失败！\n"); 
	   getchar();getchar();
	   break;
	   case 15:getchar();     //层序遍历，调用LevelOrderTraverse函数 
	   if(LevelOrderTraverse(T,Visit)==OK) printf("二叉树层序遍历成功！\n");
	   else printf("二叉树层序遍历失败！\n"); 
	   getchar();getchar();
	   break;
	   case 16:getchar();     //查找左孩子，调用LeftChild函数 
	   printf("请输入待查找的关键字：\n");
	   scanf("%c",&e); getchar(); 
	   if(LeftChild(T,e)==ERROR) printf("左孩子查找失败！\n");
	   getchar();getchar();
	   break;
	   case 17:getchar();     //查找右孩子，调用RightChild函数 
	   printf("请输入待查找的关键字：\n");
	   scanf("%c",&e); getchar(); 
	   if(RightChild(T,e)==ERROR) printf("右孩子查找失败！\n");
	   getchar();getchar();
	   break;
	   case 18:getchar();     //查找父母结点，调用Parent函数 
	   printf("请输入待查找的关键字：\n");
	   scanf("%c",&e); getchar();
	   c=Parent(T,e);
	   if(c==NULL) printf("父结点查找失败！\n");
	   else printf("父结点为：%c",c->data);
	   getchar();getchar();
	   break;
	   case 19:getchar();     //将二叉树存入文件，调用BiTreeSave函数 
	   char filename[100];
	   printf("input file name: ");
	   scanf("%s",filename);
	   if(BiTreeSave(T,filename)==OK) printf("二叉树存入文件成功！\n"); 
	   else printf("二叉树存入文件失败！\n");
	   getchar();getchar();
	   break;
	   case 0:
	   break;
	   }//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
	return 0;
}//end of main() 

