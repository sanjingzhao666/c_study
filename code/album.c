
#include "album.h" 
#include "bmp.h"
#include "touch.h"

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>




//通过手指的滑动来进行切换图片
int my_Album( char * path )
{
	//创建一个双向链表
	DList * list = create_list();
	
	//搜索指定目录下的所有的bmp图片
	get_bmp_name( path, list );
	
	//首尾相连 ---> 循环链表
	if( list->num != 0 )
	{
		list->last->next = list->first;
		list->first->prev = list->last;
	}
	
	DNode * p = list->first;	//遍历指针
	
	while( 1 )	//遍历 
	{
		printf("bmp : %s\n", p->data );
	
		//显示图片
		show_bmp( 0, 0, p->data );
		
		//通过滑动进行切换
		int fx = get_direction();
		
		if( fx == LEFT || fx == UP )
		{
			//下一张
			p = p->next;
		}
		else if( fx == RIGHT || fx == DOWN )
		{
			//上一张
			p = p->prev;
		}
		else if( fx == 0 )
		{
			break;	//退出按钮
		}
	}
	
	//销毁链表
	list->last->next = NULL;
	destroy_list( list );
}



//搜索指定目录下的所有的bmp图片，保存到一个双向链表中
int get_bmp_name( char * path, DList * list )
{
	//1.打开目录 
	DIR * dir = opendir( path );
	if( dir == NULL )
	{
		perror("open dir error ");
		return -1;
	}
	
	//2.读取目录
	struct dirent * d;
	while( d = readdir( dir ) )
	{
		//3.过滤 . 和 .. 目录
		if( strcmp( d->d_name, ".") == 0 || strcmp( d->d_name, "..") == 0 )
		{
			continue;
		}
		
		//4.合成路径名	"路径/名字"
		char pathname[128] = {0};
		strcpy( pathname, path );			//路径
		if( pathname[ strlen(pathname) - 1 ] != '/' )
		{
			pathname[ strlen(pathname) ] = '/';		// "/"
		}
		strcat( pathname, d->d_name );		// 文件名
		
		
		if( d->d_type == DT_REG )	//5.普通文件
		{
			//判断后缀名是否为 .bmp 
			if( strcmp( pathname+(strlen(pathname)-4), ".bmp" ) == 0 )
			{
				//把图片的名字添加进链表（先创建数据节点，再添加）
				DNode * pnew = (DNode *)malloc( sizeof(DNode) );
				strcpy( pnew->data, pathname );
				pnew->next = NULL;
				pnew->prev = NULL;
				
				insert_node( list, pnew );
			}
		}
		else if( d->d_type == DT_DIR )	//6.子目录
		{
			//继续打开去搜索 ---> 递归
			get_bmp_name( pathname, list );
		}
	}
	
	//7.关闭目录
	closedir( dir );
}



