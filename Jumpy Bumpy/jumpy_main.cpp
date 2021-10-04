#include "iGraphics.h"
#include "bitmap_loader.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void score_calc();
bool options = false;
bool music=false;
int b;
int b_x=490, b_y=50;
int m_x, m_y;
int pm_x, pm_y;
bool lev_cmplt;
int l1_score=0;
int l2_score=0;
int l3_score=0;
int l4_score=0;
int l5_score=0;

struct playerScore{
	char name[100];
	int score1;
	int score2;
	int score3;
	int score4;
	int score5;
}ps[1000], psmed[1000],pshard[1000];

int speed;

/*_________________________________________________Log in/Register_________________________________________________*/

int log_img[20];
int log_x[30], log_y[30];
bool log_success = false;
int log_flag[5] = {0,0,0,0,0};


//text input
int a, a1;
char str[100]="", str2[100]="";
int len=0;
int mode=0;
char str_name[100]= {0,0}, str_pass[100]= {0,0}, str_auth[100]= {0,0};
char str_logname[100]= {0,0}, str_logpass[100]= {0,0};
char name_check[100], pass_check[100], auth_check[100];
int log_check=0;
int users;
int total_points;
int error=0;

void log_img_position()
{
	log_x[0]=140, log_y[0]=100;
	log_x[1]=225, log_y[1]=180;
	log_x[2]=225, log_y[2]=130;
	log_x[3]=490, log_y[3]=50;
	log_x[4]=log_x[17]=175, log_y[4]=log_x[17]=220;
	log_x[5]=log_x[18]=165, log_y[5]=log_x[18]=185;
	log_x[6]=log_x[19]=175, log_y[6]=log_x[19]=160;
	log_x[7]=log_x[20]=165, log_y[7]=log_x[20]=125;
	log_x[8]=225, log_y[8]=40;
	log_x[9]=175, log_y[9]=225+4;
	log_x[10]=165, log_y[10]=195+4;
	log_x[11]=175, log_y[11]=180+4;
	log_x[12]=165, log_y[12]=150+4;
	log_x[13]=175, log_y[13]=135+4;
	log_x[14]=165, log_y[14]=105+4;
	log_x[15]=225, log_y[15]=60;
	log_x[16]=225, log_y[16]=60;
}

void log_image()
{
	log_img[0]=iLoadImage("log in\\Box_B.png");
	log_img[1]=iLoadImage("log in\\Lg_i_S.png");
	log_img[2]=iLoadImage("log in\\Lg_i_B.png");
	log_img[3]=iLoadImage("log in\\Reg_i_S.png");
	log_img[4]=iLoadImage("log in\\Reg_i_B.png");
	log_img[5]=iLoadImage("log in\\User_txt.png");
	log_img[6]=iLoadImage("log in\\Box.png");
	log_img[7]=iLoadImage("log in\\Pass_txt.png");
	log_img[8]=iLoadImage("log in\\Fpass_txt_p.png");
	log_img[9]=iLoadImage("log in\\Error.png");
	log_img[10]=iLoadImage("log in\\Box.png");
	log_img[11]=iLoadImage("landing\\Exit.png");
}


FILE *reg_data= fopen("database\\reg_data.txt","a");
FILE *usrdata = fopen("database\\users.txt", "r");
FILE *lev_scores =fopen("database\\level scores.txt", "a");
char sc_name[100];
int sc_point=0;
int i_flag;

