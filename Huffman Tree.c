#include<stdio.h>
#include<stdlib.h>
typedef struct Link{
	int w;//权重
	char data;//权重对应的数据
	struct Link *next;
	struct Link *left;
	struct Link *right;
}Link;
Link* InitLink(){//初始化
	Link* link=(Link*)malloc(sizeof(Link));
	link->next=NULL;
	link->left=link->right=NULL;
	return link;
}
void InsertLink(Link *link,Link* node){//从小到大插入元素
	Link *p=link;
	Link *q=p->next;
	while(q&&node->w>q->w){
		p=q;
		q=q->next;
	}
	node->next=q;
	p->next=node;
}
Link *DelLink(Link *link,int place){//删除place处节点并返回
	Link *p,*s;
	int i=0;
	p=link;
	while(i<place-1&&p->next!=NULL){
		i++;
		p=p->next;
	}
	s=p->next;
	p->next=s->next;
	return s;
}
Link *CreateHuffman(Link *link,int n){//n是元素个数
	Link *del1,*del2,*p;
	Link *node;
	int w_sum,i;
	p=link;
	for(i=0;i<n-1;i++){
		del1=DelLink(p,1);
		del2=DelLink(p,1);
		w_sum=del1->w+del2->w;
		node=(Link*)malloc(sizeof(Link));
		node->left==del1;
		node->right=del2;
		node->w=w_sum;
		InsertLink(link,node);
	}
	return node;//关键在于把取最小、删除、插入融为一体
}
void GetCode(Link *tree,int len){//在主函数里调用是直接len=0从顶开始调
	if(!tree) return;
	static int a[20];//即使是递归也可以互相传
	int i=0;//len是层数
	if(!tree->left&&!tree->right){
		printf("%c Huffman code：",tree->data);
		for(int i=0;i<len;i++) printf("%d",a[i]);
		printf("\n");
	}else{
		a[len]=0;
		GetCode(tree->left,len+1);
		a[len]=1;
		GetCode(tree->right,len+1);//由上到下一层层分左右递归
	}
}