
#ifndef  __WORD_H__
#define  __WORD_H__


extern unsigned char xu[46][40/8];



void show_word( int x0, int y0, int w, int h, unsigned char word[][w/8], int color );

void show_number( int x0, int y0, int num, int color );

#endif
