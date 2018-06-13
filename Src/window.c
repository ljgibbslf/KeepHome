/*************************************************
//File name:	window.c
//File info:	control window displayed on LCD(bridge between tftDisp and touch)
//Author:		fan Li
//Date:			18.4.15
*************************************************/
#include "window.h"

extern struTimerTask      tim_task;

void window_ctl(struTouch ctpxy,struWin * win)
{
	//Activate /Deactivate Right Menu
	if(ctpxy.ctpmainstatus == TOUCHED && ctpxy.dx < -15 
		&& ctpxy.ctpxy.ctp_x > X_MAX_PIXEL -150 
		&& win->mode == WIN_MAIN)
		{
			//show menu
			win->old_mode = win->mode;
			win->mode = WIN_MENU;
		}
		else if(ctpxy.ctpmainstatus == TOUCHED && ctpxy.dx > 15 
			&& ctpxy.ctpxy.ctp_x > X_MAX_PIXEL -200
			&& win->mode == WIN_MENU
			)
		{
			//flod the menu
			win->old_mode = win->mode;
			win->mode = WIN_MAIN;
		}
		
	//BOTTOM ABOUT
	if(is_touch_area(ctpxy,BTM_BUTTON_1_X,BTM_BUTTON_1_y,BTM_BUTTON_WEIGHT,BTM_BUTTON_HEIGHT,TOUCH_MARGIN)
		&& win->mode == WIN_MAIN
	)
	{
		win->old_mode = win->mode;
		win->mode = WIN_ABOUT;
		
	}
	//BOTTOM DEMO1 boommed
//	if(is_touch_area(ctpxy,BTM_BUTTON_2_X,BTM_BUTTON_1_y,BTM_BUTTON_WEIGHT,BTM_BUTTON_HEIGHT,TOUCH_MARGIN)
//		&& win->mode == WIN_MAIN
//	){win->old_mode = win->mode;win->mode = WIN_DEMO;}
	
	
	//AMARM MODE
	if(ctpxy.ctpmainstatus == TOUCHED 
		&& ctpxy.ctpxy.ctp_x >= WIN_DEMO_X - TOUCH_MARGIN && ctpxy.ctpxy.ctp_x <= WIN_DEMO_X + WIN_DEMO_W + TOUCH_MARGIN 
		&& ctpxy.ctpxy.ctp_y >= WIN_DEMO_Y - TOUCH_MARGIN && ctpxy.ctpxy.ctp_y <= WIN_DEMO_Y + WIN_DEMO_H + TOUCH_MARGIN
		&& win->mode == WIN_DEMO
	){win->old_mode = win->mode;win->mode = WIN_ALARM;}
	
	
	//Return home from about/demo
	if(is_touch_area(ctpxy,40,300,100,100,TOUCH_MARGIN))
	{
		if(win->old_mode == WIN_ABOUT || win->old_mode == WIN_DEMO || win->old_mode == WIN_ALARM
			|| win->old_mode == WIN_MESS)
		{
			win->old_mode = win->mode;
			win->mode = WIN_MAIN;
		}
	}
	
	//show son node args
	if(is_touch_area(ctpxy,METRO_BL_H_1_X,METRO_BL_L_1_Y,METRO_LEGHTH,METRO_WIDTH,TOUCH_MARGIN))
	{
		win->show_subdev_data =!win->show_subdev_data;
		Delay_ms(50);
		
		win->old_mode = WIN_DEMO;
		win->mode = WIN_MAIN;
		//refresh data 
		tftDisp_SensorData(win);
		
	}
	
	
}

void buttom_event_ctl(struTouch ctpxy,struWin * win,struButtomEvent * but_ent)
{
	//BOTTOM 1_R quit wifi tt 
	if(is_touch_area(ctpxy,BTM_BUTTON_3_X,BTM_BUTTON_1_y,BTM_BUTTON_WEIGHT,BTM_BUTTON_HEIGHT,TOUCH_MARGIN)
		&& win->mode == WIN_MAIN
	)
	{
		but_ent->flag_wifitt_out = TRUE;
		win->old_mode = win->mode;
		win->mode = WIN_MESS;
	}
	
	//BOTTOM of light
	if(is_touch_area(ctpxy,BTM_BUTTON_2_X,BTM_BUTTON_1_y,BTM_BUTTON_WEIGHT,BTM_BUTTON_HEIGHT,TOUCH_MARGIN)
		&& win->mode == WIN_MAIN
	)
	{
		but_ent->flag_light_on_off = TRUE;
		win->old_mode = win->mode;
		win->mode = WIN_MESS;
		
	}
}