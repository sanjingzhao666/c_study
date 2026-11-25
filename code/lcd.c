
#include "lcd.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>

int fd = -1;			//屏幕的文件描述符
int * plcd = NULL;		//指向帧缓冲的首地址

//初始化屏幕
int lcd_init()
{
	//1.打开屏幕文件 "/dev/fb0"
	fd = open( "/dev/fb0", O_RDWR );
	if( fd == -1 )
	{
		perror("open lcd error ");
		return -1;
	}
	
	//2.内存映射
	plcd = mmap( NULL, 1024*600*4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );
	if( plcd == MAP_FAILED )
	{
		perror("mmap error ");
		close( fd );
		return -1;
	}
}

//关闭屏幕
void lcd_close()
{
	//1.解除映射
	munmap( plcd, 1024*600*4 );
	
	//2.关闭屏幕文件
	close( fd );
}

//画点：在屏幕上任意的一个点(x,y)显示一个颜色color
void display_point( int x, int y, int color )
{
	if( x>=0 && x<1024 && y>=0 && y<600 )
	{
		*( plcd + y*1024 + x ) = color;
	}
}

//在屏幕上 显示一张纯色的图像
void show_a_color( int color )
{
	int x,y;
	for( y=0; y<600; y++ )
	{
		for( x=0; x<1024; x++ )
		{
			//画点
			display_point( x, y, color );
		}
	}
}


//矩形
void display_Rectangle( int x0, int y0, int w, int h, int color )
{
	int i,j;
	for( j=0; j<600; j++ )
	{
		for( i=0; i<1024; i++ )
		{
			//矩形
			if( i>=x0 && i<x0+w && j>=y0 && j<y0+h )
			{
				//画点
				display_point( i, j, color );
			}
		}
	}
}


//圆形
void display_Circle( int x0, int y0, int r, int color )
{
	int i,j;
	for( j=0; j<600; j++ )
	{
		for( i=0; i<1024; i++ )
		{
			//圆形
			if( (i-x0)*(i-x0) + (j-y0)*(j-y0) <= r*r )
			{
				//画点
				display_point( i, j, color );
			}
		}
	}
}


/*
	display_pentastar ：画正五角星
		sin18 = 0.31 , cos18 = 0.95
		sin36 = 0.59 , cos36 = 0.81

		已知两点，求其直线方程：(x-x1)/(x2-x1) = (y-y1)/(y2-y1)
					变形 得 ==》(x-x1)*(y2-y1)/(x2-x1)+y1 = y
	
*/
void display_pentastar( int x0, int y0,int r,int color)
{
	int x,y;

	//根据中心点坐标，得出每个顶点的坐标
	int x1 = x0 , y1=y0-r;
	int x2 = x0-0.95*r , y2=y0-0.31*r;//x0-cos18*r , y0-sin18*r
	int x3 = x0+0.95*r , y3=y0-0.31*r;//x0+cos18*r , y0-sin18*r
	int x4 = x0-0.59*r , y4=y0+0.81*r;//x0-sin36*r , y0+cos36*r
	int x5 = x0+0.59*r , y5=y0+0.81*r;//x0+sin36*r , y0+cos36*r

	printf("(%d , %d) (%d , %d) (%d , %d) (%d , %d) (%d , %d)\n",x1,y1,x2,y2,x3,y3,x4,y4,x5,y5);

	int flag = 0;//重叠标志
	
	for(x=x0-r;x<x0+r;x++)
	{
		for(y=y0-r;y<y0+r;y++)
		{
			flag = 0;
			if((x-x1)*(y4-y1)/(x4-x1)+y1 <= y)
			{
				flag++;
			}
			if((x-x1)*(y5-y1)/(x5-x1)+y1 <= y)
			{
				flag++;
			}
			if(y >= y2)//x2,x3
			{
				flag++;
			}
			if((x-x2)*(y5-y2)/(x5-x2)+y2 >= y)
			{
				flag++;
			}
			if((x-x3)*(y4-y3)/(x4-x3)+y3 >= y)
			{
				flag++;
			}
			
			if( flag >= 4 )//重叠4和5次 是五角星的部分
			{
				display_point(x,y,color);
			}
		}
	}
}
