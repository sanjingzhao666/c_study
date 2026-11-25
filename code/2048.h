
#ifndef  __2048_H__
#define  __2048_H__


typedef struct Point
{
	int x;
	int y;
} Point ;


int my_2048game();


//刷新游戏界面
void refresh();

//在随机的位置上，生成随机的2或4
void position();


#endif

