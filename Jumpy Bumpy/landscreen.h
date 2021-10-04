#ifndef LANDING
#include "iGraphics.h"
#include "bitmap_loader.h"
#include "stb_image.h"
#include "glaux.h"
#include "glut.h"

int nam_x, nam_y;
int st_x, st_y;
int op_x, op_y;
int sc_x, sc_y;
int hp_x, hp_y;
int pm_x, pm_y;
int e_x, e_y;



void l_screen_size()
{
	nam_x=0, nam_y=400;
	st_x=600 , st_y=210;
	op_x=600 , op_y=160;
	sc_x=600 , sc_y=110;
	hp_x=600 , hp_y=60;
	e_x =600, e_y=50;
}
void l_screen(int mx, int my)
{
	l_screen_size();
	iShowBMP(0, 0, "Landing_Screen(bg).bmp");
	iShowBMP2(nam_x, nam_y, "1.Name.bmp", 0);
	iShowBMP2(st_x, st_y, "1.Start_S.bmp",0);
	iShowBMP2(op_x, op_y, "1.Option_S.bmp", 0);
	iShowBMP2(sc_x, sc_y, "1.Score_S.bmp", 0);
	iShowBMP2(hp_x, hp_y, "1.Help_S.bmp", 0);
	iShowBMP2(e_x, e_y, "1.Exit.bmp", 0);
	if(nam_x<=90 && nam_y>=230)
		{
			nam_x+=2;
			nam_y-=5;
		}
	else if(nam_y>=80 && st_x>=230)st_x-=10;
	else if(st_x>=220 && op_x>=230)op_x-=10;
	else if(op_x>=220 && sc_x>=230)sc_x-=10;
	else if(sc_x>=220 && hp_x>=230)hp_x-=10;
	else if(hp_x>=220 && hp_x>=230)hp_x-=10;
	else if(hp_x>=220 && e_x>=500)e_x-=10;
	pm_x=mx, pm_y=my;
	if(pm_x>=st_x && pm_x<=st_x+153 && pm_y>=st_y && pm_y<=st_y+38)iShowBMP2(st_x-12, st_y-4, "1.Start_B.bmp",0);
	else if(pm_x>=op_x && pm_x<=op_x+153 && pm_y>=op_y && pm_y<=op_y+38)iShowBMP2(op_x-12, op_y-4, "1.Option_B.bmp", 0);
	else if(pm_x>=sc_x && pm_x<=sc_x+153 && pm_y>=sc_y && pm_y<=sc_y+38)iShowBMP2(sc_x-12, sc_y-4, "1.Score_B.bmp", 0);
	else if(pm_x>=hp_x && pm_x<=hp_x+153 && pm_y>=hp_y && pm_y<=hp_y+38)iShowBMP2(hp_x-12, hp_y-4, "1.Help_B.bmp", 0);
}
#endif LANDING