int q =1;
void log_screen()
{
	fscanf(usrdata, "%d", &users);
	fclose(usrdata);
	if(log_success==false)
	{
		iShowImage(log_x[0], log_y[0], 301, 146, log_img[0]);
		if(log_flag[0]==0)
		{
			iShowImage(log_x[1], log_y[1], 135, 38, log_img[1]);
			iShowImage(log_x[2], log_y[2], 135, 38, log_img[3]);
			iShowImage(log_x[3], log_y[3], 73,36, log_img[11]);

			if(pm_x>=log_x[1] && pm_x<=log_x[1]+135 && pm_y>=log_y[1] && pm_y<=log_y[1]+38)iShowImage(log_x[1]-8, log_y[1]-2, 152, 43, log_img[2]);
			else if(pm_x>=log_x[2] && pm_x<=log_x[2]+135 && pm_y>=log_y[2] && pm_y<=log_y[2]+38)iShowImage(log_x[2]-8, log_y[2]-2, 152, 43, log_img[4]);

			if(m_x>=log_x[3] && m_x<=log_x[3]+78 && m_y>=log_y[3] && m_y<=log_y[3]+36)
			{
				exit(0);
				m_x=m_y=0;
			}
			else if(m_x>=log_x[1] && m_x<=log_x[1]+135 && m_y>=log_y[1] && m_y<=log_y[1]+38)
			{
				log_flag[1]=1;// log in
				m_x=m_y=0;
				mode =1;
			}
			else if(m_x>=log_x[2] && m_x<=log_x[2]+135 && m_y>=log_y[2] && m_y<=log_y[2]+38) 
			{
				log_flag[2]=1;// Register
				m_x=m_y=0;
				mode =1;
			}
		}




		if(log_flag[1]==1)// log in
		{
			if(q==1)printf("Log in Screen appears\n");
			q++;
			log_flag[0] = 1;
			log_flag[1]=1;
			log_flag[2]=0;
			if(mode!=4)
			{
				iSetColor(255,255,255);
				iText(log_x[4], log_y[4], "Username", GLUT_BITMAP_8_BY_13);
				iShowImage(log_x[5], log_y[5], 250, 26, log_img[6]);
				iText(log_x[6], log_y[6], "Password", GLUT_BITMAP_8_BY_13);
				iShowImage(log_x[7], log_y[7], 250, 26, log_img[6]);
				iText(log_x[8], log_y[8], "Forgot Password?", GLUT_BITMAP_9_BY_15);
				if(error==0)iShowImage(log_x[15], log_y[15], 135, 38, log_img[1]);
			}
			iShowImage(b_x, b_y,78,36, b);
			if(pm_x>=log_x[8] && pm_x<=log_x[8]+145 && pm_y>=log_y[8] && pm_y<=log_y[8]+10 && mode!=4)//hover mouse
			{
				iSetColor(255,0,0);
				iText(log_x[8], log_y[8], "Forgot Password?", GLUT_BITMAP_9_BY_15);
			}
			if(m_x>=b_x && m_x<=b_x+78 && m_y>=b_y && m_y<=b_y+36)//back button
			{
				printf("Back\n");
				iKeyboard('\r');
				strcpy(str_logname, "");
				strcpy(str_logpass, "");
				strcpy(str, "");
				log_flag[0] = 0;
				log_flag[1]=0;
				a1=0;
				q=1;
				mode =0;	
				log_check = 0;
				error=0;
				m_x=m_y=0;
			}
			else if(m_x>=log_x[5] && m_x<=log_x[5]+250 && m_y>=log_y[5] && m_y<=log_y[5]+25)//Username input
			{
				m_x=m_y=0;
				printf("Enter Username\n");
				mode =1;

			}
			else if(m_x>=log_x[7] && m_x<=log_x[7]+250 && m_y>=log_y[7] && m_y<=log_y[7]+25)//Password input
			{
				m_x=m_y=0;
				printf("Enter Password\n");
				mode = 2;

			}
			else if(m_x>=log_x[8] && m_x<=log_x[8]+145 && m_y>=log_y[8] && m_y<=log_y[8]+10)//forgot pass
			{
				mode = 4;
				m_x=m_y=0;
			}

			if(mode == 1)// log in name input
			{
				iSetColor(0,0,0);
				iText(173, 193, str);
			}
			iSetColor(0,0,0);
			iText(173, 193, str_logname);


			if(mode == 2)// login pass
			{
				iSetColor(0,0,0);
				iText(173, 133, str);
			}
			iSetColor(0,0,0);
			iText(173, 133, str_logpass);


			/*if(mode==4)
			{
			iSetColor(255,255,255);
			iText(log_x[4], log_y[4], "Username", GLUT_BITMAP_8_BY_13);
			iShowImage(log_x[5], log_y[5], 250, 26, log_img[6]);
			iText(log_x[6], log_y[6], "Birth Place", GLUT_BITMAP_8_BY_13);
			iShowImage(log_x[7], log_y[7], 250, 26, log_img[6]);
			}*/
			FILE *read_reg_data = fopen("database\\reg_data.txt", "r");
			FILE *read_score = fopen("database\\level scores.txt", "r");
			if(m_x>=log_x[15] && m_x<=log_x[15]+135 && m_y>=log_y[15] && m_y<=log_y[15]+38 || a1==1)//log in button
			{
				iKeyboard('\r');
				a1=1;
				if(a1==1)
				{
					int cmp1, cmp2;
					for(int i=0;i<users;i++)
					{
						fscanf(read_score, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &ps[i].name, &ps[i].score1, &ps[i].score2,&ps[i].score3, &ps[i].score4, &ps[i].score5, &psmed[i].score1, &psmed[i].score2,&psmed[i].score3, &psmed[i].score4, &psmed[i].score5,&pshard[i].score1, &pshard[i].score2,&pshard[i].score3, &pshard[i].score4, &pshard[i].score5); 
						printf("%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", ps[i].name, ps[i].score1, ps[i].score2,ps[i].score3, ps[i].score4, ps[i].score5, psmed[i].score1, psmed[i].score2,psmed[i].score3, psmed[i].score4, psmed[i].score5,pshard[i].score1, pshard[i].score2,pshard[i].score3, pshard[i].score4, pshard[i].score5);
					}
					fclose(read_score);
					for(int i=0; i<=users; i++)
					{
						fscanf(read_reg_data,"%s %s %s", &name_check, &auth_check, &pass_check);
						cmp1 = strcmp(name_check, str_logname);
						cmp2 = strcmp(pass_check, str_logpass);
						if(cmp1==0 && cmp2==0)
						{
							i_flag =i;
							//printf("%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", ps[i].name, ps[i].score1, ps[i].score2, ps[i].score3, ps[i].score4, ps[i].score5, psmed[i].score1, psmed[i].score2,psmed[i].score3, psmed[i].score4, psmed[i].score5,pshard[i].score1, pshard[i].score2,pshard[i].score3, pshard[i].score4, pshard[i].score5);
							log_success = true;
							printf("Login Successful!\n");
							break;
						}
						else
							log_check = 1;
						if(fgetc(read_reg_data)==EOF)
							break;
					}
				}
				m_x=m_y=0;
			}

			fclose(read_reg_data);
			if(log_check == 1 && log_success == false)
			{
				error = 1;
				printf("Login Failed!\n");
				log_check = 0;
			}
			if(error == 1)
			{
				iShowImage(log_x[0], log_y[0], 301, 146, log_img[9]);
			}
			a1=0;
			if(mode == 1)
			{
				iSetColor(0,0,0);
				iLine(173,188,173,207);
			}
			else if(mode == 2)
			{
				iSetColor(0,0,0);
				iLine(173,128,173,147);
			}
		}


		else if(log_flag[2]==1)// Register
		{
			log_flag[0] = 1;
			log_flag[1]=0;
			iSetColor(255,255,255);
			iText(log_x[9], log_y[9], "Username", GLUT_BITMAP_8_BY_13);
			iShowImage(log_x[10], log_y[10], 250, 26, log_img[6]);
			iText(log_x[11], log_y[11], "Password", GLUT_BITMAP_8_BY_13);
			iShowImage(log_x[12], log_y[12], 250, 26, log_img[6]);
			iText(log_x[13], log_y[13], "Birth Place?", GLUT_BITMAP_8_BY_13);
			iShowImage(log_x[14], log_y[14], 250, 26, log_img[6]);
			iShowImage(b_x, b_y,78,36, b);

			if(m_x>=b_x && m_x<=b_x+78 && m_y>=b_y && m_y<=b_y+36)//back button
			{
				strcpy(str_name, "");
				strcpy(str_pass, "");
				strcpy(str_auth, "");
				log_flag[0] = 0;
				log_flag[2]=0;
				iKeyboard('\r');
				a=0;
				m_x=m_y=0;
			}
			else if(m_x>=log_x[10] && m_x<=log_x[10]+250 && m_y>=log_y[10] && m_y<=log_y[10]+25)//Username input
			{
				m_x=m_y=0;
				printf("Enter Username\n");
				mode = 1;
				iSetColor(0,0,0);
				iLine(175,203,175,222);
			}
			else if(m_x>=log_x[12] && m_x<=log_x[12]+250 && m_y>=log_y[12] && m_y<=log_y[12]+25)//Password input
			{
				m_x=m_y=0;
				printf("Enter Password\n");
				mode = 2;
				iSetColor(0,0,0);
				iLine(175,158,175,177);
			}
			else if(m_x>=log_x[14] && m_x<=log_x[14]+250 && m_y>=log_y[14] && m_y<=log_y[7]+25)//Authentic data innput
			{
				m_x=m_y=0;
				printf("Enter Birthplace\n");
				mode = 3;
				iSetColor(0,0,0);
				iLine(175,113,175,132);
			}
			if(mode == 1)
			{
				iSetColor(0,0,0);
				iText(173, 208, str);
			}
			iSetColor(0,0,0);
			iText(173, 208, str_name);
			if(mode == 2)
			{
				iSetColor(0,0,0);
				iText(173, 163, str);
			}
			iSetColor(0,0,0);
			iText(173, 163, str_pass);
			if(mode == 3)
			{
				iSetColor(0,0,0);
				iText(173, 118, str);
			}
			iSetColor(0,0,0);
			iText(173, 118, str_auth);
			iShowImage(log_x[16], log_y[16], 135, 38, log_img[3]);
			if(m_x>=log_x[15] && m_x<=log_x[15]+135 && m_y>=log_y[15] && m_y<=log_y[15]+38)
			{
				char lev_score_name[100];
				iKeyboard('\r');
				a=1;
				if(a==1)
				{
					FILE *usrdata = fopen("database\\users.txt", "w");
					users++;
					strcpy(sc_name, str_name);
					strcpy(lev_score_name, str_name);
					printf("%d\n", users);
					fprintf(reg_data,"%s\n", str_name);
					fprintf(reg_data,"%s\n", str_auth);
					fprintf(reg_data,"%s\n", str_pass);
					printf("%s \n%s \n%s \n", str_name, str_auth, str_pass);
					log_flag[0]=0;
					log_flag[2]=0;
					fprintf(usrdata,"%d", users);
					fclose(usrdata);
					fclose(reg_data);
					fprintf(lev_scores, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",lev_score_name, l1_score, l2_score, l3_score, l4_score, l5_score, l1_score, l2_score, l3_score, l4_score, l5_score, l1_score, l2_score, l3_score, l4_score, l5_score);
					fclose(lev_scores);
					a=0;
				}
				m_x=m_y=0;
			}
			if(mode == 1)
			{
				iSetColor(0,0,0);
				iLine(173,203,173,222);
			}
			else if(mode == 2)
			{
				iSetColor(0,0,0);
				iLine(173,158,173,177);
			}
			else if(mode == 3)
			{
				iSetColor(0,0,0);
				iLine(173,113,173,132);
			}

		}
	}
}


/*_________________________________________________Landing Screen_________________________________________________*/
int nam_x, nam_y;
int st_x, st_y;
int op_x, op_y;
int sc_x, sc_y;
int help_x, help_y;
int exit_x, exit_y;
int sel_op=0;
int img[10];

void l_screen_size()
{
	nam_x=0, nam_y=400;
	st_x=600, st_y=210;
	op_x=600, op_y=160;
	sc_x=600, sc_y=110;
	help_x=600, help_y=60;
	exit_x=600, exit_y=50;
}

void l_screen_image()
{
	img[0]=iLoadImage("landing\\1.Name.png");
	img[1]=iLoadImage("landing\\Start_S.png");
	img[2]=iLoadImage("landing\\Start_B.png");
	img[3]=iLoadImage("landing\\Option_S.png");
	img[4]=iLoadImage("landing\\Option_B.png");
	img[5]=iLoadImage("landing\\Score_S.png");
	img[6]=iLoadImage("landing\\Score_B.png");
	img[7]=iLoadImage("landing\\Help_S.png");
	img[8]=iLoadImage("landing\\Help_B.png");
	img[9]=iLoadImage("landing\\Exit.png");
}

void l_screen()
{
	iShowBMP(0, 0, "Landing_Screen(bg).bmp");
	iShowImage(nam_x, nam_y,429,137, img[0]);
	iShowImage(st_x, st_y, 153,38, img[1]);
	iShowImage(op_x, op_y, 153,38, img[3]);
	iShowImage(sc_x, sc_y, 153,38, img[5]);
	iShowImage(help_x, help_y, 153,38, img[7]);
	iShowImage(exit_x, exit_y, 73,36, img[9]);
	if(nam_x<=90 && nam_y>=230)
	{
		nam_x+=2;
		nam_y-=5;
	}
	else if(nam_y>=80 && log_success == false)log_screen();
	else if(log_success==true && st_x>=230)st_x-=20;
	else if(st_x>=220 && op_x>=230)op_x-=20;
	else if(op_x>=220 && sc_x>=230)sc_x-=20;
	else if(sc_x>=220 && help_x>=230)help_x-=20;
	else if(help_x>=220 && exit_x>=520)exit_x-=20;

	if(pm_x>=st_x && pm_x<=st_x+153 && pm_y>=st_y && pm_y<=st_y+38)iShowImage(st_x-12, st_y-4, 178,44, img[2]);
	else if(pm_x>=op_x && pm_x<=op_x+153 && pm_y>=op_y && pm_y<=op_y+38)iShowImage(op_x-12, op_y-4, 178,44, img[4]);
	else if(pm_x>=sc_x && pm_x<=sc_x+153 && pm_y>=sc_y && pm_y<=sc_y+38)iShowImage(sc_x-12, sc_y-4, 178,44, img[6]);
	else if(pm_x>=help_x && pm_x<=help_x+153 && pm_y>=help_y && pm_y<=help_y+38)iShowImage(help_x-12, help_y-4, 178,44, img[8]);

	if(m_x>=st_x && m_x<=st_x+153 && m_y>=st_y && m_y<=st_y+38)
	{
		sel_op=1;//jump to Difficulty Level Screen
		m_x=m_y=0;
	}
	else if(m_x>=op_x && m_x<=op_x+153 && m_y>=op_y && m_y<=op_y+38)
	{
		sel_op=2;//jump to
		m_x=m_y=0;
	}
	else if(m_x>=sc_x && m_x<=sc_x+153 && m_y>=sc_y && m_y<=sc_y+38)
	{
		sel_op=3;
		m_x=m_y=0;
	}
	else if(m_x>=help_x && m_x<=help_x+153 && m_y>=help_y && m_y<=help_y+38)
	{
		sel_op=4;
		m_x=m_y=0;
	}
	else if(m_x>=exit_x && m_x<=exit_x+78 && m_y>=exit_y && m_y<=exit_y+36)
	{
		exit(0);
		m_x=m_y=0;
	}
}


/*_________________________________________________Difficulty Level Screen_________________________________________________*/

int dif_sel_op=0;
int o1_x, o1_y;
int o2_x, o2_y;
int o3_x, o3_y;
int d_image[10];

void d_screen_size()
{
	o1_x=600, o1_y=250;
	o2_x=600, o2_y=180;
	o3_x=600, o3_y=110;
}

void d_screen_image()
{
	d_image[0]=iLoadImage("dif_lev//Easy.png");
	d_image[1]=iLoadImage("dif_lev//Easy_B.png");
	d_image[2]=iLoadImage("dif_lev//Medium.png");
	d_image[3]=iLoadImage("dif_lev//Medium_B.png");
	d_image[4]=iLoadImage("dif_lev//Hard.png");
	d_image[5]=iLoadImage("dif_lev//Hard_B.png");

}

void d_screen()
{
	iShowBMP(0, 0, "All_Screen(bg).bmp");
	iShowImage(o1_x, o1_y,153,38, d_image[0]);
	iShowImage(o2_x, o2_y,153,38, d_image[2]);
	iShowImage(o3_x, o3_y,153,38, d_image[4]);
	iShowImage(b_x, b_y,78,36, b);
	if(o1_x>=225)o1_x-=20;
	else if(o1_x<=230 && o2_x>=225)o2_x-=20;
	else if(o2_x<=230 && o3_x>=225)o3_x-=20;


	if(pm_x>=o1_x && pm_x<=o1_x+153 && pm_y>=o1_y && pm_y<=o1_y+38)iShowImage(o1_x-12, o1_y-4, 178,44, d_image[1]);
	else if(pm_x>=o2_x && pm_x<=o2_x+153 && pm_y>=o2_y && pm_y<=o2_y+38)iShowImage(o2_x-12, o2_y-4, 178,44, d_image[3]);
	else if(pm_x>=o3_x && pm_x<=o3_x+153 && pm_y>=o3_y && pm_y<=o3_y+38)iShowImage(o3_x-12, o3_y-4, 178,44, d_image[5]);

	if(m_x>=o1_x && m_x<=o1_x+153 && m_y>=o1_y && m_y<=o1_y+38)
	{
		speed=1;
		dif_sel_op=1;
		m_x=m_y=0;
	}
	else if(m_x>=o2_x && m_x<=o2_x+153 && m_y>=o2_y && m_y<=o2_y+38)
	{
		speed=2;
		dif_sel_op=2;
		m_x=m_y=0;
	}
	else if(m_x>=o3_x && m_x<=o3_x+153 && m_y>=o3_y && m_y<=o3_y+38)
	{
		speed=3;
		dif_sel_op=3;
		m_x=m_y=0;
	}
	else if(m_x>b_x && m_x<b_x+78 && m_y>=b_y && m_y<=b_y+36)
	{
		sel_op=0;
		m_x=m_y=0;
	}

}

/*_________________________________________________Character_________________________________________________*/
double ch_x=0, ch_y=55;
int ch_img[13];
int ch_rot_img[13];
int c_flag[5]= {0,0,0,0,0};
int char_in=0;
bool rotate = false;
bool stand = true;
int stdcount = 0;
bool running = true;

void ch_image()
{
	ch_img[0] = iLoadImage("char\\C1.png");
	ch_img[1] = iLoadImage("char\\C2.png");
	ch_img[2] = iLoadImage("char\\C2.png");
	ch_img[3] = iLoadImage("char\\C2.png");
	ch_img[4] = iLoadImage("char\\C3.png");
	ch_img[5] = iLoadImage("char\\C3.png");
	ch_img[6] = iLoadImage("char\\C3.png");
	ch_img[7] = iLoadImage("char\\C4.png");
	ch_img[8] = iLoadImage("char\\C4.png");
	ch_img[9] = iLoadImage("char\\C4.png");
	ch_img[10] = iLoadImage("char\\C5.png");
	ch_img[11] = iLoadImage("char\\C5.png");
	ch_img[12] = iLoadImage("char\\C5.png");
	ch_img[13] = iLoadImage("char\\C6.png");
}

void ch_rot_image()
{
	ch_rot_img[0] = iLoadImage("char\\C11.png");
	ch_rot_img[1] = iLoadImage("char\\C22.png");
	ch_rot_img[2] = iLoadImage("char\\C22.png");
	ch_rot_img[3] = iLoadImage("char\\C22.png");
	ch_rot_img[4] = iLoadImage("char\\C33.png");
	ch_rot_img[5] = iLoadImage("char\\C33.png");
	ch_rot_img[6] = iLoadImage("char\\C33.png");
	ch_rot_img[7] = iLoadImage("char\\C44.png");
	ch_rot_img[8] = iLoadImage("char\\C44.png");
	ch_rot_img[9] = iLoadImage("char\\C44.png");
	ch_rot_img[10] = iLoadImage("char\\C55.png");
	ch_rot_img[11] = iLoadImage("char\\C55.png");
	ch_rot_img[12] = iLoadImage("char\\C55.png");
}
int jumpCount =0;
bool jump;
bool jumpUp =false;
bool jumpDown = false;
int x;
int reach =0;
int ground =55;
int height=90;
int dy =0;
bool floating = false;
bool f = false;
int pch_y=55;
bool scn_change = false;

void Jump()
{
	if(rotate == false)
	{
		if(stand==true)
		{
			if(ch_y<=(ground+height) && jumpUp == true)
			{
				ch_y+=5;
				if(ch_y==(ground+height))
				{
					jumpUp=false;
					jumpDown =true;
				}
			}
			else if(ch_y>=ground && jumpDown ==true)
			{
				if(ch_y==ground)
				{
					jump=false;
					jumpDown = false;
				}
				else
					ch_y-=5;
			}
		}
		else if(stand==false)
		{
			if(ch_y<=(ground+height) && jumpUp == true)
			{
				ch_y+=5;
				ch_x+=2.5;
				if(ch_y==(ground+height))
				{
					jumpUp=false;
					jumpDown = true;
				}
			}
			else if(ch_y>=ground && jumpDown ==true)
			{
				if(ch_y==ground)
				{
					jump=false;
					jumpDown =false;
				}
				else
				{
					ch_y-=5;
					ch_x+=2.5;
				}
			}
		}
	}
	else if(rotate == true)
	{
		if(stand==true)
		{
			if(ch_y<=(ground+height) && jumpUp == true)
			{
				if(ch_y==(ground+height))
				{
					jumpUp=false;
					jumpDown =true;
				}
				else
					ch_y+=5;
			}
			else if(ch_y>=ground && jumpDown == true)
			{
				if(ch_y==ground)
				{
					jump=false;
					jumpDown =false;
				}
				else
					ch_y-=5;
			}
		}
		else if(stand==false)
		{
			if(ch_y<=(ground+height) && jumpUp == true)
			{
				if(ch_y==(ground+height))
				{
					jumpUp=false;
					jumpDown =true;
				}
				else
				{
					ch_y+=5;
					ch_x-=2.5;
				}
			}
			else if(ch_y>=ground && jumpDown ==true)
			{
				if(ch_y==ground)
				{
					jump=false;
					jumpDown =false;
				}
				else
				{
					ch_y-=5;
					ch_x-=2.5;
				}
			}
		}
	}
}


void character()//character run
{
	char_in++;
	if(char_in==12)
	{
		char_in=0;
	}
}
void character_move()
{
	if(rotate==true && jump == false)
	{
		if(stand==true && jump == false)
		{
			iShowImage(ch_x, ch_y, 25, 31, ch_rot_img[0]);
		}
		else
		{
			iShowImage(ch_x, ch_y, 25, 31, ch_rot_img[char_in]);//Level1
			stdcount++;
			if(stdcount>=20)
			{
				stdcount=0;
				stand=true;
			}
		}

	}
	else if(rotate == false && jump == false)
	{
		if(stand==true)
		{
			iShowImage(ch_x, ch_y, 25, 31, ch_img[0]);
		}
		else
		{
			iShowImage(ch_x, ch_y, 25, 31, ch_img[char_in]);//Level1
			stdcount++;
			if(stdcount>=20)
			{
				stdcount=0;
				stand=true;
			}
		}
	}
	else
	{
		if(jump==true && rotate == false)
		{
			iShowImage(ch_x, ch_y, 25, 31, ch_img[3]);
		}
		else if(jump==true && rotate == true)
		{
			iShowImage(ch_x, ch_y, 25, 31, ch_rot_img[3]);
		}
		//jumpUp = false;
	}
}



/*_________________________________________________Level Screen_________________________________________________*/


int l_x[5], l_y[5];
int sel_lev=0;

int p[10];
void lev_screen_size()
{
	l_x[0]=180, l_y[0]=220;
	l_x[1]=l_x[0]+100, l_y[1]=220;
	l_x[2]=l_x[1]+100, l_y[2]=220;
	l_x[3]=220, l_y[3]=120;
	l_x[4]=l_x[3]+120, l_y[4]=120;
}

void lev_screen_image()
{
	p[0]=iLoadImage("Level_Screen(1).png");
	p[1]=iLoadImage("Level_Screen(2).png");
	p[2]=iLoadImage("Level_Screen(3).png");
	p[3]=iLoadImage("Level_Screen(4).png");
	p[4]=iLoadImage("Level_Screen(5).png");
	p[5]=iLoadImage("Level_Screen\\Lock_i.png");
	p[6]=iLoadImage("Cr.png");
	p[7]=iLoadImage("Rect.png");
}
void lev_screen()
{
	iShowBMP(0, 0, "All_Screen(bg).bmp");
	iShowImage(l_x[0], l_y[0],60,60, p[0]);
	iShowImage(l_x[1], l_y[1],60,60, p[1]);
	if(dif_sel_op==1)
	{
		if(ps[i_flag].score1<=80)iShowImage(l_x[1]+15, l_y[1]+20,29,29, p[5]);
		iShowImage(l_x[2], l_y[2],60,60, p[2]);
		if(ps[i_flag].score2<=80)iShowImage(l_x[2]+15, l_y[2]+20,29,29, p[5]);
		iShowImage(l_x[3], l_y[3],60,60, p[3]);
		if(ps[i_flag].score3<=80)iShowImage(l_x[3]+15, l_y[3]+18,29,29, p[5]);
		iShowImage(l_x[4], l_y[4],60,60, p[4]);
		if(ps[i_flag].score4<=80)iShowImage(l_x[4]+15, l_y[4]+18,29,29, p[5]);

		if(m_x>=l_x[0] && m_x<=l_x[0]+60 && m_y>=l_y[0] && m_y<=l_y[0]+60)
		{
			sel_lev=1;
			m_x=m_y=0;
		}
		else if(m_x>=l_x[1] && m_x<=l_x[1]+60 && m_y>=l_y[1] && m_y<=l_y[1]+60 && ps[i_flag].score1>=80)
		{
			sel_lev=2;
			m_x=m_y=0;
		}
		else if(m_x>=l_x[2] && m_x<=l_x[2]+60 && m_y>=l_y[2] && m_y<=l_y[2]+60 && ps[i_flag].score2>=80)
		{
			sel_lev=3;
			m_x=m_y=0;
		}
		else if(m_x>=l_x[3] && m_x<=l_x[3]+60 && m_y>=l_y[3] && m_y<=l_y[3]+60 && ps[i_flag].score3>=80)
		{
			sel_lev=4;
			m_x=m_y=0;
		}
		else if(m_x>=l_x[4] && m_x<=l_x[4]+60 && m_y>=l_y[4] && m_y<=l_y[4]+60 && ps[i_flag].score4>=80)
		{
			sel_lev=5;
			m_x=m_y=0;
		}
	}
	else if(dif_sel_op==2)
	{
		if(psmed[i_flag].score1<=80)iShowImage(l_x[1]+15, l_y[1]+20,29,29, p[5]);
		iShowImage(l_x[2], l_y[2],60,60, p[2]);
		if(psmed[i_flag].score2<=80)iShowImage(l_x[2]+15, l_y[2]+20,29,29, p[5]);
		iShowImage(l_x[3], l_y[3],60,60, p[3]);
		if(psmed[i_flag].score3<=80)iShowImage(l_x[3]+15, l_y[3]+18,29,29, p[5]);
		iShowImage(l_x[4], l_y[4],60,60, p[4]);
		if(psmed[i_flag].score4<=80)iShowImage(l_x[4]+15, l_y[4]+18,29,29, p[5]);

		if(m_x>=l_x[0] && m_x<=l_x[0]+60 && m_y>=l_y[0] && m_y<=l_y[0]+60)
		{
			sel_lev=1;
			m_x=m_y=0;
		}
		else if(m_x>=l_x[1] && m_x<=l_x[1]+60 && m_y>=l_y[1] && m_y<=l_y[1]+60 && psmed[i_flag].score1>=80)
		{
			sel_lev=2;
			m_x=m_y=0;
		}
		else if(m_x>=l_x[2] && m_x<=l_x[2]+60 && m_y>=l_y[2] && m_y<=l_y[2]+60 && psmed[i_flag].score2>=80)
		{
			sel_lev=3;
			m_x=m_y=0;
		}
		else if(m_x>=l_x[3] && m_x<=l_x[3]+60 && m_y>=l_y[3] && m_y<=l_y[3]+60 && psmed[i_flag].score3>=80)
		{
			sel_lev=4;
			m_x=m_y=0;
		}
		else if(m_x>=l_x[4] && m_x<=l_x[4]+60 && m_y>=l_y[4] && m_y<=l_y[4]+60 && psmed[i_flag].score4>=80)
		{
			sel_lev=5;
			m_x=m_y=0;
		}
	}
	else if(dif_sel_op==3)
	{
		if(pshard[i_flag].score1<=80)iShowImage(l_x[1]+15, l_y[1]+20,29,29, p[5]);
		iShowImage(l_x[2], l_y[2],60,60, p[2]);
		if(pshard[i_flag].score2<=80)iShowImage(l_x[2]+15, l_y[2]+20,29,29, p[5]);
		iShowImage(l_x[3], l_y[3],60,60, p[3]);
		if(pshard[i_flag].score3<=80)iShowImage(l_x[3]+15, l_y[3]+18,29,29, p[5]);
		iShowImage(l_x[4], l_y[4],60,60, p[4]);
		if(pshard[i_flag].score4<=80)iShowImage(l_x[4]+15, l_y[4]+18,29,29, p[5]);

		if(m_x>=l_x[0] && m_x<=l_x[0]+60 && m_y>=l_y[0] && m_y<=l_y[0]+60)
		{
			sel_lev=1;
			m_x=m_y=0;
		}
		else if(m_x>=l_x[1] && m_x<=l_x[1]+60 && m_y>=l_y[1] && m_y<=l_y[1]+60 && pshard[i_flag].score1>=80)
		{
			sel_lev=2;
			m_x=m_y=0;
		}
		else if(m_x>=l_x[2] && m_x<=l_x[2]+60 && m_y>=l_y[2] && m_y<=l_y[2]+60 && pshard[i_flag].score2>=80)
		{
			sel_lev=3;
			m_x=m_y=0;
		}
		else if(m_x>=l_x[3] && m_x<=l_x[3]+60 && m_y>=l_y[3] && m_y<=l_y[3]+60 && pshard[i_flag].score3>=80)
		{
			sel_lev=4;
			m_x=m_y=0;
		}
		else if(m_x>=l_x[4] && m_x<=l_x[4]+60 && m_y>=l_y[4] && m_y<=l_y[4]+60 && pshard[i_flag].score4>=80)
		{
			sel_lev=5;
			m_x=m_y=0;
		}
	}
	iShowImage(b_x, b_y,78,36, b);


	if(m_x>b_x && m_x<b_x+78 && m_y>=b_y && m_y<=b_y+36)
	{
		sel_op=1;
		dif_sel_op=0;
		m_x=m_y=0;
	}
}


void flt(int ax_x, int ax_y)
{
	if(rotate == false)
	{
		if(ch_x+10 >= ax_x && ch_x+10 <= ax_x+50 && jumpUp ==  true && ch_y>=pch_y+60)
		{
			jumpUp=false;
			ch_y = ax_y+10;
		}
		else if(ch_x+10 <= ax_x && ch_y>=pch_y+60)
		{
			jumpUp=true;
			reach = 1;
		}
		else if (ch_x+10 >= ax_x+60 && ch_y>=pch_y+60)
		{
			jumpUp=true;
			reach = 1;
		}
	}
	if(rotate == true)
	{
		if(ch_x >= ax_x+20 && ch_x <= ax_x+62 && jumpUp ==  true && ch_y>=pch_y+60)
		{
			jumpUp=false;
			ch_y = ax_y+10;
		}
		else if(ch_x+10 <= ax_x && ch_y>=pch_y+60)
		{
			jumpUp=true;
			reach = 1;
		}
		else if (ch_x+10 >= ax_x+60 && ch_y>=pch_y+60)
		{
			jumpUp=true;
			reach = 1;
		}
	}
}
int water_1, water_2, water_3;
void water(int x)
{
	water_1=x;
	water_2=water_1-5+x;
	water_3=water_2-5+x;
	iShowImage(x, 0, 49, 29, p[7]);

}

/*________________________________________________Level 1 Screen________________________________________________*/

int lvl_x[15], lvl_y[15],img_ld_1[15];
int l1_f[10]={0,0};

void l1_position()
{
	lvl_x[0]= 245, lvl_y[0]=355;
	lvl_x[1]= 530, lvl_y[1]=355; 
	lvl_x[2]= 80, lvl_y[2]=355;
	lvl_x[3]= 50, lvl_y[3]=360;
	lvl_x[4]= 250, lvl_y[4]=140;
	lvl_x[5]= 425, lvl_y[5]=140;
	lvl_x[6]= 530, lvl_y[6]=140;
	lvl_x[7]= 145, lvl_y[7]=110;
	lvl_x[8]= 295, lvl_y[8]=80;
	lvl_x[9]= 530, lvl_y[9]=80;
	lvl_x[10]= 315, lvl_y[10]=90;
	lvl_x[11]= 445, lvl_y[11]=140;
	lvl_x[12]= 200, lvl_y[12]=140;
	lvl_x[13]=180, lvl_y[13]=110;
	lvl_x[14]=430, lvl_y[14]=110;

}
void l1_image()
{
	img_ld_1[0]= iLoadImage("Level 1\\Lvl1(1)-01.png");
	img_ld_1[1]= iLoadImage("Level 1\\Lvl_1_icon_1.png");
	img_ld_1[2]= iLoadImage("Pause_1.png");
	img_ld_1[3]= iLoadImage("Love_1.png");
	img_ld_1[4]= iLoadImage("Point.png");
	img_ld_1[5]= iLoadImage("Level 1\\Lvl1(2)-01.png");
	img_ld_1[6]= iLoadImage("Level 1\\Lvl1(3)-01.png");
	img_ld_1[7]= iLoadImage("Floating.png");
	img_ld_1[8]= iLoadImage("Flag.png");
	img_ld_1[9]=iLoadImage("Lvl_cmplt_icon.png");
	img_ld_1[10] = iLoadImage("Pop_up_p.png");
	img_ld_1[11] = iLoadImage("Game_O.png");

}
int l1_point[10]={0,0};
int l1_life =3;
void l1_screen()
{
	char points[10], life[5];
	lev_cmplt=false;

	/*________________________________________________Screen 1________________________________________________*/
	if(l1_f[0]==0)
	{
		iShowImage(0, 0, 600,400,img_ld_1[0]);
		iShowImage(lvl_x[0], lvl_y[0],78,23,img_ld_1[1]);
		iShowImage(lvl_x[1], lvl_y[1],24,25,img_ld_1[2]);
		iShowImage(lvl_x[2], lvl_y[2],28,22,img_ld_1[3]);
		itoa(l1_life, life, 10);
		iSetColor(255,0,0);
		iText(lvl_x[3],lvl_y[3], life, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(lvl_x[3]+15,lvl_y[3], "x", GLUT_BITMAP_TIMES_ROMAN_24);
		itoa(l1_score, points ,10);
		iText(247, 340, "POINTS:", GLUT_BITMAP_9_BY_15);
		iText(310, 340, points, GLUT_BITMAP_9_BY_15);

		if(l1_point[0]==0)iShowImage(lvl_x[4], lvl_y[4],20,20,img_ld_1[4]);
		if((ch_y+25>= lvl_y[4] && ch_y+25<= lvl_y[4]+20) && (ch_x+20>= lvl_x[4] && ch_x+20<= lvl_x[4]+20 && l1_point[0]==0) || (ch_y+25>= lvl_y[4] && ch_y+25<= lvl_y[4]+20) && (ch_x+10>= lvl_x[4] && ch_x+5<= lvl_x[4]+20 && l1_point[0]==0))
		{
			if(l1_point[0]==0)l1_score +=10;
			l1_point[0]=1;
		}

		if(l1_point[1]==0)iShowImage(lvl_x[5], lvl_y[5],20,20,img_ld_1[4]);
		if((ch_y+25>= lvl_y[5] && ch_y+25<= lvl_y[5]+20) && (ch_x+20>= lvl_x[5] && ch_x+20<= lvl_x[5]+20) || (ch_y+25>= lvl_y[5] && ch_y+25<= lvl_y[5]+20) && (ch_x+10>= lvl_x[5] && ch_x+5<= lvl_x[5]+20))
		{
			if(l1_point[1]==0)l1_score +=10;
			l1_point[1]=1;
		}

		if(l1_point[2]==0)iShowImage(lvl_x[6], lvl_y[6],20,20,img_ld_1[4]);
		if((ch_y+25>= lvl_y[6] && ch_y+25<= lvl_y[6]+20) && (ch_x+20>= lvl_x[6] && ch_x+20<= lvl_x[6]+20) || (ch_y+25>= lvl_y[6] && ch_y+25<= lvl_y[6]+20) && (ch_x+10>= lvl_x[6] && ch_x+5<= lvl_x[6]+20))
		{
			if(l1_point[2]==0)l1_score +=10;
			l1_point[2]=1;
		}
		if(ch_x+20>=245 && ch_x<=280 && ch_y>=50 && ch_y<=73)
		{
			l1_life--;
			rotate =false;
			ch_x=0;
		}
		if(ch_x+20>=420 && ch_x<=455 && ch_y>=50 && ch_y<=73)
		{
			l1_life--;
			jumpUp=false;
			jumpDown=false;
			rotate =false;
			ch_x=0;
		}

		if(ch_x>=590)
		{
			scn_change = true;
			ch_x=0;
			l1_f[0]=1;
			l1_f[1]=1;
		}
	}

	/*________________________________________________Screen 2________________________________________________*/
	else if(l1_f[1]==1)
	{
		scn_change = false;
		iShowImage(0, 0, 600,400,img_ld_1[5]);
		iShowImage(lvl_x[0], lvl_y[0],78,23,img_ld_1[1]);
		iShowImage(lvl_x[1], lvl_y[1],24,25,img_ld_1[2]);
		iShowImage(lvl_x[2], lvl_y[2],28,22,img_ld_1[3]);
		itoa(l1_life, life, 10);
		iSetColor(255,0,0);
		iText(lvl_x[3],lvl_y[3], life, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(lvl_x[3]+15,lvl_y[3], "x", GLUT_BITMAP_TIMES_ROMAN_24);
		itoa(l1_score, points ,10);
		iText(247, 340, "POINTS:", GLUT_BITMAP_9_BY_15);
		iText(310, 340, points, GLUT_BITMAP_9_BY_15);

		if(l1_point[3]==0)iShowImage(lvl_x[7], lvl_y[7],20,20,img_ld_1[4]);
		if((ch_y+25>= lvl_y[7] && ch_y+25<= lvl_y[7]+20) && (ch_x+20>= lvl_x[7] && ch_x+20<= lvl_x[7]+20) || (ch_y+25>= lvl_y[7] && ch_y+25<= lvl_y[7]+20) && (ch_x+10>= lvl_x[7] && ch_x+5<= lvl_x[7]+20))
		{
			if(l1_point[3]==0)l1_score +=10;
			l1_point[3]=1;
		}

		if(l1_point[4]==0)iShowImage(lvl_x[8], lvl_y[8],20,20,img_ld_1[4]);
		if((ch_y+25>= lvl_y[8] && ch_y+25<= lvl_y[8]+20) && (ch_x+20>= lvl_x[8] && ch_x+20<= lvl_x[8]+20) || (ch_y+25>= lvl_y[8] && ch_y+25<= lvl_y[8]+20) && (ch_x+10>= lvl_x[8] && ch_x+5<= lvl_x[8]+20))
		{
			if(l1_point[4]==0)l1_score +=10;
			l1_point[4]=1;
		}

		if(l1_point[5]==0)iShowImage(lvl_x[9], lvl_y[9],20,20,img_ld_1[4]);
		if((ch_y+25>= lvl_y[9] && ch_y+25<= lvl_y[9]+20) && (ch_x+20>= lvl_x[9] && ch_x+20<= lvl_x[9]+20) || (ch_y+25>= lvl_y[9] && ch_y+25<= lvl_y[9]+20) && (ch_x+10>= lvl_x[9] && ch_x+5<= lvl_x[9]+20))
		{
			if(l1_point[5]==0)l1_score +=10;
			l1_point[5]=1;
		}

		if(ch_x+20>=430 && ch_x<=465 && ch_y>=50 && ch_y<=73)
		{
			l1_life--;
			jumpUp=false;
			jumpDown=false;
			rotate =false;
			ch_x=0;
		}
		if(ch_x+8>=140 && ch_x+20<=185 && ch_y>=0 && ch_y<=70)//hole
		{
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l1_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
				rotate = false;
			}
		}
		if(ch_x>=590)
		{
			ch_x=0;
			l1_f[0]=1;
			l1_f[1]=0;
			l1_f[2]=1;

		}

	}

	/*________________________________________________Screen 3________________________________________________*/
	else if(l1_f[2]==1)
	{
		scn_change = false;
		iShowImage(0, 0, 600,400,img_ld_1[6]);
		iShowImage(lvl_x[0], lvl_y[0],78,23,img_ld_1[1]);
		iShowImage(lvl_x[1], lvl_y[1],24,25,img_ld_1[2]);
		iShowImage(lvl_x[2], lvl_y[2],28,22,img_ld_1[3]);
		iShowImage(575, 55, 26, 32, img_ld_1[8]);
		itoa(l1_life, life, 10);
		iSetColor(255,0,0);
		iText(lvl_x[3],lvl_y[3], life, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(lvl_x[3]+15,lvl_y[3], "x", GLUT_BITMAP_TIMES_ROMAN_24);
		itoa(l1_score, points ,10);
		iText(247, 340, "POINTS:", GLUT_BITMAP_9_BY_15);
		iText(310, 340, points, GLUT_BITMAP_9_BY_15);

		if(l1_point[6]==0)iShowImage(lvl_x[10], lvl_y[10],20,20,img_ld_1[4]);
		if((ch_y+25>= lvl_y[10] && ch_y+25<= lvl_y[10]+20) && (ch_x+20>= lvl_x[10] && ch_x+20<= lvl_x[10]+20)|| (ch_y+25>= lvl_y[10] && ch_y+25<= lvl_y[10]+20) && (ch_x+10>= lvl_x[10] && ch_x+5<= lvl_x[10]+20))
		{
			if(l1_point[6]==0)l1_score +=10;
			l1_point[6]=1;
		}

		if(l1_point[7]==0)iShowImage(lvl_x[11], lvl_y[11],20,20,img_ld_1[4]);
		if((ch_y+25>= lvl_y[11] && ch_y+25<= lvl_y[11]+20) && (ch_x+20>= lvl_x[11] && ch_x+20<= lvl_x[11]+20)|| (ch_y+25>= lvl_y[11] && ch_y+25<= lvl_y[11]+20) && (ch_x+10>= lvl_x[11] && ch_x+5<= lvl_x[11]+20))
		{
			if(l1_point[7]==0)l1_score +=10;
			l1_point[7]=1;
		}

		if(l1_point[8]==0)iShowImage(lvl_x[12], lvl_y[12],20,20,img_ld_1[4]);
		if((ch_y+25>= lvl_y[12] && ch_y+25<= lvl_y[12]+20) && (ch_x+20>= lvl_x[12] && ch_x+20<= lvl_x[12]+20)|| (ch_y+25>= lvl_y[12] && ch_y+25<= lvl_y[12]+20) && (ch_x+10>= lvl_x[12] && ch_x+5<= lvl_x[12]+20))
		{
			if(l1_point[8]==0)l1_score +=10;
			l1_point[8]=1;
		}

		iShowImage(lvl_x[13], lvl_y[13],62,14,img_ld_1[7]);
		if( ch_x+10>=lvl_x[13]+5 && ch_x+12<=lvl_x[13]+58 && ch_y==lvl_y[13]+10)
		{
			jumpDown=false;
			jump=false;
		}
		else if( ch_x+10>=lvl_x[14]+5 && ch_x+12<=lvl_x[14]+58 && ch_y==lvl_y[14]+10)
		{
			jumpDown=false;
			jump=false;
		}
		else
		{
			jumpDown =true;
		}

		iShowImage(lvl_x[14], lvl_y[14],62,14,img_ld_1[7]);


		if(ch_x+8>=310 && ch_x+20<=355 && ch_y>=0 && ch_y<=70)//hole
		{
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l1_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
				rotate = false;
			}
		}
		if(ch_x>=570)
		{
			if(l1_f[4]==0)
			{
				l1_score+=10;
				
				FILE *print_score = fopen("database\\level scores.txt", "w");
				if(dif_sel_op==1)
				{
					ps[i_flag].score1=l1_score;
				}
				else if(dif_sel_op==2)
				{
					psmed[i_flag].score1=l1_score;
				}
				else if(dif_sel_op==3)
				{
					pshard[i_flag].score1=l1_score;
				}
				for(int i=0; i<users;i++)
				{
					fprintf(print_score, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", ps[i].name, ps[i].score1,ps[i].score2,ps[i].score3,ps[i].score4,ps[i].score5, psmed[i].score1,psmed[i].score2,psmed[i].score3,psmed[i].score4,psmed[i].score5,pshard[i].score1,pshard[i].score2,pshard[i].score3,pshard[i].score4,pshard[i].score5);
					printf("%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", ps[i].name, ps[i].score1,ps[i].score2,ps[i].score3,ps[i].score4,ps[i].score5, psmed[i].score1,psmed[i].score2,psmed[i].score3,psmed[i].score4,psmed[i].score5,pshard[i].score1,pshard[i].score2,pshard[i].score3,pshard[i].score4,pshard[i].score5);
				}
				fclose(print_score);
				l1_f[4]=1;
			}

			iShowImage(170, 150, 247, 138, img_ld_1[9]);
			lev_cmplt = true;
			if(m_x>265 && m_x<340 && m_y>170 && m_y<190)
			{
				dif_sel_op=1;
				sel_lev=0;
				ch_x=0;
				l1_life = 3;
				l1_f[0]=0;
				l1_f[1]=0;
				l1_f[2]=0;
				l1_point[0] =0;
				l1_point[1] =0;
				l1_point[2] =0;
				l1_point[3] =0;
				l1_point[4] =0;
				l1_point[5] =0;
				l1_point[6] =0;
				l1_point[7] =0;
				l1_point[8] =0;
			}
		}
	}
	if(m_x>530 && m_x<554 && m_y>350 && m_y<=375 || options==true)
	{
		options =true;
		iShowImage(195, 100, 201,215, img_ld_1[10]);
		if(m_x>230 && m_x<360 && m_y>245 && m_y<=270)//resume
		{
			options =false;
			m_x=m_y=0;
		}
		if(m_x>230 && m_x<360 && m_y>190 && m_y<=220)//restart
		{
			options =false;
			ch_x=0;
			l1_score=0;
			l1_life=3;
			l1_f[0]=0;
			l1_f[1]=0;
			l1_f[2]=0;
			l1_point[0] =0;
			l1_point[1] =0;
			l1_point[2] =0;
			l1_point[3] =0;
			l1_point[4] =0;
			l1_point[5] =0;
			l1_point[6] =0;
			l1_point[7] =0;
			l1_point[8] =0;
			m_x=m_y=0;
		}
		if(m_x>230 && m_x<360 && m_y>140 && m_y<=170)//back
		{
			options =false;
			dif_sel_op=1;
			sel_lev=0;
			ch_x=0;
			l1_score=0;
			l1_life=3;
			l1_f[0]=0;
			l1_f[1]=0;
			l1_f[2]=0;
			l1_point[0] =0;
			l1_point[1] =0;
			l1_point[2] =0;
			l1_point[3] =0;
			l1_point[4] =0;
			l1_point[5] =0;
			l1_point[6] =0;
			l1_point[7] =0;
			l1_point[8] =0;
			m_x=m_y=0;
		}
	}
	if(l1_life==0)
	{
		lev_cmplt =true;
		iShowImage(175, 140, 260, 158, img_ld_1[11]);
		if(m_x>250 && m_x<360 && m_y>170 && m_y<200)
		{
			l1_life=3;
			dif_sel_op=1;
			sel_lev=0;
			ch_x=0;
			l1_score=0;
			l1_f[0]=0;
			l1_f[1]=1;
			l1_f[2]=1;
			l1_point[0] =0;
			l1_point[1] =0;
			l1_point[2] =0;
			l1_point[3] =0;
			l1_point[4] =0;
			l1_point[5] =0;
			l1_point[6] =0;
			l1_point[7] =0;
			l1_point[8] =0;
		}
	}
	character_move();
}

/*________________________________________________Level 2 Screen________________________________________________*/

int lv2_x[20], lv2_y[20],img_ld_2[20] ;
int l2_f[5]={0,0};
int l2_point[10]={0,0};
int l2_life=3;

void l2_screen()
{
	char points[10], life[5];
	lev_cmplt=false;

	/*________________________________________________Screen 1________________________________________________*/

	if(l2_f[0]==0)
	{
		iShowImage(0, 0, 600,400,img_ld_2[0]);
		iShowImage(lv2_x[0], lv2_y[0],92,22,img_ld_2[1]);
		iShowImage(lvl_x[1], lvl_y[1],24,25,img_ld_1[2]);
		iShowImage(lvl_x[2], lvl_y[2],28,22,img_ld_1[3]);
		itoa(l2_life, life, 10);
		iSetColor(255,0,0);
		iText(lvl_x[3],lvl_y[3], life, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(lvl_x[3]+15,lvl_y[3], "x", GLUT_BITMAP_TIMES_ROMAN_24);
		itoa(l2_score, points ,10);
		iText(247, 340, "POINTS:", GLUT_BITMAP_9_BY_15);
		iText(310, 340, points, GLUT_BITMAP_9_BY_15);

		if(l2_point[0]==0)iShowImage(lv2_x[1], lv2_y[1],20,20,img_ld_1[4]);
		if((ch_y+25>= lv2_y[1] && ch_y+25<= lv2_y[1]+20) && (ch_x+20>= lv2_x[1] && ch_x+20<= lv2_x[1]+20) || (ch_y+25>= lv2_y[1] && ch_y+25<= lv2_y[1]+20) && (ch_x+10>= lv2_x[1] && ch_x+5<= lv2_x[1]+20))
		{
			if(l2_point[0]==0)l2_score +=10;
			l2_point[0]=1;
		}

		if(l2_point[1]==0)iShowImage(lv2_x[2], lv2_y[2],20,20,img_ld_1[4]);
		if((ch_y+25>= lv2_y[2] && ch_y+25<= lv2_y[2]+20) && (ch_x+20>= lv2_x[2] && ch_x+20<= lv2_x[2]+20) || (ch_y+25>= lv2_y[2] && ch_y+25<= lv2_y[2]+20) && (ch_x+10>= lv2_x[2] && ch_x+5<= lv2_x[2]+20))
		{
			if(l2_point[1]==0)l2_score +=10;
			l2_point[1]=1;
		}

		if(l2_point[2]==0)iShowImage(lv2_x[3], lv2_y[3],20,20,img_ld_1[4]);
		if((ch_y+25>= lv2_y[3] && ch_y+25<= lv2_y[3]+20) && (ch_x+20>= lv2_x[3] && ch_x+20<= lv2_x[3]+20) || (ch_y+25>= lv2_y[3] && ch_y+25<= lv2_y[3]+20) && (ch_x+10>= lv2_x[3] && ch_x+5<= lv2_x[3]+20))
		{
			if(l2_point[2]==0)l2_score +=10;
			l2_point[2]=1;
		}

		iShowImage(lv2_x[4], lv2_y[4],62,14,img_ld_1[7]);
		if( ch_x+10>=lv2_x[4]+5 && ch_x+12<=lv2_x[4]+58 && ch_y==lv2_y[4]+10)
		{
			jumpDown=false;
			jump=false;
		}
		else if( ch_x+10>=lv2_x[5]+5 && ch_x+12<=lv2_x[5]+58 && ch_y==lv2_y[5]+10)
		{
			jumpDown=false;
			jump=false;
		}
		else
		{
			jumpDown =true;
		}
		iShowImage(lv2_x[5], lv2_y[5],62,14,img_ld_1[7]);


		if(ch_x+20>=465 && ch_x<=500 && ch_y>=50 && ch_y<=73)
		{
			l2_life--;
			jumpUp=false;
			jumpDown=false;
			rotate =false;
			ch_x=0;
		}


		if(ch_x>=590)
		{
			ch_x=0;
			l2_f[0]=1;
			l2_f[1]=1;
		}
	}
	/*________________________________________________Screen 2________________________________________________*/
	else if(l2_f[1]==1)
	{
		iShowImage(0, 0, 600,400,img_ld_2[2]);
		iShowImage(lv2_x[0], lv2_y[0],92,22,img_ld_2[1]);
		iShowImage(lvl_x[1], lvl_y[1],24,25,img_ld_1[2]);
		iShowImage(lvl_x[2], lvl_y[2],28,22,img_ld_1[3]);
		itoa(l2_life, life, 10);
		iSetColor(255,0,0);
		iText(lvl_x[3],lvl_y[3], life, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(lvl_x[3]+15,lvl_y[3], "x", GLUT_BITMAP_TIMES_ROMAN_24);
		itoa(l2_score, points ,10);
		iText(247, 340, "POINTS:", GLUT_BITMAP_9_BY_15);
		iText(310, 340, points, GLUT_BITMAP_9_BY_15);

		if(l2_point[3]==0)iShowImage(lv2_x[6], lv2_y[6],20,20,img_ld_1[4]);
		if((ch_y+25>= lv2_y[6] && ch_y+25<= lv2_y[6]+20) && (ch_x+20>= lv2_x[6] && ch_x+20<= lv2_x[6]+20) || (ch_y+25>= lv2_y[6] && ch_y+25<= lv2_y[6]+20) && (ch_x+10>= lv2_x[6] && ch_x+5<= lv2_x[6]+20))
		{
			if(l2_point[3]==0)l2_score +=10;
			l2_point[3]=1;
		}

		if(l2_point[4]==0)iShowImage(lv2_x[7], lv2_y[7],20,20,img_ld_1[4]);
		if((ch_y+25>= lv2_y[7] && ch_y+25<= lv2_y[7]+20) && (ch_x+20>= lv2_x[7] && ch_x+20<= lv2_x[7]+20) || (ch_y+25>= lv2_y[7] && ch_y+25<= lv2_y[7]+20) && (ch_x+10>= lv2_x[7] && ch_x+5<= lv2_x[7]+20))
		{
			if(l2_point[4]==0)l2_score +=10;
			l2_point[4]=1;
		}

		if(l2_point[5]==0)iShowImage(lv2_x[8], lv2_y[8],20,20,img_ld_1[4]);
		if((ch_y+25>= lv2_y[8] && ch_y+25<= lv2_y[8]+20) && (ch_x+20>= lv2_x[8] && ch_x+20<= lv2_x[8]+20) || (ch_y+25>= lv2_y[8] && ch_y+25<= lv2_y[8]+20) && (ch_x+10>= lv2_x[8] && ch_x+5<= lv2_x[8]+20))
		{
			if(l2_point[5]==0)l2_score +=10;
			l2_point[5]=1;
		}

		iShowImage(lv2_x[9], lv2_y[9],62,14,img_ld_1[7]);
		iShowImage(lv2_x[10], lv2_y[10],62,14,img_ld_1[7]);
		iShowImage(lv2_x[11], lv2_y[11],62,14,img_ld_1[7]);
		if( ch_x+10>=lv2_x[9]+5 && ch_x+12<=lv2_x[9]+58 && ch_y==lv2_y[9]+10)
		{
			jumpDown=false;
			jump=false;
		}
		else if( ch_x+10>=lv2_x[10]+5 && ch_x+12<=lv2_x[10]+58 && ch_y==lv2_y[10]+10)
		{
			jumpDown=false;
			jump=false;
		}
		else if( ch_x+10>=lv2_x[11]+5 && ch_x+12<=lv2_x[11]+58 && ch_y==lv2_y[11]+10)
		{
			jumpDown=false;
			jump=false;
		}
		else
		{
			jumpDown =true;
		}

		if(ch_x+20>=280 && ch_x<=325 && ch_y>=50 && ch_y<=73)
		{
			l2_life--;
			jumpUp=false;
			jumpDown=false;
			rotate =false;
			ch_x=0;
		}

		if(ch_x+8>=100 && ch_x+20<=145 && ch_y>=0 && ch_y<=70)//hole
		{
			rotate = false;
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l1_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
			}
		}
		if(ch_x+8>=463 && ch_x+20<=511 && ch_y>=0 && ch_y<=70)//hole
		{
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l1_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
				rotate = false;
			}
		}
		if(ch_x>=590)
		{
			ch_x=0;
			l2_f[0]=1;
			l2_f[1]=0;
			l2_f[2]=1;
		}
	}

	/*________________________________________________Screen 3________________________________________________*/
	else if(l2_f[2]==1)
	{
		scn_change = false;
		iShowImage(0, 0, 600,400,img_ld_2[3]);
		iShowImage(lv2_x[0], lv2_y[0],92,22,img_ld_2[1]);
		iShowImage(lvl_x[1], lvl_y[1],24,25,img_ld_1[2]);
		iShowImage(lvl_x[2], lvl_y[2],28,22,img_ld_1[3]);
		iShowImage(575, 55, 26, 32, img_ld_1[8]);
		itoa(l2_life, life, 10);
		iSetColor(255,0,0);
		iText(lvl_x[3],lvl_y[3], life, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(lvl_x[3]+15,lvl_y[3], "x", GLUT_BITMAP_TIMES_ROMAN_24);
		itoa(l2_score, points ,10);
		iText(247, 340, "POINTS:", GLUT_BITMAP_9_BY_15);
		iText(310, 340, points, GLUT_BITMAP_9_BY_15);

		if(l2_point[6]==0)iShowImage(lv2_x[12], lv2_y[12],20,20,img_ld_1[4]);
		if((ch_y+25>= lv2_y[12] && ch_y+25<= lv2_y[12]+20) && (ch_x+20>= lv2_x[12] && ch_x+20<= lv2_x[12]+20) || (ch_y+25>= lv2_y[12] && ch_y+25<= lv2_y[12]+20) && (ch_x+10>= lv2_x[12] && ch_x+5<= lv2_x[12]+20))
		{
			if(l2_point[6]==0)l2_score +=10;
			l2_point[6]=1;
		}

		if(l2_point[7]==0)iShowImage(lv2_x[13], lv2_y[13],20,20,img_ld_1[4]);
		if((ch_y+25>= lv2_y[13] && ch_y+25<= lv2_y[13]+20) && (ch_x+20>= lv2_x[13] && ch_x+20<= lv2_x[13]+20) || (ch_y+25>= lv2_y[13] && ch_y+25<= lv2_y[13]+20) && (ch_x+10>= lv2_x[13] && ch_x+5<= lv2_x[13]+20))
		{
			if(l2_point[7]==0)l2_score +=10;
			l2_point[7]=1;
		}

		if(l2_point[8]==0)iShowImage(lv2_x[14], lv2_y[14],20,20,img_ld_1[4]);
		if((ch_y+25>= lv2_y[14] && ch_y+25<= lv2_y[14]+20) && (ch_x+20>= lv2_x[14] && ch_x+20<= lv2_x[14]+20) || (ch_y+25>= lv2_y[14] && ch_y+25<= lv2_y[14]+20) && (ch_x+10>= lv2_x[14] && ch_x+5<= lv2_x[14]+20))
		{
			if(l2_point[8]==0)l2_score +=10;
			l2_point[8]=1;
		}

		iShowImage(lv2_x[15], lv2_y[15],62,14,img_ld_1[7]);//floats
		iShowImage(lv2_x[16], lv2_y[16],62,14,img_ld_1[7]);
		if( ch_x+10>=lv2_x[15]+5 && ch_x+12<=lv2_x[15]+58 && ch_y==lv2_y[15]+10)
		{
			jumpDown=false;
			jump=false;
		}
		else if( ch_x+10>=lv2_x[16]+5 && ch_x+12<=lv2_x[16]+58 && ch_y==lv2_y[16]+10)
		{
			jumpDown=false;
			jump=false;
		}
		else
		{
			jumpDown =true;
		}


		if(ch_x+8>=100 && ch_x+20<=145 && ch_y>=0 && ch_y<=70)//hole
		{
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l2_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
				rotate = false;
			}
		}
		if(ch_x+8>=463 && ch_x+20<=511 && ch_y>=0 && ch_y<=70)//hole
		{
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l2_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
				rotate = false;
			}
		}
		if(ch_x>=570)
		{
			if(l2_f[4]==0)
			{
				l2_score+=10;
				FILE *print_score = fopen("database\\level scores.txt", "w");
				if(dif_sel_op==1)
				{
					ps[i_flag].score2=l2_score;
				}
				else if(dif_sel_op==2)
				{
					psmed[i_flag].score2=l2_score;
				}
				else if(dif_sel_op==3)
				{
					pshard[i_flag].score2=l2_score;
				}
				for(int i=0; i<users;i++)
				{
					fprintf(print_score, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", ps[i].name, ps[i].score1,ps[i].score2,ps[i].score3,ps[i].score4,ps[i].score5, psmed[i].score1,psmed[i].score2,psmed[i].score3,psmed[i].score4,psmed[i].score5,pshard[i].score1,pshard[i].score2,pshard[i].score3,pshard[i].score4,pshard[i].score5);
					printf("%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", ps[i].name, ps[i].score1,ps[i].score2,ps[i].score3,ps[i].score4,ps[i].score5, psmed[i].score1,psmed[i].score2,psmed[i].score3,psmed[i].score4,psmed[i].score5,pshard[i].score1,pshard[i].score2,pshard[i].score3,pshard[i].score4,pshard[i].score5);
				}
				fclose(print_score);
				l2_f[4]=1;
			}

			iShowImage(170, 150, 247, 138, img_ld_1[9]);
			lev_cmplt = true;
			if(m_x>265 && m_x<340 && m_y>170 && m_y<190)
			{
				dif_sel_op=1;
				sel_lev=0;
				ch_x=0;
				l2_life = 3;
				l2_f[0]=0;
				l2_f[1]=0;
				l2_f[2]=0;
				l2_point[0] =0;
				l2_point[1] =0;
				l2_point[2] =0;
				l2_point[3] =0;
				l2_point[4] =0;
				l2_point[5] =0;
				l2_point[6] =0;
				l2_point[7] =0;
				l2_point[8] =0;
			}
		}
	}
	if(m_x>530 && m_x<554 && m_y>350 && m_y<=375 || options==true)
	{
		options =true;
		iShowImage(195, 100, 201,215, img_ld_1[10]);
		if(m_x>230 && m_x<360 && m_y>245 && m_y<=270)//resume
		{
			options =false;
			m_x=m_y=0;
		}
		if(m_x>230 && m_x<360 && m_y>190 && m_y<=220)//restart
		{
			options =false;
			ch_x=0;
			l2_life = 3;
			l2_score=0;
			l2_f[0]=0;
			l2_f[1]=0;
			l2_f[2]=0;
			l2_point[0] =0;
			l2_point[1] =0;
			l2_point[2] =0;
			l2_point[3] =0;
			l2_point[4] =0;
			l2_point[5] =0;
			l2_point[6] =0;
			l2_point[7] =0;
			l2_point[8] =0;
			m_x=m_y=0;
		}
		if(m_x>230 && m_x<360 && m_y>140 && m_y<=170)//back
		{
			options =false;
			dif_sel_op=1;
			sel_lev=0;
			ch_x=0;
			l2_life=3;
			l2_score=0;
			l2_f[0]=0;
			l2_f[1]=0;
			l2_f[2]=0;
			l2_point[0] =0;
			l2_point[1] =0;
			l2_point[2] =0;
			l2_point[3] =0;
			l2_point[4] =0;
			l2_point[5] =0;
			l2_point[6] =0;
			l2_point[7] =0;
			l2_point[8] =0;
			m_x=m_y=0;
		}
	}
	if(l2_life==0)
	{
		lev_cmplt =true;
		iShowImage(175, 140, 260, 158, img_ld_1[11]);
		if(m_x>250 && m_x<360 && m_y>170 && m_y<200)
		{
			dif_sel_op=1;
			sel_lev=0;
			ch_x=0;
			l2_life=3;
			l2_score=0;
			l2_f[0]=0;
			l2_f[1]=0;
			l2_f[2]=0;
			l2_point[0] =0;
			l2_point[1] =0;
			l2_point[2] =0;
			l2_point[3] =0;
			l2_point[4] =0;
			l2_point[5] =0;
			l2_point[6] =0;
			l2_point[7] =0;
			l2_point[8] =0;

		}
	}
	character_move();
}

void l2_position()
{
	lv2_x[0]=245;lv2_y[0]=355;
	lv2_x[1]=150;lv2_y[1]=160;
	lv2_x[2]=335;lv2_y[2]=160;
	lv2_x[3]=480;lv2_y[3]=120;
	lv2_x[4]=135; lv2_y[4]=125;
	lv2_x[5]=320;lv2_y[5]=125;
	lv2_x[6]=110;lv2_y[6]=155;
	lv2_x[7]=295;lv2_y[7]=165;
	lv2_x[8]=470;lv2_y[8]=145;
	lv2_x[9]=280;lv2_y[9]=125;
	lv2_x[10]=95;lv2_y[10]=110;
	lv2_x[11]=455;lv2_y[11]=110;
	lv2_x[12]=110;lv2_y[12]=160;
	lv2_x[13]=475;lv2_y[13]=160;
	lv2_x[14]=285;lv2_y[14]=120;
	lv2_x[15]=95;lv2_y[15]=110;
	lv2_x[16]=455;lv2_y[16]=110;

}

void l2_img_ld()
{
	img_ld_2[0]= iLoadImage("Level 2\\Lvl2(1)-01.png");
	img_ld_2[1]= iLoadImage("Level 2\\Lvl_2_icon.png");
	img_ld_2[2]= iLoadImage("Level 2\\Lvl2(2)-01.png");
	img_ld_2[3]= iLoadImage("Level 2\\Lvl2(3)-01.png");

}


/*________________________________________________Level 3 Screen________________________________________________*/

int lv3_x[20], lv3_y[20],img_ld_3[20] ;
int l3_f[5]={0,0};
int l3_point[10]={0,0};
int l3_life=3;


void l3_screen()
{
	/*_______________________________________________Screen 1_______________________________________________*/
	char points[10], life[5];
	lev_cmplt=false;

	if(l3_f[0]==0)
	{
		iShowImage(0, 0, 600,400,img_ld_3[0]);
		iShowImage(lv3_x[0], lv3_y[0],93,23,img_ld_3[1]);
		iShowImage(lvl_x[1], lvl_y[1],24,25,img_ld_1[2]);
		iShowImage(lvl_x[2], lvl_y[2],28,22,img_ld_1[3]);
		itoa(l3_life, life, 10);
		iSetColor(255,0,0);
		iText(lvl_x[3],lvl_y[3], life, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(lvl_x[3]+15,lvl_y[3], "x", GLUT_BITMAP_TIMES_ROMAN_24);
		itoa(l3_score, points ,10);
		iText(247, 340, "POINTS:", GLUT_BITMAP_9_BY_15);
		iText(310, 340, points, GLUT_BITMAP_9_BY_15);

		if(l3_point[0]==0)iShowImage(lv3_x[1], lv3_y[1],20,20,img_ld_1[4]);
		if((ch_y+25>= lv3_y[1] && ch_y+25<= lv3_y[1]+20) && (ch_x+20>= lv3_x[1] && ch_x+20<= lv3_x[1]+20) || (ch_y+25>= lv3_y[1] && ch_y+25<= lv3_y[1]+20) && (ch_x+10>= lv3_x[1] && ch_x+5<= lv3_x[1]+20))
		{
			if(l3_point[0]==0)l3_score +=10;
			l3_point[0]=1;
		}
		if(l3_point[1]==0)iShowImage(lv3_x[2], lv3_y[2],20,20,img_ld_1[4]);
		if((ch_y+25>= lv3_y[2] && ch_y+25<= lv3_y[2]+20) && (ch_x+20>= lv3_x[2] && ch_x+20<= lv3_x[2]+20) || (ch_y+25>= lv3_y[2] && ch_y+25<= lv3_y[2]+20) && (ch_x+10>= lv3_x[2] && ch_x+5<= lv3_x[2]+20))
		{
			if(l3_point[1]==0)l3_score +=10;
			l3_point[1]=1;
		}

		if(l3_point[2]==0)iShowImage(lv3_x[3], lv3_y[3],20,20,img_ld_1[4]);
		if((ch_y+25>= lv3_y[3] && ch_y+25<= lv3_y[3]+20) && (ch_x+20>= lv3_x[3] && ch_x+20<= lv3_x[3]+20) || (ch_y+25>= lv3_y[3] && ch_y+25<= lv3_y[3]+20) && (ch_x+10>= lv3_x[3] && ch_x+5<= lv3_x[3]+20))
		{
			if(l3_point[2]==0)l3_score +=10;
			l3_point[2]=1;
		}
		iShowImage(lv3_x[4], lv3_y[4],62,14,img_ld_1[7]);
		if(ch_x+10>=lv3_x[4]+5 && ch_x+12<=lv3_x[4]+58 && ch_y==lv3_y[4]+10)
		{
			jumpDown=false;
			jump=false;
		}
		else if(ch_x+10>=lv3_x[5]+5 && ch_x+12<=lv3_x[5]+58 && ch_y==lv3_y[5]+10)
		{
			jumpDown=false;
			jump=false;
		}	
		else if(ch_x+10>=lv3_x[6]+5 && ch_x+12<=lv3_x[6]+58 && ch_y==lv3_y[6]+10)
		{
			jumpDown=false;
			jump=false;
		}
		else 
			jumpDown=true;  

		iShowImage(lv3_x[5], lv3_y[5],62,14,img_ld_1[7]);
		iShowImage(lv3_x[6], lv3_y[6],62,14,img_ld_1[7]);
		if(((ch_x+8>=100 && ch_x+8<=145) && (ch_y>=0 && ch_y<=70))||((ch_x+8>=465 && ch_x+8<=510) && (ch_y>=0 && ch_y<=70)))//hole
		{
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l3_life--;
				ch_x=0;
				ch_y=55;
				jumpDown= true;
				rotate = false;
			}
		}

		if(ch_x>=590)
		{
			ch_x=0;
			l3_f[0]=1;
			l3_f[1]=1;
		}
	}
	/*_______________________________________________Screen 2_______________________________________________*/
	else if(l3_f[1]==1)
	{

		iShowImage(0, 0, 600,400,img_ld_3[2]);
		iShowImage(lv3_x[0], lv3_y[0],93,23,img_ld_3[1]);
		iShowImage(lvl_x[1], lvl_y[1],24,25,img_ld_1[2]);
		iShowImage(lvl_x[2], lvl_y[2],28,22,img_ld_1[3]);
		itoa(l3_life, life, 10);
		iSetColor(255,0,0);
		iText(lvl_x[3],lvl_y[3], life, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(lvl_x[3]+15,lvl_y[3], "x", GLUT_BITMAP_TIMES_ROMAN_24);
		itoa(l3_score, points ,10);
		iText(247, 340, "POINTS:", GLUT_BITMAP_9_BY_15);
		iText(310, 340, points, GLUT_BITMAP_9_BY_15);

		if(l3_point[3]==0)iShowImage(lv3_x[12], lv3_y[12],20,20,img_ld_1[4]);
		if((ch_y+25>= lv3_y[12] && ch_y+25<= lv3_y[121]+20) && (ch_x+20>= lv3_x[12] && ch_x+20<= lv3_x[12]+20) || (ch_y+25>= lv3_y[12] && ch_y+25<= lv3_y[12]+20) && (ch_x+10>= lv3_x[12] && ch_x+5<= lv3_x[12]+20))
		{
			if(l3_point[3]==0)l3_score +=10;
			l3_point[3]=1;
		}
		if(l3_point[4]==0)iShowImage(lv3_x[13], lv3_y[13],20,20,img_ld_1[4]);
		if((ch_y+25>= lv3_y[13] && ch_y+25<= lv3_y[13]+20) && (ch_x+20>= lv3_x[13] && ch_x+20<= lv3_x[13]+20) || (ch_y+25>= lv3_y[13] && ch_y+25<= lv3_y[13]+20) && (ch_x+10>= lv3_x[13] && ch_x+5<= lv3_x[13]+20))
		{
			if(l3_point[4]==0)l3_score +=10;
			l3_point[4]=1;
		}
		if(l3_point[5]==0)iShowImage(lv3_x[14], lv3_y[14],20,20,img_ld_1[4]);
		if((ch_y+25>= lv3_y[14] && ch_y+25<= lv3_y[14]+20) && (ch_x+20>= lv3_x[14] && ch_x+20<= lv3_x[14]+20) || (ch_y+25>= lv3_y[14] && ch_y+25<= lv3_y[14]+20) && (ch_x+10>= lv3_x[14] && ch_x+5<= lv3_x[14]+20))
		{
			if(l3_point[5]==0)l3_score +=10;			
			l3_point[5]=1;
		}
		iShowImage(lv3_x[15], lv3_y[15],62,14,img_ld_1[7]);
		if(ch_x+10>=lv3_x[15]+5 && ch_x+12<=lv3_x[15]+58 && ch_y==lv3_y[15]+10)
		{
			jumpDown=false;
			jump=false;
		}	
		else if(ch_x+10>=lv3_x[16]+5 && ch_x+12<=lv3_x[16]+58 && ch_y==lv3_y[16]+10)
		{
			jumpDown=false;
			jump=false;
		}	
		else if(ch_x+10>=lv3_x[17]+5 && ch_x+12<=lv3_x[17]+58 && ch_y==lv3_y[17]+10)
		{
			jumpDown=false;
			jump=false;
		}
		else 
			jumpDown=true;

		iShowImage(lv3_x[16], lv3_y[16],62,14,img_ld_1[7]);
		iShowImage(lv3_x[17], lv3_y[17],62,14,img_ld_1[7]);

		if(((ch_x+8>=100 && ch_x+8<=145) && (ch_y>=0 && ch_y<=70)) || ((ch_x+8>=465 && ch_x+8<=510) && (ch_y>=0 && ch_y<=70)) || ((ch_x>=270 && ch_x+20<=318) && (ch_y>=0 && ch_y<=70)))//hole
		{
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l3_life--;
				ch_x=0;
				ch_y=55;
				jumpDown= true;
				rotate = false;
			}
		}

		if(ch_x>=590)
		{
			ch_x=0;
			l3_f[1]=0;
			l3_f[2]=1;
		}
	}

	/*_______________________________________________Screen 3_______________________________________________*/
	else if(l3_f[2]==1)
	{
		iShowImage(0, 0, 600,400,img_ld_3[3]);
		iShowImage(lv3_x[0], lv3_y[0],93,23,img_ld_3[1]);
		iShowImage(lvl_x[1], lvl_y[1],24,25,img_ld_1[2]);
		iShowImage(lvl_x[2], lvl_y[2],28,22,img_ld_1[3]);
		iShowImage(575, 55, 26, 32, img_ld_1[8]);
		itoa(l3_life, life, 10);
		iSetColor(255,0,0);
		iText(lvl_x[3],lvl_y[3], life, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(lvl_x[3]+15,lvl_y[3], "x", GLUT_BITMAP_TIMES_ROMAN_24);
		itoa(l3_score, points ,10);
		iText(247, 340, "POINTS:", GLUT_BITMAP_9_BY_15);
		iText(310, 340, points, GLUT_BITMAP_9_BY_15);

		if(l3_point[6]==0)iShowImage(lv3_x[7], lv3_y[7],20,20,img_ld_1[4]);
		if((ch_y+25>= lv3_y[7] && ch_y+25<= lv3_y[7]+20) && (ch_x+20>= lv3_x[7] && ch_x+20<= lv3_x[7]+20) || (ch_y+25>= lv3_y[7] && ch_y+25<= lv3_y[7]+20) && (ch_x+10>= lv3_x[7] && ch_x+5<= lv3_x[7]+20))
		{
			if(l3_point[6]==0)l3_score +=10;
			l3_point[6]=1;
		}
		if(l3_point[7]==0)iShowImage(lv3_x[8], lv3_y[8],20,20,img_ld_1[4]);
		if((ch_y+25>= lv3_y[8] && ch_y+25<= lv3_y[8]+20) && (ch_x+20>= lv3_x[8] && ch_x+20<= lv3_x[8]+20) || (ch_y+25>= lv3_y[8] && ch_y+25<= lv3_y[8]+20) && (ch_x+10>= lv3_x[8] && ch_x+5<= lv3_x[8]+20))
		{
			if(l3_point[7]==0)l3_score +=10;
			l3_point[7]=1;
		}
		if(l3_point[8]==0)iShowImage(lv3_x[9], lv3_y[9],20,20,img_ld_1[4]);
		if((ch_y+25>= lv3_y[9] && ch_y+25<= lv3_y[9]+20) && (ch_x+20>= lv3_x[9] && ch_x+20<= lv3_x[9]+20) || (ch_y+25>= lv3_y[9] && ch_y+25<= lv3_y[9]+20) && (ch_x+10>= lv3_x[9] && ch_x+5<= lv3_x[+9]+20))
		{
			if(l3_point[8]==0)l3_score +=10;
			l3_point[8]=1;
		}
		iShowImage(lv3_x[10], lv3_y[10],62,14,img_ld_1[7]);
		if(ch_x+10>=lv3_x[10]+5 && ch_x+12<=lv3_x[10]+58 && ch_y==lv3_y[10]+10)
		{
			jumpDown=false;
			jump=false;
		}	
		else if(ch_x+10>=lv3_x[5]+5 && ch_x+12<=lv3_x[5]+58 && ch_y==lv3_y[5]+10)
		{
			jumpDown=false;
			jump=false;
		}	
		else 
			jumpDown=true;
		iShowImage(lv3_x[5], lv3_y[5],62,14,img_ld_1[7]);

		if(((ch_x+20>=66 && ch_x<=106) && (ch_y>=50 && ch_y<=77)) ||((ch_x+20>=200 && ch_x<=235) && (ch_y>=50 && ch_y<=77)))
		{
			l3_life--;
			jumpUp=false;
			jumpDown=false;
			rotate =false;
			ch_x=0;
		}
		if(((ch_x+8>=317 && ch_x+8<=365) && (ch_y>=0 && ch_y<=70)) || ((ch_x+8>=470 && ch_x+8<=520) && (ch_y>=0 && ch_y<=70)))//hole
		{
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l3_life--;
				ch_x=0;
				ch_y=55;
				jumpDown= true;
				rotate = false;
			}
		}
		if(ch_x>=570)
		{
			if(l3_f[4]==0)
			{
				l3_score+=10;
				FILE *print_score = fopen("database\\level scores.txt", "w");
				if(dif_sel_op==1)
				{
					ps[i_flag].score3=l3_score;
				}
				else if(dif_sel_op==2)
				{
					psmed[i_flag].score3=l3_score;
				}
				else if(dif_sel_op==3)
				{
					pshard[i_flag].score3=l3_score;
				}
				for(int i=0; i<users;i++)
				{
					fprintf(print_score, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", ps[i].name, ps[i].score1,ps[i].score2,ps[i].score3,ps[i].score4,ps[i].score5, psmed[i].score1,psmed[i].score2,psmed[i].score3,psmed[i].score4,psmed[i].score5,pshard[i].score1,pshard[i].score2,pshard[i].score3,pshard[i].score4,pshard[i].score5);
					printf("%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", ps[i].name, ps[i].score1,ps[i].score2,ps[i].score3,ps[i].score4,ps[i].score5, psmed[i].score1,psmed[i].score2,psmed[i].score3,psmed[i].score4,psmed[i].score5,pshard[i].score1,pshard[i].score2,pshard[i].score3,pshard[i].score4,pshard[i].score5);
				}
				fclose(print_score);
				l3_f[4]=1;

			}
			iShowImage(170, 150, 247, 138, img_ld_1[9]);
			lev_cmplt = true; 
			if(m_x>265 && m_x<340 && m_y>170 && m_y<190)
			{
				dif_sel_op=1;
				sel_lev=0;
				ch_x=0;
				l3_life = 3;
				l3_f[0]=0;
				l3_f[1]=0;
				l3_f[2]=0;
				l3_point[0] =0;
				l3_point[1] =0;
				l3_point[2] =0;
				l3_point[3] =0;
				l3_point[4] =0;
				l3_point[5] =0;
				l3_point[6] =0;
				l3_point[7] =0;
				l3_point[8] =0;
			}
		}
	}
	if(m_x>530 && m_x<554 && m_y>350 && m_y<=375 || options==true)
	{
		options =true;
		iShowImage(195, 100, 201,215, img_ld_1[10]);
		if(m_x>230 && m_x<360 && m_y>245 && m_y<=270)//resume
		{
			options =false;
			m_x=m_y=0;
		}
		if(m_x>230 && m_x<360 && m_y>190 && m_y<=220)//restart
		{
			options =false;
			ch_x=0;
			l3_life = 3;
			l3_score=0;
			l3_f[0]=0;
			l3_f[1]=0;
			l3_f[2]=0;
			l3_point[0] =0;
			l3_point[1] =0;
			l3_point[2] =0;
			l3_point[3] =0;
			l3_point[4] =0;
			l3_point[5] =0;
			l3_point[6] =0;
			l3_point[7] =0;
			l3_point[8] =0;
			m_x=m_y=0;
		}
		if(m_x>230 && m_x<360 && m_y>140 && m_y<=170)//back
		{
			options =false;
			dif_sel_op=1;
			sel_lev=0;
			ch_x=0;
			l3_score=0;
			l3_life=3;
			l3_f[0]=0;
			l3_f[1]=0;
			l3_f[2]=0;
			l3_point[0] =0;
			l3_point[1] =0;
			l3_point[2] =0;
			l3_point[3] =0;
			l3_point[4] =0;
			l3_point[5] =0;
			l3_point[6] =0;
			l3_point[7] =0;
			l3_point[8] =0;
			m_x=m_y=0;
		}
	}
	if(l3_life==0)
	{
		lev_cmplt =true;
		iShowImage(175, 140, 260, 158, img_ld_1[11]);
		if(m_x>250 && m_x<360 && m_y>170 && m_y<200)
		{
			dif_sel_op=1;
			sel_lev=0;
			ch_x=0;
			l3_life=3;
			l3_score=0;
			l3_f[0]=0;
			l3_f[1]=0;
			l3_f[2]=0;
			l3_point[0] =0;
			l3_point[1] =0;
			l3_point[2] =0;
			l3_point[3] =0;
			l3_point[4] =0;
			l3_point[5] =0;
			l3_point[6] =0;
			l3_point[7] =0;
			l3_point[8] =0;

		}
	}
	character_move();
}

void l3_position()
{
	lv3_x[0]=245; lv3_y[0]=355;
	lv3_x[1]=lv3_x[12]=120; lv3_y[1]=lv3_y[12]=155;
	lv3_x[2]=lv3_x[13]=475; lv3_y[2]=lv3_y[13]=155;
	lv3_x[3]=lv3_x[14]=285; lv3_y[3]=lv3_y[14]=155;
	lv3_x[4]=lv3_x[15]=100; lv3_y[4]=lv3_y[15]=110;
	lv3_x[5]=lv3_x[16]=460; lv3_y[5]=lv3_y[16]=110;
	lv3_x[6]=lv3_x[17]=270; lv3_y[6]=lv3_y[17]=110;
	lv3_x[7]=145; lv3_y[7]=120;
	lv3_x[8]=335; lv3_y[8]=165;
	lv3_x[9]=475; lv3_y[9]=165;
	lv3_x[10]=320; lv3_y[10]=110;
	lv3_x[11]=270; lv3_y[11]=110;


}
void l3_img_ld()
{
	img_ld_3[0]=iLoadImage("Level 3\\Lvl3(1)-01.png");
	img_ld_3[1]=iLoadImage("Level 3\\Lvl_3_icon.png");
	img_ld_3[2]=iLoadImage("Level 3\\Lvl3(2)-01.png");
	img_ld_3[3]=iLoadImage("Level 3\\Lvl3(3)-01.png");

}

/*______________________________________________Level 4 Screen______________________________________________*/

int lv4_x[20], lv4_y[20],img_ld_4[20] ;
int l4_f[5]={0,0};
int l4_point[10]={0,0};
int l4_life=3;


void l4_screen()
{
	/*______________________________________________Screen 1______________________________________________*/

	char points[10], life[5];
	lev_cmplt=false;

	if(l4_f[0]==0)
	{
		iShowImage(0, 0, 600,400,img_ld_4[0]);
		iShowImage(lv4_x[0], lv4_y[0],93,23,img_ld_4[1]);
		iShowImage(lvl_x[1], lvl_y[1],24,25,img_ld_1[2]);
		iShowImage(lvl_x[2], lvl_y[2],28,22,img_ld_1[3]);
		itoa(l4_life, life, 10);
		iSetColor(255,0,0);
		iText(lvl_x[3],lvl_y[3], life, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(lvl_x[3]+15,lvl_y[3], "x", GLUT_BITMAP_TIMES_ROMAN_24);
		itoa(l4_score, points ,10);
		iText(247, 340, "POINTS:", GLUT_BITMAP_9_BY_15);
		iText(310, 340, points, GLUT_BITMAP_9_BY_15);

		if(l4_point[0]==0)iShowImage(lv4_x[1], lv4_y[1],20,20,img_ld_1[4]);
		if((ch_y+25>= lv4_y[1] && ch_y+25<= lv4_y[1]+20) && (ch_x+20>= lv4_x[1] && ch_x+20<= lv4_x[1]+20) || (ch_y+25>= lv4_y[1] && ch_y+25<= lv4_y[1]+20) && (ch_x+10>= lv4_x[1] && ch_x+5<= lv4_x[1]+20))
		{	
			if(l4_point[0]==0)l4_score +=10;
			l4_point[0]=1;		
		}

		if(l4_point[1]==0)iShowImage(lv4_x[2], lv4_y[2],20,20,img_ld_1[4]);
		if((ch_y+25>= lv4_y[2] && ch_y+25<= lv4_y[2]+20) && (ch_x+20>= lv4_x[2] && ch_x+20<= lv4_x[2]+20) || (ch_y+25>= lv4_y[2] && ch_y+25<= lv4_y[2]+20) && (ch_x+10>= lv4_x[2] && ch_x+5<= lv4_x[2]+20))
		{
			if(l4_point[1]==0)l4_score +=10;
			l4_point[1]=1;
		}
		if(l4_point[2]==0)iShowImage(lv4_x[3], lv4_y[3],20,20,img_ld_1[4]);
		if((ch_y+25>= lv4_y[3] && ch_y+25<= lv4_y[3]+20) && (ch_x+20>= lv4_x[3] && ch_x+20<= lv4_x[3]+20) || (ch_y+25>= lv4_y[3] && ch_y+25<= lv4_y[3]+20) && (ch_x+10>= lv4_x[3] && ch_x+5<= lv4_x[3]+20))
		{
			if(l4_point[2]==0)l4_score +=10;
			l4_point[2]=1;
		}

		iShowImage(lv4_x[4], lv4_y[4],62,14,img_ld_1[7]);
		if(ch_x+10>=lv4_x[4]+5 && ch_x+12<=lv4_x[4]+58 && ch_y==lv4_y[4]+10)
		{
			jumpDown=false;
			jump=false;
		}	
		else if(ch_x+10>=lv4_x[5]+5 && ch_x+12<=lv4_x[5]+58 && ch_y==lv4_y[5]+10)
		{
			jumpDown=false;
			jump=false;
		}
		else
			jumpDown=true;
		iShowImage(lv4_x[5], lv4_y[5],62,14,img_ld_1[7]);

		if((ch_x+20>=68 && ch_x<=105) && (ch_y>=50 && ch_y<=73))
		{
			l4_life--;
			jumpUp=false;
			jumpDown=false;
			rotate =false;
			ch_x=0;
		}

		if(ch_x+8>=320 && ch_x+20<=365 && ch_y>=0 && ch_y<=70)//hole
		{
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l1_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
				rotate = false;
			}
		}
		if(ch_x+8>=470 && ch_x+20<=518 && ch_y>=0 && ch_y<=70)//hole
		{
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l1_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
				rotate = false;
			}
		}
		if(ch_x>=590)
		{
			ch_x=0;
			l4_f[0]=1;
			l4_f[1]=1;
		}
	}
	/*______________________________________________Screen 2______________________________________________*/
	if(l4_f[1]==1)
	{

		iShowImage(0, 0, 600,400,img_ld_4[2]);
		iShowImage(lv4_x[0], lv4_y[0],93,23,img_ld_4[1]);
		iShowImage(lvl_x[1], lvl_y[1],24,25,img_ld_1[2]);
		iShowImage(lvl_x[2], lvl_y[2],28,22,img_ld_1[3]);
		itoa(l4_life, life, 10);
		iSetColor(255,0,0);
		iText(lvl_x[3],lvl_y[3], life, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(lvl_x[3]+15,lvl_y[3], "x", GLUT_BITMAP_TIMES_ROMAN_24);
		itoa(l4_score, points ,10);
		iText(247, 340, "POINTS:", GLUT_BITMAP_9_BY_15);
		iText(310, 340, points, GLUT_BITMAP_9_BY_15);

		if(l4_point[3]==0)iShowImage(lv4_x[12], lv4_y[12],20,20,img_ld_1[4]);
		if((ch_y+25>= lv4_y[12] && ch_y+25<= lv4_y[121]+20) && (ch_x+20>= lv4_x[12] && ch_x+20<= lv4_x[12]+20) || (ch_y+25>= lv4_y[12] && ch_y+25<= lv4_y[12]+20) && (ch_x+10>= lv4_x[12] && ch_x+5<= lv4_x[12]+20))
		{
			if(l4_point[3]==0)l4_score +=10;
			l4_point[3]=1;
		}

		if(l4_point[4]==0)iShowImage(lv4_x[13], lv4_y[13],20,20,img_ld_1[4]);
		if((ch_y+25>= lv4_y[13] && ch_y+25<= lv4_y[13]+20) && (ch_x+20>= lv4_x[13] && ch_x+20<= lv4_x[13]+20) || (ch_y+25>= lv4_y[13] && ch_y+25<= lv4_y[13]+20) && (ch_x+10>= lv4_x[13] && ch_x+5<= lv4_x[13]+20))
		{
			if(l4_point[4]==0)l4_score +=10;
			l4_point[4]=1;
		}

		if(l4_point[5]==0)iShowImage(lv4_x[14], lv4_y[14],20,20,img_ld_1[4]);
		if((ch_y+25>= lv4_y[14] && ch_y+25<= lv4_y[14]+20) && (ch_x+20>= lv4_x[14] && ch_x+20<= lv4_x[14]+20) || (ch_y+25>= lv4_y[14] && ch_y+25<= lv4_y[14]+20) && (ch_x+10>= lv4_x[14] && ch_x+5<= lv4_x[14]+20))
		{
			if(l4_point[5]==0)l4_score +=10;
			l4_point[5]=1;
		}

		iShowImage(lv4_x[15], lv4_y[15],62,14,img_ld_1[7]);
		if(ch_x+10>=lv4_x[15]+5 && ch_x+12<=lv4_x[15]+58 && ch_y==lv4_y[15]+10)
		{
			jumpDown=false;
			jump=false;
		}	
		else if(ch_x+10>=lv4_x[16]+5 && ch_x+12<=lv4_x[16]+58 && ch_y==lv4_y[16]+10)
		{
			jumpDown=false;
			jump=false;
		}	
		else if(ch_x+10>=lv4_x[17]+5 && ch_x+12<=lv4_x[17]+58 && ch_y==lv4_y[17]+10)
		{
			jumpDown=false;
			jump=false;
		}
		else 
			jumpDown= true;

		iShowImage(lv4_x[16], lv3_y[16],62,14,img_ld_1[7]);
		iShowImage(lv4_x[17], lv4_y[17],62,14,img_ld_1[7]);

		if(ch_x+8>=55 && ch_x+20<=100 && ch_y>=0 && ch_y<=70)//hole
		{
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l1_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
				rotate = false;
			}
		}
		if(ch_x+8>=318 && ch_x+20<=364 && ch_y>=0 && ch_y<=70)//hole
		{
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l1_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
				rotate = false;
			}
		}
		if(ch_x+8>=470 && ch_x+20<=517 && ch_y>=0 && ch_y<=70)//hole
		{
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l1_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
				rotate = false;
			}
		}
		if(ch_x>=590)
		{
			ch_x=0;
			l4_f[1]=0;
			l4_f[2]=1;
		}
	}

	/*______________________________________________Screen 3______________________________________________*/
	if(l4_f[2]==1)
	{
		iShowImage(0, 0, 600,400,img_ld_4[3]);
		iShowImage(lv4_x[0], lv4_y[0],92,22,img_ld_4[1]);
		iShowImage(lvl_x[1], lvl_y[1],24,25,img_ld_1[2]);
		iShowImage(lvl_x[2], lvl_y[2],28,22,img_ld_1[3]);
		itoa(l4_life, life, 10);
		iShowImage(575, 55, 26, 32, img_ld_1[8]);
		iSetColor(255,0,0);
		iText(lvl_x[3],lvl_y[3], life, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(lvl_x[3]+15,lvl_y[3], "x", GLUT_BITMAP_TIMES_ROMAN_24);
		itoa(l4_score, points ,10);
		iText(247, 340, "POINTS:", GLUT_BITMAP_9_BY_15);
		iText(310, 340, points, GLUT_BITMAP_9_BY_15);

		if(l4_point[6]==0)iShowImage(lv4_x[19], lv4_y[19],20,20,img_ld_1[4]);
		if((ch_y+25>= lv4_y[19] && ch_y+25<= lv4_y[19]+20) && (ch_x+20>= lv4_x[19] && ch_x+20<= lv4_x[19]+20) || (ch_y+25>= lv4_y[19] && ch_y+25<= lv4_y[19]+20) && (ch_x+10>= lv4_x[19] && ch_x+5<= lv4_x[19]+20))
		{
			if(l4_point[6]==0)l4_score +=10;
			l4_point[6]=1;
		}
		if(l4_point[7]==0)iShowImage(lv4_x[13], lv4_y[13],20,20,img_ld_1[4]);
		if((ch_y+25>= lv4_y[13] && ch_y+25<= lv4_y[13]+20) && (ch_x+20>= lv4_x[13] && ch_x+20<= lv4_x[13]+20) || (ch_y+25>= lv4_y[13] && ch_y+25<= lv4_y[13]+20) && (ch_x+10>= lv4_x[13] && ch_x+5<= lv4_x[13]+20))
		{
			if(l4_point[7]==0)l4_score +=10;
			l4_point[7]=1;
		}
		if(l4_point[8]==0)iShowImage(lv4_x[14], lv4_y[14],20,20,img_ld_1[4]);
		if((ch_y+25>= lv4_y[14] && ch_y+25<= lv4_y[14]+20) && (ch_x+20>= lv4_x[14] && ch_x+20<= lv4_x[14]+20) || (ch_y+25>= lv4_y[14] && ch_y+25<= lv4_y[14]+20) && (ch_x+10>= lv4_x[14] && ch_x+5<= lv4_x[14]+20))
		{
			if(l4_point[7]==0)l4_score +=10;
			l4_point[8]=1;
		}
		iShowImage(lv4_x[15], lv4_y[15],62,14,img_ld_1[7]);
		if(ch_x+10>=lv4_x[15]+5 && ch_x+12<=lv4_x[15]+58 && ch_y==lv4_y[15]+10)
		{
			jumpDown=false;
			jump=false;
		}

		else if(ch_x+10>=lv4_x[16]+5 && ch_x+12<=lv4_x[16]+58 && ch_y==lv4_y[16]+10)
		{
			jumpDown=false;
			jump=false;
		}

		else if(ch_x+10>=lv4_x[18]+5 && ch_x+12<=lv4_x[18]+58 && ch_y==lv4_y[18]+10)
		{
			jumpDown=false;
			jump=false;
		}
		else 
			jumpDown=true;

		iShowImage(lv4_x[18], lv4_y[18],62,14,img_ld_1[7]);
		iShowImage(lv4_x[16], lv4_y[16],62,14,img_ld_1[7]);

		if(ch_x+8>=200 && ch_x+20<=250 && ch_y>=0 && ch_y<=70)//hole
		{
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l1_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
				rotate = false;
			}
		}
		if(ch_x+8>=318 && ch_x+20<=364 && ch_y>=0 && ch_y<=70)//hole
		{
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l1_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
				rotate = false;
			}
		}
		if(ch_x+8>=470 && ch_x+20<=520 && ch_y>=0 && ch_y<=70)//hole
		{
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l1_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
				rotate = false;
			}
		}
		if(ch_x>=570)
		{
			if(l4_f[4]==0)
			{
				l4_score+=10;
				FILE *print_score = fopen("database\\level scores.txt", "w");
				if(dif_sel_op==1)
				{
					ps[i_flag].score4=l4_score;
				}
				else if(dif_sel_op==2)
				{
					psmed[i_flag].score4=l4_score;
				}
				else if(dif_sel_op==3)
				{
					pshard[i_flag].score4=l4_score;
				}
				for(int i=0; i<users;i++)
				{
					fprintf(print_score, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", ps[i].name, ps[i].score1,ps[i].score2,ps[i].score3,ps[i].score4,ps[i].score5, psmed[i].score1,psmed[i].score2,psmed[i].score3,psmed[i].score4,psmed[i].score5,pshard[i].score1,pshard[i].score2,pshard[i].score3,pshard[i].score4,pshard[i].score5);
					printf("%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", ps[i].name, ps[i].score1,ps[i].score2,ps[i].score3,ps[i].score4,ps[i].score5, psmed[i].score1,psmed[i].score2,psmed[i].score3,psmed[i].score4,psmed[i].score5,pshard[i].score1,pshard[i].score2,pshard[i].score3,pshard[i].score4,pshard[i].score5);
				}
				fclose(print_score);
				l4_f[4]=1;
			}
			iShowImage(170, 150, 247, 138, img_ld_1[9]);
			lev_cmplt = true;
			if(m_x>265 && m_x<340 && m_y>170 && m_y<190)
			{
				dif_sel_op=1;
				sel_lev=0;
				ch_x=0;
				l4_life = 3;
				l4_score=0;
				l4_f[0]=0;
				l4_f[1]=0;
				l4_f[2]=0;
				l4_point[0] =0;
				l4_point[1] =0;
				l4_point[2] =0;
				l4_point[3] =0;
				l4_point[4] =0;
				l4_point[5] =0;
				l4_point[6] =0;
				l4_point[7] =0;
				l4_point[8] =0;
			}
		}
	}
	if(m_x>530 && m_x<554 && m_y>350 && m_y<=375 || options==true)
	{
		options =true;
		iShowImage(195, 100, 201,215, img_ld_1[10]);
		if(m_x>230 && m_x<360 && m_y>245 && m_y<=270)//resume
		{
			options =false;
			m_x=m_y=0;
		}
		if(m_x>230 && m_x<360 && m_y>190 && m_y<=220)//restart
		{
			options =false;
			ch_x=0;
			l4_life = 3;
			l4_score=0;
			l4_f[0]=0;
			l4_f[1]=0;
			l4_f[2]=0;
			l4_point[0] =0;
			l4_point[1] =0;
			l4_point[2] =0;
			l4_point[3] =0;
			l4_point[4] =0;
			l4_point[5] =0;
			l4_point[6] =0;
			l4_point[7] =0;
			l4_point[8] =0;
			m_x=m_y=0;
		}
		if(m_x>230 && m_x<360 && m_y>140 && m_y<=170)//back
		{
			options =false;
			dif_sel_op=1;
			sel_lev=0;
			ch_x=0;
			l4_life=3;
			l4_score=0;
			l4_f[0]=0;
			l4_f[1]=0;
			l4_f[2]=0;
			l4_point[0] =0;
			l4_point[1] =0;
			l4_point[2] =0;
			l4_point[3] =0;
			l4_point[4] =0;
			l4_point[5] =0;
			l4_point[6] =0;
			l4_point[7] =0;
			l4_point[8] =0;
			m_x=m_y=0;
		}
	}
	if(l4_life==0)
	{
		lev_cmplt =true;
		iShowImage(175, 140, 260, 158, img_ld_1[11]);
		if(m_x>250 && m_x<360 && m_y>170 && m_y<200)
		{
			dif_sel_op=1;
			sel_lev=0;
			ch_x=0;
			l4_life=3;
			l4_score=0;
			l4_f[0]=0;
			l4_f[1]=0;
			l4_f[2]=0;
			l4_point[0] =0;
			l4_point[1] =0;
			l4_point[2] =0;
			l4_point[3] =0;
			l4_point[4] =0;
			l4_point[5] =0;
			l4_point[6] =0;
			l4_point[7] =0;
			l4_point[8] =0;

		}
	}

	character_move();

}


