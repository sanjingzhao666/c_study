
#include "bmp.h"
#include "lcd.h"
#include "touch.h"

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


//显示bmp图片
int show_bmp( int x0, int y0, char * filename )
{
    //1.打开图片
    int fd = open( filename, O_RDWR );
    if( fd == -1 )
    {
        perror("open bmp error ");
        return -1;
    }

    //2.获取图片的信息
    //2.1获取 宽度、高度、色深
    int width = 0;
    lseek( fd, 0x12, SEEK_SET );
    read( fd, &width, 4 );

    int height = 0;
    lseek( fd, 0x16, SEEK_SET );
    read( fd, &height, 4 );

    short depth = 0;
    lseek( fd, 0x1C, SEEK_SET );
    read( fd, &depth, 2 );

    //2.2获取像素点数据
    // 计算每一行可能会填充的字节数
    int line_size = 0;		//实际的字节数
    int fill_size = 0;		//填充的字节数

    fill_size = 4 - ( abs(width) * (depth/8) ) % 4;
    if( fill_size == 4 )
    {
    	fill_size = 0;
    }

    // printf("w = %d, h = %d, d = %hd, fill = %d\n", width, height, depth, fill_size );

    //保存一行实际的字节数 = 有效字节数 + 填充字节数
    line_size = abs(width) * (depth/8)  + fill_size;


    //一次性把整个图片的像素点数据 全部读取出来 ( bgr / bgra )
    unsigned char buf[ abs(height)*line_size ];
    // 指针 unsigned char * buf = (unsigned char *)malloc( abs(height)*line_size );
    lseek( fd, 0x36, SEEK_SET );
    read( fd, buf, abs(height)*line_size );

    //3.显示 
    int i, j;
	int color = 0;
	unsigned char a,r,g,b;
	int num = 0;
	
	for( j=0; j<abs(height); j++ )
	{
		for( i=0; i<abs(width); i++ )
		{
			//先合成颜色值
			b = buf[num++];
			g = buf[num++];
			r = buf[num++];
			if( depth == 32 )
			{
				a = buf[num++];
			}
			else 
			{
				a = 0;
			}
			color = (a<<24) | (r<<16) | (g<<8) | b;
			
			//画点 
			int x = width>0 ? i : abs(width)-i-1 ;
            int y = height>0 ? abs(height)-j-1 : j ;
			display_point( x+x0, y+y0, color );
		}
		num = num + fill_size;		//跳过填充的无效数据
	}

    //4.关闭图片
	close( fd );
}


//保存bmp图片的名字
char * bmp[5] = { "1.bmp", "2.bmp", "3.bmp", "4.bmp", "5.bmp"  };

//循环播放多张图片 
void Auto_show_bmp()
{
	int i = 0;
	while( 1 )
	{
		//显示bmp图片
		show_bmp( 0, 0, bmp[i] );
		sleep( 2 );	//延时2s
		
		i = (i+1)%5;
	}
}

