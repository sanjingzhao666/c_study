
#include "2048.h"
#include "bmp.h"
#include "touch.h"

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>


//保存游戏的数据
int game[4][4] = { 0 };

int score = 0;			//实时游戏得分
int MAX_SCORE = 0;		//最高分
int LEVEL = 2048;		//游戏难以程度


//2048游戏
int my_2048game()
{
	//设置时间种子
	srand( time(NULL) );
	
	//刷新游戏界面
	refresh();
	
	sleep(2);
	
	//在随机的位置上，生成随机的2或4
	position();
	position();
	
	
	
}


//刷新游戏界面
void refresh()
{
	int i,j;
	for( i=0; i<4; i++ )
	{
		for( j=0; j<4; j++ )
		{
			printf("%d\t", game[i][j] );
			
			//合成图片的名字 0.bmp / 2.bmp / 4.bmp 
			char buf[32] = {0};
			snprintf( buf, 32, "%d%s", game[i][j], ".bmp" );
			
			//显示 
			show_bmp( j*150, i*150, buf );
		}
		putchar('\n');
	}
	putchar('\n');
	
	//实时得分 和 最高分 
	//...
}


//在随机的位置上，生成随机的2或4
void position()
{
	Point  empty[16];
	int num = 0;
	
	//1.遍历4x4界面，收集所有的空白位置
	int i,j;
	for( i=0; i<4; i++ )
	{
		for( j=0; j<4; j++ )
		{
			if( game[i][j] == 0 )
			{
				empty[num].x = i;
				empty[num].y = j;
				num++;
			}
		}
	}
	
	//没有空白位置，直接退出
	if( num == 0 )
	{
		refresh();
		return ;
	}

	//2.生成随机数
	int rand_value = rand()%2 ? 4 : 2;
	
	//3.生成随机的位置
	int idx = rand() % num;
	i = empty[idx].x;
	j = empty[idx].y;
	
	game[i][j] = rand_value;

	//4.刷新游戏界面
	refresh();
}