void l4_position()
{
	lv4_x[0]=245; lv4_y[0]=355;
	lv4_x[1]=170;lv4_x[12]=85; lv4_y[1]=100;lv4_y[12]=145;
	lv4_x[2]=lv4_x[13]=340; lv4_y[2]=lv4_y[13]=145;
	lv4_x[3]=lv4_x[14]=490; lv4_y[3]=lv4_y[14]=145;
	lv4_x[4]=lv4_x[15]=320; lv4_y[4]=lv4_y[15]=110;
	lv4_x[5]=lv4_x[16]=470; lv4_y[5]=lv4_y[16]=110;
	/*lv4_x[6]=*/lv4_x[17]=65; /*lv4_x[6]=*/lv4_y[17]=110;
	lv4_x[7]=145; lv4_y[7]=120;
	lv4_x[8]=335; lv4_y[8]=165;
	lv4_x[9]=475; lv4_y[9]=165;
	lv4_x[10]=320; lv4_y[10]=110;
	lv4_x[11]=270; lv4_y[11]=110;
	lv4_x[18]=205; lv4_y[18]=110;
	lv4_x[19]=225; lv4_y[19]=145;


}
void l4_img_ld()
{
	img_ld_4[0]=iLoadImage("Level 4\\Lvl4(1)-01.png");
	img_ld_4[1]=iLoadImage("Level 4\\Lvl_4_icon.png");
	img_ld_4[2]=iLoadImage("Level 4\\Lvl4(2)-01.png");
	img_ld_4[3]=iLoadImage("Level 4\\Lvl4(3)-01.png");

}

