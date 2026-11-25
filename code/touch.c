
#include "touch.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <linux/input.h>
#include <stdlib.h>

//获取触摸屏点击的坐标
int get_touch( int * x, int * y )
{
	//1.打开触摸屏
	int fd = open( "/dev/input/event6", O_RDWR );
	if( fd == -1 )
	{
		perror("open event6 error  ");
		return -1;
	}
	
	//2.读取输入事件的信息
	struct input_event  ev;		//保存输入事件的信息
	int x0 = -1;
	int y0 = -1;
	
	while(1)
	{
		//读取
		read( fd, &ev, sizeof(ev) );
		
		//解析
		if( ev.type == EV_ABS )	//触摸事件
		{
			if( ev.code == ABS_X )	//x轴
			{
				x0 = ev.value;
			}
			else if( ev.code == ABS_Y ) //y轴
			{
				y0 = ev.value;
			}
			else if( ev.code == ABS_PRESSURE && ev.value == 0 )	
			{
				//触摸屏压力事件，且压力值为0，表示手指松开了
				if( x0 != -1 && y0 != -1 )
				{
					break;
				}
			}
		}
		else if( ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0 )	
		{
			//按键事件，且手指松开
			if( x0 != -1 && y0 != -1 )
			{
				break;
			}
		}
	}
	
	*x = x0;
	*y = y0;
	
	printf("( %d , %d )\n", *x, *y );
	
	//3.关闭屏幕
	close( fd );
}



//获取手指滑动的方向：上1 下2 左3 右4	
int get_direction()
{
	//1.打开触摸屏
	int fd = open( "/dev/input/event6", O_RDWR );
	if( fd == -1 )
	{
		perror("open event6 error  ");
		return -1;
	}
	
	//2.获取触摸的坐标
	struct input_event  ev;		//保存输入事件的信息
	int x0 = -1, y0 = -1;		//起点坐标
	int x1 = -1, y1 = -1;		//终点坐标
	
	while(1)
	{
		//读取
		read( fd, &ev, sizeof(ev) );
	
		//解析
		if( ev.type == EV_ABS )			//触摸事件
		{
			if( ev.code == ABS_X )		// x轴
			{
				if( x0 == -1 )
				{
					x0 = ev.value;
				}
				x1 = ev.value;
			}
			if( ev.code == ABS_Y )		// y轴
			{
				if( y0 == -1 )
				{
					y0 = ev.value;
				}
				y1 = ev.value;
			}
			else if( ev.code == ABS_PRESSURE && ev.value == 0 )	
			{
				//触摸屏压力事件，且压力值为0，表示手指松开了
				if( x0 != -1 && y0 != -1 )
				{
					break;
				}
			}
		}
		else if( ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0 )	
		{
			//按键事件，且手指松开
			if( x0 != -1 && y0 != -1 )
			{
				break;
			}
		}
	}
	
	//3.关闭触摸屏
	close( fd );
	
	printf("( %d , %d ) ---> ( %d , %d )\n", x0, y0, x1, y1 );
	
	//设置 退出按钮
	if( x0 >= 900 && y0 < 100 )
	{
		printf("exit ! \n");
		return 0;
	}
	
	//4.判断滑动的方向
	int xx = abs( x0 - x1 );
	int yy = abs( y0 - y1 );
	
	if( xx > yy )	//水平方向
	{
		if( x0 > x1 )
		{
			return LEFT;		//左滑
		}
		else
		{
			return RIGHT;		//右滑
		}
	}
	else		//垂直方向
	{
		if( y0 > y1 )
		{
			return UP;			//上滑
		}
		else
		{
			return DOWN;		//下滑
		}
	}
}

