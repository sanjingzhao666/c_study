
#include "DoublyLinkedList.h"
#include <stdio.h>
#include <stdlib.h>



//创建一个带头结点的双向链表
DList * create_list()
{
	//1.创建一个头结点，并初始化
	DList * list = (DList *)malloc( sizeof(DList) );
	list->first = NULL;
	list->last = NULL;
	list->num = 0;
	
	//2.将新链表返回
	return list;
}


//打印链表
void print_list( DList * list )
{
	if( list == NULL )
	{
		return ;
	}
	
	DNode * p = list->first;		//遍历指针
	
	int n = list->num;
	while( n-- )
	{
		printf("%s\n", p->data );
		p = p->next;
	}
	putchar('\n');
	
	printf("num = %d\n", list->num );
}



//往一个链表中的添加一个新的数据节点
DList * insert_node( DList * list, DNode * pnew )
{
	if( list == NULL )
	{
		return NULL;
	}
	
	if( list->first == NULL )	//从无到有
	{
		list->first = pnew;
		list->last = pnew;
	}
	else		//从少到多
	{
		//尾插
		list->last->next = pnew;
		pnew->prev = list->last;
		list->last = pnew;
	}
	
	//元素个数+1
	list->num++;
	
	return list;
}



//销毁链表
void destroy_list( DList * list )
{
	if( list == NULL )
	{
		return ;
	}

	//1.遍历 先释放每一个数据节点（一直去删除第一个节点）
	DNode * p = list->first;		//遍历指针
	
	int n = list->num;
	while( n-- )
	{
		//一直去 删除第一个节点
		list->first = list->first->next;
		p->next = NULL;					//工程规范
		if( list->first != NULL )
		{
			list->first->prev = NULL;	//工程规范
		}
		free( p );
		
		p = list->first;
	}
	
	//2.最后再释放头结点
	list->first = NULL;
	list->last = NULL;
	list->num = 0;
	free( list );
}