/*______________________________________________Level 5 Screen______________________________________________*/

int lv5_x[25], lv5_y[25],img_ld_5[20] ;
int l5_f[5]={0,0};
int l5_point[10]={0,0};
int l5_life=3;

void l5_screen()
{
	/*______________________________________________Screen 1______________________________________________*/

	char points[10], life[5];
	lev_cmplt=false;

	if(l5_f[0]==0)
	{
		iShowImage(0, 0, 600,400,img_ld_5[0]);
		iShowImage(lv5_x[0], lv5_y[0],93,23,img_ld_5[1]);
		iShowImage(lvl_x[1], lvl_y[1],24,25,img_ld_1[2]);
		iShowImage(lvl_x[2], lvl_y[2],28,22,img_ld_1[3]);
		itoa(l5_life, life, 10);
		iSetColor(255,0,0);
		iText(lvl_x[3],lvl_y[3], life, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(lvl_x[3]+15,lvl_y[3], "x", GLUT_BITMAP_TIMES_ROMAN_24);
		itoa(l5_score, points ,10);
		iText(247, 340, "POINTS:", GLUT_BITMAP_9_BY_15);
		iText(310, 340, points, GLUT_BITMAP_9_BY_15);

		if(l5_point[0]==0)iShowImage(lv5_x[1], lv5_y[1],20,20,img_ld_1[4]);
		if((ch_y+25>= lv5_y[1] && ch_y+25<= lv5_y[1]+20) && (ch_x+20>= lv5_x[1] && ch_x+20<= lv5_x[1]+20) || (ch_y+25>= lv5_y[1] && ch_y+25<= lv5_y[1]+20) && (ch_x+10>= lv5_x[1] && ch_x+5<= lv5_x[1]+20))
		{
			if(l5_point[0]==0)l5_score +=10;
			l5_point[0]=1;
		}
		if(l5_point[1]==0)iShowImage(lv5_x[2], lv5_y[2],20,20,img_ld_1[4]);
		if((ch_y+25>= lv5_y[2] && ch_y+25<= lv5_y[2]+20) && (ch_x+20>= lv5_x[2] && ch_x+20<= lv5_x[2]+20) || (ch_y+25>= lv5_y[2] && ch_y+25<= lv5_y[2]+20) && (ch_x+10>= lv5_x[2] && ch_x+5<= lv5_x[2]+20))
		{
			if(l5_point[1]==0)l5_score +=10;
			l5_point[1]=1;
		}
		if(l5_point[2]==0)iShowImage(lv5_x[3], lv5_y[3],20,20,img_ld_1[4]);
		if((ch_y+25>= lv5_y[3] && ch_y+25<= lv5_y[3]+20) && (ch_x+20>= lv5_x[3] && ch_x+20<= lv5_x[3]+20) || (ch_y+25>= lv5_y[3] && ch_y+25<= lv5_y[3]+20) && (ch_x+10>= lv5_x[3] && ch_x+5<= lv5_x[3]+20))
		{
			if(l5_point[2]==0)l5_score +=10;
			l5_point[2]=1;
		}
		iShowImage(lv5_x[4], lv5_y[4],62,14,img_ld_1[7]);
		if(ch_x+10>=lv5_x[4]+5 && ch_x+12<=lv5_x[4]+58 && ch_y==lv5_y[5]+10)
		{
			jumpDown=false;
			jump=false;
		}
		else 
			jumpDown= true;

		if(((ch_x+20>=50 && ch_x<=88) && (ch_y>=50 && ch_y<=73)) || ((ch_x+20>=440 && ch_x<=480) && (ch_y>=50 && ch_y<=73)))
		{
			l5_life--;
			jumpUp=false;
			jumpDown=false;
			rotate =false;
			ch_x=0;
		}

		if(ch_x>=308 && ch_x+20<=355 && ch_y>=0 && ch_y<=70)//hole
		{
			rotate = false;
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l1_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
			}
		}
		if(ch_x>=590)
		{
			ch_x=0;
			l5_f[0]=1;
			l5_f[1]=1;
		}
	}
	/*______________________________________________Screen 2______________________________________________*/
	else if(l5_f[1]==1)
	{

		iShowImage(0, 0, 600,400,img_ld_5[2]);
		iShowImage(lv5_x[0], lv5_y[0],93,23,img_ld_5[1]);
		iShowImage(lvl_x[1], lvl_y[1],24,25,img_ld_1[2]);
		iShowImage(lvl_x[2], lvl_y[2],28,22,img_ld_1[3]);
		itoa(l5_life, life, 10);
		iSetColor(255,0,0);
		iText(lvl_x[3],lvl_y[3], life, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(lvl_x[3]+15,lvl_y[3], "x", GLUT_BITMAP_TIMES_ROMAN_24);
		itoa(l5_score, points ,10);
		iText(247, 340, "POINTS:", GLUT_BITMAP_9_BY_15);
		iText(310, 340, points, GLUT_BITMAP_9_BY_15);

		if(l5_point[3]==0)iShowImage(lv5_x[12], lv5_y[12],20,20,img_ld_1[4]);
		if((ch_y+25>= lv5_y[12] && ch_y+25<= lv5_y[121]+20) && (ch_x+20>= lv5_x[12] && ch_x+20<= lv5_x[12]+20) || (ch_y+25>= lv5_y[12] && ch_y+25<= lv5_y[12]+20) && (ch_x+10>= lv5_x[12] && ch_x+5<= lv5_x[12]+20))
		{
			if(l5_point[3]==0)l5_score +=10;
			l5_point[3]=1;
		}
		if(l5_point[4]==0)iShowImage(lv5_x[13], lv5_y[13],20,20,img_ld_1[4]);
		if((ch_y+25>= lv5_y[13] && ch_y+25<= lv5_y[13]+20) && (ch_x+20>= lv5_x[13] && ch_x+20<= lv5_x[13]+20) || (ch_y+25>= lv5_y[13] && ch_y+25<= lv5_y[13]+20) && (ch_x+10>= lv5_x[13] && ch_x+5<= lv5_x[13]+20))
		{
			if(l5_point[4]==0)l5_score +=10;
			l5_point[4]=1;
		}
		if(l5_point[5]==0)iShowImage(lv5_x[14], lv5_y[14],20,20,img_ld_1[4]);
		if((ch_y+25>= lv5_y[14] && ch_y+25<= lv5_y[14]+20) && (ch_x+20>= lv5_x[14] && ch_x+20<= lv5_x[14]+20) || (ch_y+25>= lv5_y[14] && ch_y+25<= lv5_y[14]+20) && (ch_x+10>= lv5_x[14] && ch_x+5<= lv5_x[14]+20))
		{
			if(l5_point[5]==0)l5_score +=10;
			l5_point[5]=1;
		}
		iShowImage(lv5_x[15], lv5_y[15],62,14,img_ld_1[7]);
		if(ch_x+10>=lv5_x[15]+5 && ch_x+12<=lv5_x[15]+58 && ch_y==lv5_y[15]+10)
		{
			jumpDown=false;
			jump=false;
		}
		else if(ch_x+10>=lv5_x[16]+5 && ch_x+12<=lv5_x[16]+58 && ch_y==lv5_y[16]+10)
		{
			jumpDown=false;
			jump=false;
		}	
		else if(ch_x+10>=lv5_x[17]+5 && ch_x+12<=lv5_x[17]+58 && ch_y==lv5_y[17]+10)
		{
			jumpDown=false;
			jump=false;
		}
		else 
			jumpDown= true;

		iShowImage(lv5_x[16], lv5_y[16],62,14,img_ld_1[7]);
		iShowImage(lv5_x[17], lv5_y[17],62,14,img_ld_1[7]);

		if(((ch_x+20>=44 && ch_x<=84) && (ch_y>=50 && ch_y<=73)) || ((ch_x+20>=440 && ch_x<=480) && (ch_y>=50 && ch_y<=73)))
		{
			l5_life--;
			jumpUp=false;
			jumpDown=false;
			rotate =false;
			ch_x=0;
		}

		if(ch_x>=100 && ch_x+20<=145 && ch_y>=0 && ch_y<=70)//hole
		{
			rotate = false;
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l1_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
			}
		}
		if(ch_x>=463 && ch_x+20<=511 && ch_y>=0 && ch_y<=70)//hole
		{
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l1_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
				rotate = false;
			}
		}
		if(ch_x>=590)
		{
			ch_x=0;
			l5_f[1]=0;
			l5_f[2]=1;
		}
	}

	/*______________________________________________Screen 3______________________________________________*/
	else if(l5_f[2]==1)
	{
		iShowImage(0, 0, 600,400,img_ld_5[3]);
		iShowImage(lv5_x[0], lv5_y[0],92,22,img_ld_5[1]);
		iShowImage(lvl_x[1], lvl_y[1],24,25,img_ld_1[2]);
		iShowImage(lvl_x[2], lvl_y[2],28,22,img_ld_1[3]);
		itoa(l5_life, life, 10);
		iShowImage(575, 55, 26, 32, img_ld_1[8]);
		iSetColor(255,0,0);
		iText(lvl_x[3],lvl_y[3], life, GLUT_BITMAP_TIMES_ROMAN_24);
		iText(lvl_x[3]+15,lvl_y[3], "x", GLUT_BITMAP_TIMES_ROMAN_24);
		itoa(l5_score, points ,10);
		iText(247, 340, "POINTS:", GLUT_BITMAP_9_BY_15);
		iText(310, 340, points, GLUT_BITMAP_9_BY_15);

		if(l5_point[6]==0)iShowImage(lv5_x[19], lv5_y[19],20,20,img_ld_1[4]);
		if((ch_y+25>= lv5_y[19] && ch_y+25<= lv5_y[19]+20) && (ch_x+20>= lv5_x[19] && ch_x+20<= lv5_x[19]+20) || (ch_y+25>= lv5_y[19] && ch_y+25<= lv5_y[19]+20) && (ch_x+10>= lv5_x[19] && ch_x+5<= lv5_x[19]+20))
		{
			if(l5_point[6]==0)l5_score +=10;
			l5_point[6]=1;
		}
		if(l5_point[7]==0)iShowImage(lv5_x[22], lv5_y[13],20,20,img_ld_1[4]);
		if((ch_y+25>= lv5_y[22] && ch_y+25<= lv5_y[22]+20) && (ch_x+20>= lv5_x[22] && ch_x+20<= lv5_x[22]+20) || (ch_y+25>= lv5_y[22] && ch_y+25<= lv5_y[22]+20) && (ch_x+10>= lv5_x[22] && ch_x+5<= lv5_x[22]+20))
		{
			if(l5_point[7]==0)l5_score +=10;
			l5_point[7]=1;
		}
		if(l5_point[8]==0)iShowImage(lv5_x[23], lv5_y[14],20,20,img_ld_1[4]);
		if((ch_y+25>= lv5_y[23] && ch_y+25<= lv5_y[23]+20) && (ch_x+20>= lv5_x[23] && ch_x+20<= lv5_x[23]+20) || (ch_y+25>= lv5_y[23] && ch_y+25<= lv5_y[23]+20) && (ch_x+10>= lv5_x[23] && ch_x+5<= lv5_x[23]+20))
		{
			if(l5_point[8]==0)l5_score +=10;
			l5_point[8]=1;
		}
		iShowImage(lv5_x[18], lv5_y[18],62,14,img_ld_1[7]);
		if(ch_x+10>=lv5_x[18]+5 && ch_x+12<=lv5_x[18]+58 && ch_y==lv5_y[18]+10)
		{
			jumpDown=false;
			jump=false;
		}	
		else if(ch_x+10>=lv5_x[20]+5 && ch_x+12<=lv5_x[20]+58 && ch_y==lv5_y[20]+10)
		{
			jumpDown=false;
			jump=false;
		}		
		else if(ch_x+10>=lv5_x[21]+5 && ch_x+12<=lv5_x[21]+58 && ch_y==lv5_y[21]+10)
		{
			jumpDown=false;
			jump=false;
		}
		else 
			jumpDown= true;

		iShowImage(lv5_x[20], lv5_y[20],62,14,img_ld_1[7]);
		iShowImage(lv5_x[21], lv5_y[21],62,14,img_ld_1[7]);
		if(ch_x>=55 && ch_x+20<=100 && ch_y>=0 && ch_y<=70)//hole
		{

			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l1_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
				rotate = false;
			}
		}
		if(ch_x>=188 && ch_x+20<=236 && ch_y>=0 && ch_y<=70)//hole
		{
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l1_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
				rotate = false;
			}
		}
		if(ch_x>=320 && ch_x+20<=365 && ch_y>=0 && ch_y<=70)//hole
		{
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l1_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
				rotate = false;
			}
		}
		if(ch_x>=470 && ch_x+20<=518 && ch_y>=0 && ch_y<=70)//hole
		{
			jump=false;
			if(ch_y>0)
			{
				ch_y-=2;
			}
			if(ch_y<=5)
			{
				l1_life--;
				ch_x=0;
				ch_y=55;
				jumpDown =true;
				rotate = false;
			}
		}

		if(ch_x>=570)
		{
			if(l5_f[4]==0)
			{
				l5_score+=10;
				FILE *print_score = fopen("database\\level scores.txt", "w");
				if(dif_sel_op==1)
				{
					ps[i_flag].score5=l5_score;
				}
				else if(dif_sel_op==2)
				{
					psmed[i_flag].score5=l5_score;
				}
				else if(dif_sel_op==3)
				{
					pshard[i_flag].score5=l5_score;
				}
				for(int i=0; i<users;i++)
				{
					fprintf(print_score, "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", ps[i].name, ps[i].score1,ps[i].score2,ps[i].score3,ps[i].score4,ps[i].score5, psmed[i].score1,psmed[i].score2,psmed[i].score3,psmed[i].score4,psmed[i].score5,pshard[i].score1,pshard[i].score2,pshard[i].score3,pshard[i].score4,pshard[i].score5);
				}
				fclose(print_score);
				l5_f[4]=1;
			}
			iShowImage(170, 150, 247, 138, img_ld_1[9]);
			lev_cmplt = true;
			if(m_x>265 && m_x<340 && m_y>170 && m_y<190)
			{
				dif_sel_op=1;
				sel_lev=0;
				ch_x=0;
				l5_life = 3;
				l5_score=0;
				l5_f[0]=0;
				l5_f[1]=0;
				l5_f[2]=0;
				l5_point[0] =0;
				l5_point[1] =0;
				l5_point[2] =0;
				l5_point[3] =0;
				l5_point[4] =0;
				l5_point[5] =0;
				l5_point[6] =0;
				l5_point[7] =0;
				l5_point[8] =0;
			}
		}
	}
	if(m_x>530 && m_x<554 && m_y>350 && m_y<=375 || options==true)
	{
		options =true;
		iShowImage(195, 100, 201,215, img_ld_1[10]);
		if(m_x>230 && m_x<360 && m_y>245 && m_y<=270)//resume
		{
			options =false;
			m_x=m_y=0;
		}
		if(m_x>230 && m_x<360 && m_y>190 && m_y<=220)//restart
		{
			options =false;
			ch_x=0;
			l5_life = 3;
			l5_score=0;
			l5_f[0]=0;
			l5_f[1]=0;
			l5_f[2]=0;
			l5_point[0] =0;
			l5_point[1] =0;
			l5_point[2] =0;
			l5_point[3] =0;
			l5_point[4] =0;
			l5_point[5] =0;
			l5_point[6] =0;
			l5_point[7] =0;
			l5_point[8] =0;
			m_x=m_y=0;
		}
		if(m_x>230 && m_x<360 && m_y>140 && m_y<=170)//back
		{
			options =false;
			dif_sel_op=1;
			sel_lev=0;
			l5_life=3;
			ch_x=0;
			l5_score=0;
			l5_f[0]=0;
			l5_f[1]=0;
			l5_f[2]=0;
			l5_point[0] =0;
			l5_point[1] =0;
			l5_point[2] =0;
			l5_point[3] =0;
			l5_point[4] =0;
			l5_point[5] =0;
			l5_point[6] =0;
			l5_point[7] =0;
			l5_point[8] =0;
			m_x=m_y=0;
		}
	}
	if(l5_life==0)
	{
		lev_cmplt =true;
		iShowImage(175, 140, 260, 158, img_ld_1[11]);
		if(m_x>250 && m_x<360 && m_y>170 && m_y<200)
		{
			dif_sel_op=1;
			sel_lev=0;
			ch_x=0;
			l5_life=3;
			l5_score=0;
			l5_f[0]=0;
			l5_f[1]=0;
			l5_f[2]=0;
			l5_point[0] =0;
			l5_point[1] =0;
			l5_point[2] =0;
			l5_point[3] =0;
			l5_point[4] =0;
			l5_point[5] =0;
			l5_point[6] =0;
			l5_point[7] =0;
			l5_point[8] =0;

		}
	}

	character_move();

}



