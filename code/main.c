
#include <stdio.h>
#include <unistd.h>
#include "lcd.h"		// 引用lcd显示屏的功能模块的头文件
#include "bmp.h"		// 引用bmp图片显示的功能模块的头文件
#include "touch.h"		// 引用触摸屏的功能模块的头文件
#include "DoublyLinkedList.h"
#include "word.h"		// 字符显示

#include "album.h"
#include "2048.h"

int main( int argc, char * argv[] )
{
	//1.初始化屏幕
	int re = lcd_init();
	if( re == -1 )
	{
		return -1;
	}
	
	
	//2.操作
		//在屏幕上 显示一张纯色的图像
		//show_a_color( 0xFFC1C1 );
		// show_a_color( 0xFFFFFF );		//白色
		
		//矩形
		// display_Rectangle( 50, 50, 200, 100, 0xFFFF00 );
		// display_Rectangle( 700, 400, 100, 100, 0x0000FF );
	
		//圆形
		// display_Circle( 500, 300, 300, 0xFF0000 );
		// display_Circle( 500, 300, 250, 0xFF8000 );
		// display_Circle( 500, 300, 200, 0xFFFF00 );
		// display_Circle( 500, 300, 150, 0x00FF00 );
		// display_Circle( 500, 300, 100, 0x00FFFF );
		// display_Circle( 500, 300,  50, 0x0000FF );
		// display_Circle( 500, 300,  20, 0xFF00FF );
		
		//五角星
		// display_pentastar( 300, 300, 200, 0xFFFF00 );
	
		
		//显示bmp图片
		//show_bmp( 0, 0, "kk.bmp" );
		//show_bmp( 0, 0, argv[1] );
		//sleep(1 );		//延时1s
		
		// show_bmp( 200, 200, argv[2] );
		// sleep( 5 );		//延时5s
	
	
		//循环播放多张图片 
		//Auto_show_bmp();
		
		
		//触摸屏
		/*
		int x = 0, y = 0;
		while(1)
		{
		
			//获取点击的坐标
			get_touch( &x, &y );
			
			//退出按钮
			if( x >= 900 && y <=100 )
			{
				break;
			}
		}
		
			
		while( 1 )
		{
			//获取滑动的方向
			int fx = get_direction();
			
			switch( fx )
			{
				case UP :    printf("UP\n"); break;
				case DOWN :  printf("DOWN\n"); break;
				case LEFT :  printf("LEFT\n"); break;
				case RIGHT : printf("RIGHT\n"); break;
			}
		}
		
		*/
		
		/*
			//创建一个双向链表
			DList * list = create_list();
			//搜索指定目录下的所有的bmp图片
			get_bmp_name( argv[1] , list );
			print_list( list );
		*/
		
		//电子相册
		// my_Album( argv[1] );
	
		
		//2048游戏
		my_2048game();
		
		
		//显示字符
		//show_word( 300, 100, 40, 46, xu, 0xFF0000 );
		
		//show_number( 300, 200, 1234567, 0x00FF00 );

	
	
	//3.关闭屏幕
	lcd_close();
}
