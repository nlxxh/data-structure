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
	int adjvex;     //����ָ����ڽӶ�������
	struct ArcNode *nextarc;     //ָ����һ������ָ��
}ArcNode,*Arcnode;//����� 
typedef struct VNode{
	VertexType data;     //��ͷ���Ĺؼ���
	ArcNode *firstarc;     //��ͷ���ָ���һ������ָ��
	int index;     //��ͷ��������ֵ
}VNode,AdjList[MAX_VERTEX_NUM];//ͷ��� 
typedef struct{
	AdjList vertices;     //��ͷ���(ͼ�Ķ���)����
	int vexnum,arcnum;     //�������ͻ���
}ALGraph;//ͼ
int vexnum,arcnum;
Status CreateGraph(ALGraph &G,char *V,int *a){
	Arcnode p,q;int i;
	G.arcnum=arcnum;     //��ͼ�Ļ�����ֵ 
	G.vexnum=vexnum;     //��ͼ�Ķ�������ֵ 
	if(G.vexnum<=0||G.arcnum<=0) return ERROR;
	printf("���붥������ݣ�");
	for(i=0;i<vexnum;i++)
	{scanf("%d",&G.vertices[i].index);G.vertices[i].data=V[i];G.vertices[i].firstarc=NULL;
	}
	for(i=0;i<G.arcnum;i++){
	   	p=(Arcnode)malloc(sizeof(ArcNode));     //���������±�Ϊa[i]�Ļ����
	   	p->adjvex=a[i+arcnum];     //Ϊ�����ڽӶ������Ÿ�ֵ����Ϊa[i]��a[i+arcnum]Ϊһ����
	   	p->nextarc=G.vertices[a[i]].firstarc;     //�󴴽��Ļ�ָ���±�Ϊa[i]�Ķ����ԭ��һ����
	   	G.vertices[a[i]].firstarc=p;     //�󴴽��Ļ���ǰ���룬��Ϊ�±�Ϊa[i]�Ķ���ĵ�һ����
	   	q=(Arcnode)malloc(sizeof(ArcNode));     //���������±�Ϊa[i+arcnum]�Ļ����
	   	q->adjvex=a[i];     //Ϊ�����ڽӶ������Ÿ�ֵ����Ϊa[i]��a[i+arcnum]Ϊһ����
	   	q->nextarc=G.vertices[a[i+arcnum]].firstarc;    //�󴴽��Ļ�ָ���±�Ϊa[i+arcnum]�Ķ����ԭ��һ����
	   	G.vertices[a[i+arcnum]].firstarc=q;    //�󴴽��Ļ���ǰ���룬��Ϊ�±�Ϊa[i+arcnum]�Ķ���ĵ�һ����
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
        	free(p);     //���ٻ� 
        	p=p->nextarc;
		}
    }
    }
    G.vexnum=0;     //ͼ�Ķ�������Ϊ0 
    G.arcnum=0;     //ͼ�Ļ�����Ϊ0 
    return OK;
}
Status LocateVex(ALGraph &G,VertexType u){
	if(G.vexnum<=0||G.arcnum<0) return INFEASIABLE;     //ͼ�����ڣ����ش�����Ϣ 
	int i;
	for(i=0;i<G.vexnum;i++)
	{if(G.vertices[i].data==u) return i;     //����ͼ�йؼ��ֺ͸����ؼ�����ͬ��λ�� 
	}
	return INFEASIABLE;
}
Status PutVex (ALGraph &G,VertexType u,int value){
	int i;
	if(G.vexnum<=0||G.arcnum<0) return ERROR;     //ͼ�����ڣ����ش�����Ϣ 
	for(i=0;i<vexnum;i++)
	{
		if(G.vertices[i].data==u) {G.vertices[i].index=value;return OK;     //Ϊ�ؼ��ָ�ֵ 
		}
	}
	return ERROR;
}
Status FirstAdjVex(ALGraph &G,int u){
	if(G.vexnum<=0||G.arcnum<0||u<0||u>=G.vexnum) return INFEASIABLE;     //�ж�ͼ�Ƿ���ں�λ��ĺ�����
	else if(G.vertices[u].firstarc==NULL) return INFEASIABLE;     //�ж�λ���Ӧ�����ָ���һ������ָ���Ƿ�Ϊ��
	else return G.vertices[u].firstarc->adjvex;     //���ش�λ���Ӧ�����ָ���һ������ָ����ָ����ڽӶ������ţ�����õ�һ�ڽӵ��λ��
}
Status NextAdjVex(ALGraph G,int v,int w){
	ArcNode *p;
	if(G.vexnum<=0||G.arcnum<0||v<0||v>=G.vexnum||w<0||w>=G.vexnum) return INFEASIABLE;     //�ж�ͼ�Ƿ���ں�λ��ĺ���
    if(G.vertices[v].firstarc==NULL) return INFEASIABLE;     //v�������ڽӶ��㣬���ش�����Ϣ
	p=G.vertices[v].firstarc;
	while(p!=NULL){
		if(p->adjvex==w&&p->nextarc!=NULL) return p->nextarc->adjvex;      //�ҵ�v���ڽӶ���w������w���ڽӶ���λ��   
		p=p->nextarc;
	}
	return INFEASIABLE;
}
Status InsertVex(ALGraph &G,VNode v){
	if(G.vexnum<=0||G.arcnum<0) return ERROR;
	int i;
	for(i=0;i<G.vexnum;i++)
	if(G.vertices[i].data==v.data) return ERROR;
	G.vexnum=G.vexnum+1;     //ͼ�Ķ�������1 
	G.vertices[G.vexnum-1]=v;
	return OK;
}
Status DeleteVex(ALGraph &G,VertexType v){
	int i,j=-1;	ArcNode *p;ArcNode *q;VNode *h;
	if(G.vexnum<=0||G.arcnum<0) return ERROR;
	for(i=0;i<G.vexnum;i++)
	{if(G.vertices[i].data==v) j=i;
	}     //�ҵ�v��λ�� 
	if(j==-1) return ERROR;
	for(i=0;i<G.vexnum;i++)
	{
		if(G.vertices[i].firstarc!=NULL)
    {   p=G.vertices[i].firstarc;
    	if(p->adjvex==j) 
	    {G.vertices[i].firstarc=p->nextarc;free(p);}     //��ɾ������Ǳ�ͷ���ĵ�һ�ڽӶ��㣬�򽫴˱�ͷ���ָ���һ������ָ��ָ����һ���ڽӵĻ�
		else
		{
	    while(p!=NULL)
		{
			if(p->nextarc!=NULL&&p->nextarc->adjvex==j) { q=p->nextarc;p->nextarc=q->nextarc;free(q);
			}
			p=p->nextarc; 
		}     //��ɾ����㲻�����ڱ�ͷ���ĵ�һ�ڽӶ��㣬���������е��������ҵ���ɾ����㣬ɾ��ָ��˽��Ļ���ͬʱ�ı�ָ��ָ��
		}	
	}
	}
	for(i=0;i<G.vexnum;i++)
	{
		p=G.vertices[i].firstarc;
		while(p!=NULL){
			if(p->adjvex>j) p->adjvex=p->adjvex-1;     //ÿһ�е������У���ָ����ڽӶ���λ������ȷ���Ĵ�ɾ������λ��֮��Ľ��λ��ȫ����1
			p=p->nextarc; 
		}
	} 
	for(i=j;i<G.vexnum-1;i++)
    G.vertices[i]=G.vertices[i+1];     //ɾ������֮��ı�ͷ������� 
	G.vexnum=G.vexnum-1;     //ͼ�Ķ�������1 
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
	}     //��ɾ������֮��Ļ��� 
	G.arcnum=k/2;     //ɾ������֮�󣬸ı仡�� 
    printf("ɾ����������λ��ı�Ϊ��\n"); 
    for(i=0;i<G.vexnum;i++)
    printf("%c��%d   ",G.vertices[i].data,i);
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
	}     //�ҵ�����v��w��λ�� 
	if(j==-1||k==-1) return ERROR;
	ArcNode *h;
	if(G.vertices[j].firstarc!=NULL)
    {   h=G.vertices[j].firstarc;
        while(h!=NULL) 
		{
        	if(h->adjvex==k) return ERROR;     //v��wԭ���Ѿ����ڻ������������Ч�����ش�����Ϣ
        	h=h->nextarc;
		}
    }
	ArcNode *p,*q;
 	p=(ArcNode*)malloc(sizeof(ArcNode));     //malloc��������ռ䣬������
	p->adjvex=j;     //�ؼ���Ϊw�Ľ���ڽӹؼ���Ϊv�Ľ��
	p->nextarc=G.vertices[k].firstarc;     //�´����Ļ���Ϊ��ͷ���ĵ�һ����
	G.vertices[k].firstarc=p;	
	q=(ArcNode*)malloc(sizeof(ArcNode));
	q->adjvex=k;
	q->nextarc=G.vertices[j].firstarc;
	G.vertices[j].firstarc=q;
	G.arcnum=G.arcnum+1;     //ͼ�Ļ�����1 
	return OK;
}	
Status DeleteArc(ALGraph &G,VertexType v,VertexType w){
	if(G.vexnum<=0||G.arcnum<0) return ERROR;     //ͼ�����ڣ����ش�����Ϣ 
	int i;int k=-1;int j=-1;int m=0;
	for(i=0;i<G.vexnum;i++)
	{
		if(G.vertices[i].data==v) j=i;
		else if(G.vertices[i].data==w) k=i;
	}     //�ҵ��ؼ���λ�� 
	if(j==-1||k==-1) return ERROR;
	ArcNode *p;ArcNode *q;
	if(G.vertices[j].firstarc!=NULL)
    {   p=G.vertices[j].firstarc;
        if(p->adjvex==k) 
	    {G.vertices[j].firstarc=p->nextarc;free(p);m=m+1;}     //��ɾ�����Ľ�����Ǳ�ͷ���ĵ�һ�ڽӶ��㣬�򽫴˱�ͷ���ָ���һ������ָ��ָ����һ���ڽӵĻ�
		else
		{
	    while(p!=NULL)
		{
			if(p->nextarc!=NULL&&p->nextarc->adjvex==k) { q=p->nextarc;p->nextarc=q->nextarc;free(q);m=m+1;
			}
			p=p->nextarc; 
		}     //��ɾ�����Ľ�㲻�����ڱ�ͷ���ĵ�һ�ڽӶ��㣬���������е��������ҵ���ɾ����㣬ɾ��ָ��˽��Ļ���ͬʱ�ı�ָ��ָ��
		}
    }
    if(G.vertices[k].firstarc!=NULL)
    {   p=G.vertices[k].firstarc;
        if(p->adjvex==j) 
	    {G.vertices[k].firstarc=p->nextarc;free(p);m=m+1;}     //��ɾ�����Ľ�����Ǳ�ͷ���ĵ�һ�ڽӶ��㣬�򽫴˱�ͷ���ָ���һ������ָ��ָ����һ���ڽӵĻ�
		else
		{
	    while(p!=NULL)
		{
			if(p->nextarc!=NULL&&p->nextarc->adjvex==j) { q=p->nextarc;p->nextarc=q->nextarc;free(q);m=m+1;
			}
			p=p->nextarc; 
		}     //��ɾ�����Ľ�㲻�����ڱ�ͷ���ĵ�һ�ڽӶ��㣬���������е��������ҵ���ɾ����㣬ɾ��ָ��˽��Ļ���ͬʱ�ı�ָ��ָ��
		}
    }
    if(m==2) {G.arcnum=G.arcnum-1;return OK;}
    else return ERROR;
}
Status visit(ALGraph G,int a){
	printf("���ؼ���Ϊ��%c  �������Ϊ��%d\n",G.vertices[a].data,G.vertices[a].index);
	return OK;
}
void DFS(ALGraph G,int a,int *visited){
	visited[a]=1;     //λ��Ϊa�Ľ���ѷ���
	visit(G,a);     //����visit��������������Ϣ
	int i;
	for(i=FirstAdjVex(G,a);i>=0;i=NextAdjVex(G,a,i))
	if(visited[i]==0) DFS(G,i,visited);     //���н��δ���ʣ��ݹ����DFS������ʵ����ȱ���
}
void DFSSAVE(ALGraph G,int a,int *visited,FILE* fp){
	visited[a]=1;     //λ��Ϊa�Ľ���ѷ���
	fprintf(fp,"%c: %d\t",G.vertices[a].data,G.vertices[a].index);
	int i;
	for(i=FirstAdjVex(G,a);i>=0;i=NextAdjVex(G,a,i))
	if(visited[i]==0) DFSSAVE(G,i,visited,fp);     //���н��δ���ʣ��ݹ����DFSSAVE����
}
Status DFSTraverse(ALGraph G,Status(*visit)(ALGraph G,int a)){
	if(G.vexnum<=0||G.arcnum<0) return ERROR;	
	int visited[G.vexnum]={0};     //�������visited	
	int k;													
	for(k=0;k<G.vexnum;k++)
	{
		if(visited[k]==0)  
		DFS(G,k,visited);      //��δ���ʹ��Ľ����ú���DFS 
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
			rear=rear+1;     //βָ����ƣ�����Ԫ�س���
		    if(G.vertices[i].firstarc!=NULL)
        {   p=G.vertices[i].firstarc;
            while(p!=NULL)
        {
        	if(visited[p->adjvex]==0) 
			{
				visited[p->adjvex]=1;     //visted����ֵ��Ϊ1�������ѷ��ʴ˺Ž��
				visit(G,p->adjvex);     //����visit�����������Ϣ
				key[top++]=p->adjvex;     //�ڽӶ��������
			}
			p=p->nextarc;
		}     //��i�Ž���һ�е�������б���
	    }
	        i=key[rear];     //��һ�����ʵ�Ԫ����βָ��ָ��Ԫ��
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
	}     //�ļ������ڣ���ʾ������Ϣ 	  
	int visited[G.vexnum]={0};     //��ε��� 
	int k;
	for(k=0;k<G.vexnum;k++)
	{
		if(visited[k]==0) {DFSSAVE(G,k,visited,fp); } 
	}
	fclose(fp);
	return OK;
	
}//��ͼ�����ļ� 
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
	printf("    ��ѡ����Ĳ���[0~13]:");     //�˵� 
	scanf("%d",&op);
    switch(op){     //��switch����ʵ�ֲ˵����� 
       ALGraph G;
	   case 1:
	   int i,a[100];char b[100];
	   printf("����ͼ�Ķ�������\n");
	   scanf("%d",&vexnum);getchar();
	   printf("����ͼ�Ķ��㣺\n");
	   for(i=0;i<vexnum;i++)
	   	{scanf("%c",&b[i]);getchar();}
	   printf("����ͼ�Ļ�����\n");
	   scanf("%d",&arcnum);
	   for(i=0;i<arcnum;i++){
	    printf("���뻡�������������(��һ������Ϊ0�ţ�������˳�����)��\n");
	   	scanf("%d %d",&a[i],&a[i+arcnum]);getchar();}
	   	if(CreateGraph(G,b,a)==OK) printf("ͼ�����ɹ���\n");
	   	else printf("ͼ����ʧ�ܣ�\n");
	   	getchar();getchar();
		break;
		case 2:
		if(DestroyGraph(G)==OK) printf("����ͼ�ɹ���\n");
		else printf("����ͼʧ�ܣ�\n");
		getchar();getchar();
		break;
		case 3:
		char n;
		printf("��������ҵĽ��ؼ��֣�\n");getchar();
		scanf("%c",&n);getchar();
		if(LocateVex(G,n)>=0) printf("����λ����ϢΪ��%d\n",LocateVex(G,n));
		else printf("���ҽ���λ����Ϣʧ�ܣ�\n");
		getchar();getchar();
		break;
		case 4:
		char u;int value; 
		printf("����Ҫ��ֵ�Ľ��ؼ��֣�");getchar();
		scanf("%c",&u);getchar();
		printf("���������ݣ�");
		scanf("%d",&value);getchar();
		if(PutVex (G,u,value)==OK) printf("��ֵ�ɹ���\n");
		else printf("��ֵʧ�ܣ�\n");
		getchar();getchar();
		break;
		case 5:
		int k;
		printf("����Ҫ���ҵĽ��λ��");getchar();
		scanf("%d",&k);getchar();
		if(FirstAdjVex(G, k)>=0) printf("�˶���ĵ�һ���ڽӶ����λ��Ϊ��%d\n",FirstAdjVex(G, k));
		else printf("������Ч��\n");
		getchar();getchar();
		break;
		case 6:
		int v,w;
		printf("����ͼ��ĳ������(v)λ��");
		scanf("%d",&v);getchar();
		printf("����˶�����ڽӶ���(w)λ��");
		scanf("%d",&w);getchar(); 
		if(NextAdjVex(G, v, w)>=0) printf("v�ģ������w����һ���ڽӶ����λ��Ϊ��%d",NextAdjVex(G, v, w));
		else printf("������Ч��\n");
		getchar();getchar();
		break;
		case 7:
		VNode s;
		printf("�����¶���Ĺؼ��֣�");getchar();
		scanf("%c",&s.data);getchar();
		printf("�����¶�������ݣ�");
		scanf("%d",&s.index);getchar(); 
		s.firstarc=NULL; 
		if(InsertVex(G,s)==OK) printf("�¶������ɹ�!\n");
		else printf("�¶������ʧ��!\n");
		getchar();getchar();
		break;
		case 8:
		printf("����Ҫɾ���Ľ��ؼ��֣�");getchar();
		scanf("%c",&u);getchar();
		if(DeleteVex(G,u)==OK) printf("ɾ�����ɹ���\n");
		else printf("ɾ�����ʧ�ܣ�\n");
		getchar();getchar();
		break;
		case 9:
		char e,f;
		printf("����ͼ��ĳ������ؼ��֣�");getchar();
		scanf("%c",&e);getchar();
		printf("����ͼ����һ������ؼ��֣�");
		scanf("%c",&f);getchar(); 
		if(InsertArc(G,e,f)==OK) printf("���ӻ��ɹ���\n");
		else  printf("���ӻ�ʧ�ܣ�\n");
		getchar();getchar();
		break;
		case 10:
		printf("����ͼ��ĳ������ؼ��֣�");getchar();
		scanf("%c",&e);getchar();
		printf("����ͼ����һ������ؼ��֣�");
		scanf("%c",&f);getchar(); 
		if(DeleteArc(G,e,f)==OK) printf("ɾ�����ɹ���\n");
		else  printf("ɾ����ʧ�ܣ�\n");
		getchar();getchar();
		break;
		case 11:
	    if(DFSTraverse(G,visit)==OK) printf("����������������ɹ���\n");
		else  printf("���������������ʧ�ܣ�\n");
		getchar();getchar();
		break;
		case 12:
	    if(BFSTraverse(G,visit)==OK) printf("����������������ɹ���\n");
		else  printf("���������������ʧ�ܣ�\n");
		getchar();getchar();
		break;
		case 13:getchar();     
	    char filename[100];
	    printf("input file name: ");
	    scanf("%s",filename);
	    if(GraphSave(G,filename)==OK) printf("ͼ�����ļ��ɹ���\n"); 
	    else printf("ͼ�����ļ�ʧ�ܣ�\n");
	    getchar();getchar();
	    break;
		case 0:
		break;
	 }//end of switch
	}//end of while
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
	return 0;
}//end of main() 

	  
	   