void l5_position()
{
	lv5_x[0]=245; lv5_y[0]=355;
	lv5_x[1]=190;lv5_x[12]=85; lv5_y[1]=105;lv5_y[12]=145;
	lv5_x[2]=325;lv5_x[13]=285; lv5_y[2]=lv5_y[13]=145;
	lv5_x[3]=455;lv5_x[14]=455; lv5_y[3]=110;lv5_y[14]=145;
	lv5_x[4]=305;lv5_x[15]=260; lv5_y[4]=lv5_y[15]=110;
	lv5_x[5]=lv5_x[16]=430; lv5_y[5]=lv5_y[16]=110;
	lv5_x[17]=65;lv5_y[17]=110;
	lv5_x[7]=145; lv5_y[7]=120;
	lv5_x[8]=335; lv5_y[8]=165;
	lv5_x[9]=475; lv5_y[9]=165;
	lv5_x[10]=320; lv5_y[10]=110;
	lv5_x[11]=270; lv5_y[11]=110;
	lv5_x[18]=190; lv5_y[18]=110;
	lv5_x[19]=210; lv5_y[19]=145;
	lv5_x[20]=320; lv5_y[20]=110;
	lv5_x[21]=470; lv5_y[21]=110;
	lv5_x[22]=340; lv5_y[22]=145;
	lv5_x[23]=490; lv5_y[23]=145;


}
void l5_img_ld()
{
	img_ld_5[0]=iLoadImage("Level 5\\Lvl5(1)-01.png");
	img_ld_5[1]=iLoadImage("Level 5\\Lvl_5_icon.png");
	img_ld_5[2]=iLoadImage("Level 5\\Lvl5(2)-01.png");
	img_ld_5[3]=iLoadImage("Level 5\\Lvl5(3)-01.png");
	img_ld_5[4]=iLoadImage("Snd_Off.png");
	img_ld_5[5]=iLoadImage("Snd_On.png");

}

