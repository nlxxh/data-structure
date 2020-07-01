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
#define MAX_VERTEX_NUM 20
using namespace std;
typedef char VertexType;
typedef int Status;
typedef struct ArcNode{
	int adjvex;     //弧所指向的邻接顶点的序号
	struct ArcNode *nextarc;     //指向下一个弧的指针
}ArcNode,*Arcnode;//弧结点 
typedef struct VNode{
	VertexType data;     //表头结点的关键字
	ArcNode *firstarc;     //表头结点指向第一条弧的指针
	int index;     //表头结点的数据值
}VNode,AdjList[MAX_VERTEX_NUM];//头结点 
typedef struct{
	AdjList vertices;     //表头结点(图的顶点)数组
	int vexnum,arcnum;     //顶点数和弧数
}ALGraph;//图
int vexnum,arcnum;
Status CreateGraph(ALGraph &G,char *V,int *a){
	Arcnode p,q;int i;
	G.arcnum=arcnum;     //给图的弧数赋值 
	G.vexnum=vexnum;     //给图的顶点数赋值 
	if(G.vexnum<=0||G.arcnum<=0) return ERROR;
	printf("输入顶点的数据：");
	for(i=0;i<vexnum;i++)
	{scanf("%d",&G.vertices[i].index);G.vertices[i].data=V[i];G.vertices[i].firstarc=NULL;
	}
	for(i=0;i<G.arcnum;i++){
	   	p=(Arcnode)malloc(sizeof(ArcNode));     //创建顶点下标为a[i]的弧结点
	   	p->adjvex=a[i+arcnum];     //为弧的邻接顶点的序号赋值，因为a[i]和a[i+arcnum]为一条弧
	   	p->nextarc=G.vertices[a[i]].firstarc;     //后创建的弧指向下标为a[i]的顶点的原第一条弧
	   	G.vertices[a[i]].firstarc=p;     //后创建的弧向前插入，作为下标为a[i]的顶点的第一条弧
	   	q=(Arcnode)malloc(sizeof(ArcNode));     //创建顶点下标为a[i+arcnum]的弧结点
	   	q->adjvex=a[i];     //为弧的邻接顶点的序号赋值，因为a[i]和a[i+arcnum]为一条弧
	   	q->nextarc=G.vertices[a[i+arcnum]].firstarc;    //后创建的弧指向下标为a[i+arcnum]的顶点的原第一条弧
	   	G.vertices[a[i+arcnum]].firstarc=q;    //后创建的弧向前插入，作为下标为a[i+arcnum]的顶点的第一条弧
	   }
	   return OK;
}
Status DestroyGraph(ALGraph &G){
	int i;
	ArcNode *p;
	for(i=0;i<G.vexnum;i++)
	{
		if(G.vertices[i].firstarc!=NULL)
    {   p=G.vertices[i].firstarc;
        while(p!=NULL)
        {
        	free(p);     //销毁弧 
        	p=p->nextarc;
		}
    }
    }
    G.vexnum=0;     //图的顶点数置为0 
    G.arcnum=0;     //图的弧数置为0 
    return OK;
}
Status LocateVex(ALGraph &G,VertexType u){
	if(G.vexnum<=0||G.arcnum<0) return INFEASIABLE;     //图不存在，返回错误信息 
	int i;
	for(i=0;i<G.vexnum;i++)
	{if(G.vertices[i].data==u) return i;     //返回图中关键字和给定关键字相同的位序 
	}
	return INFEASIABLE;
}
Status PutVex (ALGraph &G,VertexType u,int value){
	int i;
	if(G.vexnum<=0||G.arcnum<0) return ERROR;     //图不存在，返回错误信息 
	for(i=0;i<vexnum;i++)
	{
		if(G.vertices[i].data==u) {G.vertices[i].index=value;return OK;     //为关键字赋值 
		}
	}
	return ERROR;
}
Status FirstAdjVex(ALGraph &G,int u){
	if(G.vexnum<=0||G.arcnum<0||u<0||u>=G.vexnum) return INFEASIABLE;     //判断图是否存在和位序的合理性
	else if(G.vertices[u].firstarc==NULL) return INFEASIABLE;     //判断位序对应顶点的指向第一条弧的指针是否为空
	else return G.vertices[u].firstarc->adjvex;     //返回此位序对应顶点的指向第一条弧的指针所指向的邻接顶点的序号，即获得第一邻接点的位序
}
Status NextAdjVex(ALGraph G,int v,int w){
	ArcNode *p;
	if(G.vexnum<=0||G.arcnum<0||v<0||v>=G.vexnum||w<0||w>=G.vexnum) return INFEASIABLE;     //判断图是否存在和位序的合理
    if(G.vertices[v].firstarc==NULL) return INFEASIABLE;     //v不存在邻接顶点，返回错误信息
	p=G.vertices[v].firstarc;
	while(p!=NULL){
		if(p->adjvex==w&&p->nextarc!=NULL) return p->nextarc->adjvex;      //找到v的邻接顶点w，返回w的邻接顶点位序   
		p=p->nextarc;
	}
	return INFEASIABLE;
}
Status InsertVex(ALGraph &G,VNode v){
	if(G.vexnum<=0||G.arcnum<0) return ERROR;
	int i;
	for(i=0;i<G.vexnum;i++)
	if(G.vertices[i].data==v.data) return ERROR;
	G.vexnum=G.vexnum+1;     //图的顶点数加1 
	G.vertices[G.vexnum-1]=v;
	return OK;
}
Status DeleteVex(ALGraph &G,VertexType v){
	int i,j=-1;	ArcNode *p;ArcNode *q;VNode *h;
	if(G.vexnum<=0||G.arcnum<0) return ERROR;
	for(i=0;i<G.vexnum;i++)
	{if(G.vertices[i].data==v) j=i;
	}     //找到v的位序 
	if(j==-1) return ERROR;
	for(i=0;i<G.vexnum;i++)
	{
		if(G.vertices[i].firstarc!=NULL)
    {   p=G.vertices[i].firstarc;
    	if(p->adjvex==j) 
	    {G.vertices[i].firstarc=p->nextarc;free(p);}     //待删除结点是表头结点的第一邻接顶点，则将此表头结点指向第一条弧的指针指向下一条邻接的弧
		else
		{
	    while(p!=NULL)
		{
			if(p->nextarc!=NULL&&p->nextarc->adjvex==j) { q=p->nextarc;p->nextarc=q->nextarc;free(q);
			}
			p=p->nextarc; 
		}     //待删除结点不是所在表头结点的第一邻接顶点，则先在这行单链表中找到待删除结点，删掉指向此结点的弧，同时改变指针指向
		}	
	}
	}
	for(i=0;i<G.vexnum;i++)
	{
		p=G.vertices[i].firstarc;
		while(p!=NULL){
			if(p->adjvex>j) p->adjvex=p->adjvex-1;     //每一行单链表中，弧指向的邻接顶点位序在已确定的待删除结点的位序之后的结点位序全部减1
			p=p->nextarc; 
		}
	} 
	for(i=j;i<G.vexnum-1;i++)
    G.vertices[i]=G.vertices[i+1];     //删除顶点之后的表头结点数组 
	G.vexnum=G.vexnum-1;     //图的顶点数减1 
	int k=0;
	for(i=0;i<G.vexnum;i++)
	{
		if(G.vertices[i].firstarc!=NULL)
    {   p=G.vertices[i].firstarc;
        while(p!=NULL)
		{
        	k=k+1;
        	p=p->nextarc;
		}
    }
	}     //求删除顶点之后的弧数 
	G.arcnum=k/2;     //删除顶点之后，改变弧数 
    printf("删除结点后各结点位序改变为：\n"); 
    for(i=0;i<G.vexnum;i++)
    printf("%c：%d   ",G.vertices[i].data,i);
    printf("\n");
    return OK;
	}
