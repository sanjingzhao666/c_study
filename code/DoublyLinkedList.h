
#ifndef  __DOUBLYLINKEDLIST_H__
#define  __DOUBLYLINKEDLIST_H__


typedef  char  ElemType;			//数据元素中的数据的类型

//双向链表的 数据节点
typedef struct node			
{
	ElemType  data[128];		// 数据域 ---> 保存数据
	struct node	* next;			// 指针域 ---> 保存逻辑上的下一个
	struct node	* prev;			//		 ---> 保存逻辑上的前一个
} DNode ;

//双向链表的 头结点
typedef struct List
{
	DNode * first;			// 指向双向链表的第一个节点
	DNode * last;			// 指向双向链表的最后一个节点
	int  num;				// 保存双向链表中的节点个数
} DList ;


DList * create_list();
void print_list( DList * list );
DList * insert_node( DList * list, DNode * pnew );
void destroy_list( DList * list );

#endif