/*_________________________________________________Options_________________________________________________*/

void Op_scrn()
{
	iShowBMP(0,0,"All_Screen(bg).bmp");

	if(m_x>210 && m_x<364 && m_y>190 &&  m_y<229 && music==true)
	{
		music=false;
		PlaySound(0,0,0);
		m_x=m_y=0;
	}
	else if(m_x>210 && m_x<364 && m_y>190 &&  m_y<229 && music==false)
	{
		music=true;
		PlaySound("Sounds\\sound.wav",NULL,SND_LOOP | SND_ASYNC);
		m_x=m_y=0;
	}

	if(music==true)
	iShowImage(210,190,154,39,img_ld_5[4]);
	else if(music ==false)
	iShowImage(210,190,154,39,img_ld_5[5]);
	iShowImage(b_x, b_y,78,36, b);
	if(m_x>b_x && m_x<b_x+78 && m_y>=b_y && m_y<=b_y+36)
	{
		sel_op=0;
		m_x=m_y=0;
	}

}
/*_________________________________________________Score Board_________________________________________________*/
struct Player{
	char playerName[100];
	int scores;
};
struct playerScore1{
	char name[100];
	int score1;
	int score2;
	int score3;
	int score4;
	int score5;
}ps1[1000], ps2[1000], ps3[1000];