Status InsertArc(ALGraph &G,VertexType v,VertexType w){
	if(G.vexnum<=0||G.arcnum<0) return ERROR;
	int i;int k=-1;int j=-1;
	for(i=0;i<G.vexnum;i++)
	{
		if(G.vertices[i].data==v) j=i;
		else if(G.vertices[i].data==w) k=i;
	}     //找到顶点v和w的位序 
	if(j==-1||k==-1) return ERROR;
	ArcNode *h;
	if(G.vertices[j].firstarc!=NULL)
    {   h=G.vertices[j].firstarc;
        while(h!=NULL) 
		{
        	if(h->adjvex==k) return ERROR;     //v和w原来已经存在弧，插入操作无效，返回错误信息
        	h=h->nextarc;
		}
    }
	ArcNode *p,*q;
 	p=(ArcNode*)malloc(sizeof(ArcNode));     //malloc函数分配空间，创建弧
	p->adjvex=j;     //关键字为w的结点邻接关键字为v的结点
	p->nextarc=G.vertices[k].firstarc;     //新创建的弧作为表头结点的第一条弧
	G.vertices[k].firstarc=p;	
	q=(ArcNode*)malloc(sizeof(ArcNode));
	q->adjvex=k;
	q->nextarc=G.vertices[j].firstarc;
	G.vertices[j].firstarc=q;
	G.arcnum=G.arcnum+1;     //图的弧数加1 
	return OK;
}	
Status DeleteArc(ALGraph &G,VertexType v,VertexType w){
	if(G.vexnum<=0||G.arcnum<0) return ERROR;     //图不存在，返回错误信息 
	int i;int k=-1;int j=-1;int m=0;
	for(i=0;i<G.vexnum;i++)
	{
		if(G.vertices[i].data==v) j=i;
		else if(G.vertices[i].data==w) k=i;
	}     //找到关键字位序 
	if(j==-1||k==-1) return ERROR;
	ArcNode *p;ArcNode *q;
	if(G.vertices[j].firstarc!=NULL)
    {   p=G.vertices[j].firstarc;
        if(p->adjvex==k) 
	    {G.vertices[j].firstarc=p->nextarc;free(p);m=m+1;}     //待删除弧的结点结点是表头结点的第一邻接顶点，则将此表头结点指向第一条弧的指针指向下一条邻接的弧
		else
		{
	    while(p!=NULL)
		{
			if(p->nextarc!=NULL&&p->nextarc->adjvex==k) { q=p->nextarc;p->nextarc=q->nextarc;free(q);m=m+1;
			}
			p=p->nextarc; 
		}     //待删除弧的结点不是所在表头结点的第一邻接顶点，则先在这行单链表中找到待删除结点，删掉指向此结点的弧，同时改变指针指向
		}
    }
    if(G.vertices[k].firstarc!=NULL)
    {   p=G.vertices[k].firstarc;
        if(p->adjvex==j) 
	    {G.vertices[k].firstarc=p->nextarc;free(p);m=m+1;}     //待删除弧的结点结点是表头结点的第一邻接顶点，则将此表头结点指向第一条弧的指针指向下一条邻接的弧
		else
		{
	    while(p!=NULL)
		{
			if(p->nextarc!=NULL&&p->nextarc->adjvex==j) { q=p->nextarc;p->nextarc=q->nextarc;free(q);m=m+1;
			}
			p=p->nextarc; 
		}     //待删除弧的结点不是所在表头结点的第一邻接顶点，则先在这行单链表中找到待删除结点，删掉指向此结点的弧，同时改变指针指向
		}
    }
    if(m==2) {G.arcnum=G.arcnum-1;return OK;}
    else return ERROR;
}
Status visit(ALGraph G,int a){
	printf("结点关键字为：%c  结点数据为：%d\n",G.vertices[a].data,G.vertices[a].index);
	return OK;
}
void DFS(ALGraph G,int a,int *visited){
	visited[a]=1;     //位序为a的结点已访问
	visit(G,a);     //调用visit函数，输出结点信息
	int i;
	for(i=FirstAdjVex(G,a);i>=0;i=NextAdjVex(G,a,i))
	if(visited[i]==0) DFS(G,i,visited);     //若有结点未访问，递归调用DFS函数，实现深度遍历
}
void DFSSAVE(ALGraph G,int a,int *visited,FILE* fp){
	visited[a]=1;     //位序为a的结点已访问
	fprintf(fp,"%c: %d\t",G.vertices[a].data,G.vertices[a].index);
	int i;
	for(i=FirstAdjVex(G,a);i>=0;i=NextAdjVex(G,a,i))
	if(visited[i]==0) DFSSAVE(G,i,visited,fp);     //若有结点未访问，递归调用DFSSAVE函数
}
Status DFSTraverse(ALGraph G,Status(*visit)(ALGraph G,int a)){
	if(G.vexnum<=0||G.arcnum<0) return ERROR;	
	int visited[G.vexnum]={0};     //标记数组visited	
	int k;													
	for(k=0;k<G.vexnum;k++)
	{
		if(visited[k]==0)  
		DFS(G,k,visited);      //对未访问过的结点调用函数DFS 
	}
	return OK;
}
Status BFSTraverse(ALGraph G,Status(*visit)(ALGraph G,int a)){
	if(G.vexnum<=0||G.arcnum<0) return ERROR;	
	int i;ArcNode *p;
	int key[100]={-1};
	int top=0;int rear=0;
	int visited[G.vexnum]={0};  
	for(i=0;i<G.vexnum;i++)
	{
		if(visited[i]==0) 
		{
			visited[i]=1;
			visit(G,i);
			key[top++]=i;
		}
		while(top!=rear)
		{
			rear=rear+1;     //尾指针后移，代表元素出队
		    if(G.vertices[i].firstarc!=NULL)
        {   p=G.vertices[i].firstarc;
            while(p!=NULL)
        {
        	if(visited[p->adjvex]==0) 
			{
				visited[p->adjvex]=1;     //visted数组值设为1，代表已访问此号结点
				visit(G,p->adjvex);     //调用visit函数，输出信息
				key[top++]=p->adjvex;     //邻接顶点入队列
			}
			p=p->nextarc;
		}     //对i号结点的一行单链表进行遍历
	    }
	        i=key[rear];     //下一个访问的元素是尾指针指向元素
        }
        
	}
	return OK;
}
Status GraphSave(ALGraph G,char *filename){
	FILE  *fp; 
	if ((fp=fopen(filename,"wb"))==NULL)
	{
	printf("File open error\n ");
	return ERROR;
	}     //文件不存在，显示错误信息 	  
	int visited[G.vexnum]={0};     //多次调用 
	int k;
	for(k=0;k<G.vexnum;k++)
	{
		if(visited[k]==0) {DFSSAVE(G,k,visited,fp); } 
	}
	fclose(fp);
	return OK;
	
}//将图存入文件 
int main(void){
	int op=1;
	while(op){
	system("cls");	printf("\n\n");
	printf("      Menu for Graph On chain Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. CreateGraph         7. InsertVex\n");
	printf("    	  2. DestroyGraph        8. DeleteVex\n");
	printf("    	  3. LocateVex           9. InsertArc \n");
	printf("    	  4. PutVex             10. DeleteArc\n");
	printf("    	  5. FirstAdjVex        11. DFSTraverse\n");
	printf("    	  6. NextAdjVex         12. BFSTraverse \n");
	printf("         13. GraphSave           0. exit \n");
	printf("-------------------------------------------------\n");
	printf("    请选择你的操作[0~13]:");     //菜单 
	scanf("%d",&op);
    switch(op){     //用switch函数实现菜单功能 
       ALGraph G;
	   case 1:
	   int i,a[100];char b[100];
	   printf("输入图的顶点数：\n");
	   scanf("%d",&vexnum);getchar();
	   printf("输入图的顶点：\n");
	   for(i=0;i<vexnum;i++)
	   	{scanf("%c",&b[i]);getchar();}
	   printf("输入图的弧数：\n");
	   scanf("%d",&arcnum);
	   for(i=0;i<arcnum;i++){
	    printf("输入弧的两个顶点序号(第一个顶点为0号，按输入顺序递增)：\n");
	   	scanf("%d %d",&a[i],&a[i+arcnum]);getchar();}
	   	if(CreateGraph(G,b,a)==OK) printf("图创建成功！\n");
	   	else printf("图创建失败！\n");
	   	getchar();getchar();
		break;
		case 2:
		if(DestroyGraph(G)==OK) printf("销毁图成功！\n");
		else printf("销毁图失败！\n");
		getchar();getchar();
		break;
		case 3:
		char n;
		printf("输入待查找的结点关键字：\n");getchar();
		scanf("%c",&n);getchar();
		if(LocateVex(G,n)>=0) printf("结点的位置信息为：%d\n",LocateVex(G,n));
		else printf("查找结点的位置信息失败！\n");
		getchar();getchar();
		break;
		case 4:
		char u;int value; 
		printf("输入要赋值的结点关键字：");getchar();
		scanf("%c",&u);getchar();
		printf("输入结点数据：");
		scanf("%d",&value);getchar();
		if(PutVex (G,u,value)==OK) printf("赋值成功！\n");
		else printf("赋值失败！\n");
		getchar();getchar();
		break;
		case 5:
		int k;
		printf("输入要查找的结点位序：");getchar();
		scanf("%d",&k);getchar();
		if(FirstAdjVex(G, k)>=0) printf("此顶点的第一个邻接顶点的位置为：%d\n",FirstAdjVex(G, k));
		else printf("操作无效！\n");
		getchar();getchar();
		break;
		case 6:
		int v,w;
		printf("输入图的某个顶点(v)位序：");
		scanf("%d",&v);getchar();
		printf("输入此顶点的邻接顶点(w)位序：");
		scanf("%d",&w);getchar(); 
		if(NextAdjVex(G, v, w)>=0) printf("v的（相对于w）下一个邻接顶点的位置为：%d",NextAdjVex(G, v, w));
		else printf("操作无效！\n");
		getchar();getchar();
		break;
		case 7:
		VNode s;
		printf("输入新顶点的关键字：");getchar();
		scanf("%c",&s.data);getchar();
		printf("输入新顶点的数据：");
		scanf("%d",&s.index);getchar(); 
		s.firstarc=NULL; 
		if(InsertVex(G,s)==OK) printf("新顶点插入成功!\n");
		else printf("新顶点插入失败!\n");
		getchar();getchar();
		break;
		case 8:
		printf("输入要删除的结点关键字：");getchar();
		scanf("%c",&u);getchar();
		if(DeleteVex(G,u)==OK) printf("删除结点成功！\n");
		else printf("删除结点失败！\n");
		getchar();getchar();
		break;
		case 9:
		char e,f;
		printf("输入图的某个顶点关键字：");getchar();
		scanf("%c",&e);getchar();
		printf("输入图的另一个顶点关键字：");
		scanf("%c",&f);getchar(); 
		if(InsertArc(G,e,f)==OK) printf("增加弧成功！\n");
		else  printf("增加弧失败！\n");
		getchar();getchar();
		break;
		case 10:
		printf("输入图的某个顶点关键字：");getchar();
		scanf("%c",&e);getchar();
		printf("输入图的另一个顶点关键字：");
		scanf("%c",&f);getchar(); 
		if(DeleteArc(G,e,f)==OK) printf("删除弧成功！\n");
		else  printf("删除弧失败！\n");
		getchar();getchar();
		break;
		case 11:
	    if(DFSTraverse(G,visit)==OK) printf("深度优先搜索遍历成功！\n");
		else  printf("深度优先搜索遍历失败！\n");
		getchar();getchar();
		break;
		case 12:
	    if(BFSTraverse(G,visit)==OK) printf("广度优先搜索遍历成功！\n");
		else  printf("广度优先搜索遍历失败！\n");
		getchar();getchar();
		break;
		case 13:getchar();     
	    char filename[100];
	    printf("input file name: ");
	    scanf("%s",filename);
	    if(GraphSave(G,filename)==OK) printf("图存入文件成功！\n"); 
	    else printf("图存入文件失败！\n");
	    getchar();getchar();
	    break;
		case 0:
		break;
	 }//end of switch
	}//end of while
	printf("欢迎下次再使用本系统！\n");
	return 0;
}//end of main() 

	  
	   