int user;
FILE *r_scores = fopen("database\\level scores.txt", "r");
FILE *read_user = fopen("database\\users.txt", "r");
struct Player player[1000], temp;
void score_calc()
{
	fscanf(read_user, "%d",&user);
	for(int i=0; i<user;i++)
	{
		fscanf(r_scores,"%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &ps1[i].name, &ps1[i].score1, &ps1[i].score2, &ps1[i].score3, &ps1[i].score4, &ps1[i].score5, &ps2[i].score1, &ps2[i].score2, &ps2[i].score3, &ps2[i].score4, &ps2[i].score5, &ps3[i].score1, &ps3[i].score2, &ps3[i].score3, &ps3[i].score4, &ps3[i].score5);
		//printf("score_calc = %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", ps1[i].name, ps1[i].score1, ps1[i].score2, ps1[i].score3, ps1[i].score4, ps1[i].score5, ps2[i].score1, ps2[i].score2, ps2[i].score3, ps2[i].score4, ps2[i].score5, ps3[i].score1, ps3[i].score2, ps3[i].score3, ps3[i].score4, ps3[i].score5);
		strcpy(player[i].playerName, ps1[i].name);
		player[i].scores=ps1[i].score1+ps1[i].score2+ps1[i].score3+ps1[i].score4+ps1[i].score5 + ps2[i].score1+ps2[i].score2+ps2[i].score3+ps2[i].score4+ps2[i].score5 + ps3[i].score1+ps3[i].score2+ps3[i].score3+ps3[i].score4+ps3[i].score5;
	}
	for(int i=0; i<user; i++)
	{
		for(int j=0; j<user-1;j++)
		{
			if(player[j].scores<player[j+1].scores)
			{
				temp=player[j];
				player[j]=player[j+1];
				player[j+1]=temp;
			}
		}
	}

}
int score_axis =200;
void scoreboard()
{
	char str[5][10];
	iShowBMP(0,0,"All_Screen(bg).bmp");
	iSetColor(102,51,0);
	iText(85,330, "Player Name", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(77,330, "___________", GLUT_BITMAP_TIMES_ROMAN_24);

	iSetColor(102,51,0);
	iText(450,330, "Scores", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(443,330, "______", GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(0,0,0);
	iText(77,300, player[0].playerName, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(77,250, player[1].playerName, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(77,200, player[2].playerName, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(77,150, player[3].playerName, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(77,100, player[4].playerName, GLUT_BITMAP_TIMES_ROMAN_24);


	iSetColor(255,0,0);
	itoa(player[0].scores,str[0],10);
	if(player[0].scores!=0)iText(485,300, str[0], GLUT_BITMAP_TIMES_ROMAN_24);
	itoa(player[1].scores,str[1],10);
	if(player[1].scores!=0)iText(485,250, str[1], GLUT_BITMAP_TIMES_ROMAN_24);
	itoa(player[2].scores,str[2],10);
	if(player[2].scores!=0)iText(485,200, str[2], GLUT_BITMAP_TIMES_ROMAN_24);
	itoa(player[3].scores,str[3],10);
	if(player[3].scores!=0)iText(485,150, str[3], GLUT_BITMAP_TIMES_ROMAN_24);
	itoa(player[4].scores,str[4],10);
	if(player[4].scores!=0)iText(485,100, str[4], GLUT_BITMAP_TIMES_ROMAN_24);
	iShowImage(b_x, b_y,78,36, b);
	if(m_x>b_x && m_x<b_x+78 && m_y>=b_y && m_y<=b_y+36)
	{
		sel_op=0;
		m_x=m_y=0;
	}

}

/*_________________________________________________Help Screen_________________________________________________*/


void h_screen()
{

	iShowBMP(0,0,"All_Screen(bg).bmp");
	iSetColor(255,0,0);
	iText(85,330, "HOW TO PLAY", GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(102,51,0);
	iText(85,290, "Run and Jump through the obstacles.", GLUT_BITMAP_HELVETICA_18);
	iSetColor(255,0,0);
	iText(85,210, "CONTROLS", GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(102,51,0);
	iText(85,180, "Press '>' to move front.", GLUT_BITMAP_HELVETICA_18);
	iText(85,150, "Press '<' to move back.", GLUT_BITMAP_HELVETICA_18);
	iText(85,120, "Press '^' to jump.", GLUT_BITMAP_HELVETICA_18);
	iSetColor(255,153,51);
	iText(85, 258, "###Hit the rings with head to collect points",GLUT_BITMAP_HELVETICA_18);
	iShowImage(b_x, b_y,78,36, b);
	if(m_x>b_x && m_x<b_x+78 && m_y>=b_y && m_y<=b_y+36)
	{
		sel_op=0;
		m_x=m_y=0;
	}
}



void iDraw()
{
	//place your drawing codes here
	iClear();
	if(sel_op==0)l_screen();//Landing Screen
	else if(sel_op==1 && dif_sel_op==0)d_screen();//Difficulty Level Screen
	else if((dif_sel_op==1 || dif_sel_op==2 || dif_sel_op==3) && sel_lev==0)lev_screen();//Level Screen
	else if(sel_lev==1 && sel_op==1 && (dif_sel_op==1 || dif_sel_op==2 || dif_sel_op==3))l1_screen();//Level1
	else if(sel_lev==2 && sel_op==1 && (dif_sel_op==1 || dif_sel_op==2 || dif_sel_op==3))l2_screen();//Level2
	else if(sel_lev==3 && sel_op==1 && (dif_sel_op==1 || dif_sel_op==2 || dif_sel_op==3))l3_screen();//Level3
	else if(sel_lev==4 && sel_op==1 && (dif_sel_op==1 || dif_sel_op==2 || dif_sel_op==3))l4_screen();//Level4
	else if(sel_lev==5 && sel_op==1 && (dif_sel_op==1 || dif_sel_op==2 || dif_sel_op==3))l5_screen();//Level5
	else if(sel_op==2)Op_scrn();//Options Screen
	else if(sel_op==3)scoreboard();//Scoreboard Screen
	else if(sel_op==4)h_screen();//Help Screen

}

/*
function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/*
function iPassiveMouse() is called when the user moves the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iPassiveMouse(int mx, int my)
{
	//place your codes here
	pm_x=mx, pm_y=my;
}


/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		m_x=mx;
		m_y=my;
		printf("x = %d\t y = %d\n", m_x, m_y);
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	int i;
	if(mode == 1 || mode == 2 || mode == 3)
	{
		if(key == '\r')
		{
			if(mode == 1)
			{
				if(log_flag[1]==1)
				{
					strcpy(str_logname, str);
				}
				else
					strcpy(str_name, str);
			}
			if(mode == 2)
			{
				if(log_flag[1]==1)
				{
					strcpy(str_logpass, str);
					a1=1;

				}
				else
				{
					strcpy(str_pass, str);
				}
			}
			if(mode == 3)
			{
				strcpy(str_auth, str);
				a=1;
			}
			mode++;
			for(i = 0; i < len; i++)
				str[i] = 0;
			len = 0;

		}
		else if(key == '\b')
		{
			str[len-1] = 0;
			len--;
		}
		else
		{
			str[len] = key;
			len++;
		}
	}
	//place your codes for other keys here
}
void iSpecialKeyboard(unsigned char key)
{
	if(key == GLUT_KEY_END)
	{
	}
	if(key ==GLUT_KEY_RIGHT && lev_cmplt ==false)
	{
		rotate = false;
		if(ch_x<600)
		{
			if(speed==1)ch_x+=1;
			else if(speed==2)ch_x+=speed*1;
			else if(speed==3)ch_x+=speed*1;
		}
		stand = false;
	}
	if(key ==GLUT_KEY_LEFT && lev_cmplt ==false)
	{
		rotate = true;
		if(ch_x>0)
		{
			if(speed==1)ch_x-=1;
			else if(speed==2)ch_x-=1.5;
			else if(speed==3)ch_x-=2;
		}
		stand = false;

	}
	if(key == GLUT_KEY_UP && lev_cmplt ==false)
	{
		jumpCount++;
		jumpUp=true;
		jump =true;
	}
	//place your codes for other keys here
}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/



int main()
{

	//place your own initialization codes here.
	l_screen_size();
	d_screen_size();
	lev_screen_size();
	l1_position();
	l2_position();
	l3_position();
	l4_position();
	l5_position();
	log_img_position();
	iInitialize(600, 400, "Jumpy Bumpy");
	log_image();
	ch_image();
	ch_rot_image();
	b=iLoadImage("Back_3.png");
	l_screen_image();
	d_screen_image();
	lev_screen_image();
	l1_image();
	l2_img_ld();
	l3_img_ld();
	l4_img_ld();
	l5_img_ld();
	Jump();
	score_calc();
	iSetTimer(70, character);
	iSetTimer(40, Jump);
	fclose(read_user);
	fclose(r_scores);
	iStart();
	return 0;
}
