#ifndef __TFTDISP_H__
#define __TFTDISP_H__ 

#include  "stm32f4xx_hal.h"
#include  "touch.h"
#include  "Lcd_Drive.h"
#include  "GUI.h"
#include  "common.h"
#include  "rtc.h"
#include  "config.h"

//----------------------------------------------
//#define RGB888TO565(color) (((((color) >> 19) & 0x1f) << 11) |((((color) >> 1& 0x3f) << 5)|(((color) >> 3) & 0x1f))
#define	   BK_COL 				rgb8882565(0x000080)
#define    WEL_BK_COL			rgb8882565(0xD3D3D3)
// 显示触摸坐标的参数
#define    LINE_Y0              (Y_MAX_PIXEL - 61) // 横线分割触摸坐标的显示
#define    X_X0                  660
#define    X_Y0                 (Y_MAX_PIXEL - 32)
#define    X_TOUCHX             (X_X0 + 24)

#define    Y_X0                 (X_X0 + 100 )
#define    Y_Y0                  X_Y0
#define    Y_TOUCHX             (Y_X0 + 24)

#define    TOUCH_DIG_FORCOLOR    YELLOW_4_4
#define    TOUCH_DIG_BKCOLOR     BLUE_4_4

// 显示测试数值的参数
#define    VALUE_X_Y0           (Y_MAX_PIXEL - 32)
#define    VALUE_X_X0            400
#define    VALUE_X_X1           (VALUE_X_X0 + 12*5)
#define    VAL_X_FORCOLOR        WHITE_3_4
#define    VAL_X_BKCOLOR         GREEN_2_4

#define    VALUE_Y_X0           (VALUE_X_X1 + 12*6)
#define    VALUE_Y_X1           (VALUE_Y_X0 + 12*5)

// 显示时间的参数  
#define    DATA_TIME_Y          (Y_MAX_PIXEL - 42)
#define    YEAR_X0               10
#define    FONT_CLR			     20
#define    YEAR_X1              (YEAR_X0 + FONT_CLR*2)
#define    MONTH_X              (YEAR_X1 + FONT_CLR*3)
#define    DATA_X               (MONTH_X + FONT_CLR*3)
#define    HOUR_X               (DATA_X + FONT_CLR*3)
#define    MINUTE_X             (HOUR_X + FONT_CLR*3)
#define    SECOND_X             (MINUTE_X + FONT_CLR*3)

#define    DATA_TIME_FORCOLOR    CYAN_4_4
#define    DATA_TIME__BKCOLOR    RED_2_4

/////////////////////////////////////////////////////////
//metro style
#define    METRO_LEGHTH					240
#define    METRO_WIDTH					170
#define    METRO_LEGHTH_L			  ((METRO_LEGHTH) * 2 + METRO_X_CLN)
#define    METRO_X_CLN					20 //同屏幕边缘间隙
#define    METRO_Y_CLN					30
#define    METRO_X_STA					20 //方块之间的间隙
#define    METRO_Y_STA					30

#define	   METRO_X_DATA                 80//显示数据时距离方块左上角的距离
#define	   METRO_Y_DATA                 75

//word
#define	   METRO_X_WORD					95
#define	   METRO_y_WORD					20

//scale
#define	   METRO_X_SCA					155
#define	   METRO_y_SCA					95

#define    METRO_1_BK_COL				0x2D5F
#define    METRO_2_BK_COL				PINGKISH_4_4
#define    METRO_3_BK_COL				CYAN_4_4
#define    METRO_4_BK_COL				rgb8882565(0x228B25)

#define	   METRO_BL_H_1_X					METRO_X_STA + METRO_X_CLN * 0 + METRO_LEGHTH * 0
#define	   METRO_BL_H_2_X					METRO_X_STA + METRO_X_CLN * 1 + METRO_LEGHTH * 1
#define	   METRO_BL_H_3_X					METRO_X_STA + METRO_X_CLN * 2 + METRO_LEGHTH * 2
#define	   METRO_BL_L_1_Y					METRO_Y_STA
#define	   METRO_BL_L_2_Y					METRO_Y_STA + METRO_Y_CLN * 1 + METRO_WIDTH * 1
//----------------------------------------------
//side menu style
#define		MENU_BK_COL					rgb8882565(0xD3D3D3)
#define		MENU_FONT_COL				0x0
#define		MENU_WEIGHT					200	
#define		MENU_START_X				20 //font starts at (x,y)
#define		MENU_START_Y				20
//----------------------------------------------
//Bottom BUTTON
#define	    BTM_BUTTON_WEIGHT				100
#define	    BTM_BUTTON_HEIGHT				30
#define		BTM_BUTTON_1_X					420
#define		BTM_BUTTON_1_y					440
#define		BTM_BUTTON_X_CLE				40
#define		BTM_BUTTON_2_X					BTM_BUTTON_1_X + BTM_BUTTON_WEIGHT + BTM_BUTTON_X_CLE
#define		BTM_BUTTON_3_X					BTM_BUTTON_2_X + BTM_BUTTON_WEIGHT + BTM_BUTTON_X_CLE
#define		BTM_BUTTON_FONT_COL				WHITE_4_4

//#define		BTM_BUTTON_REC_X				BTM_BUTTON_1_X-10
//#define		BTM_BUTTON_REC_Y				BTM_BUTTON_1_y-10
#define		BTM_BUTTON_REC_W
#define		BTM_BUTTON_REC_H
#define		BTM_BUTTON_REC_COL				WHITE_4_4

#define	    MENU_BUTTON_WEIGHT				100
#define	    MENU_BUTTON_HEIGHT				30
#define		MENU_BUTTON_1_X					BTM_BUTTON_3_X
#define		MENU_BUTTON_1_y					BTM_BUTTON_1_y
#define		MENU_BUTTON_y_CLE				40

#define		MENU_BUTTON_2_y					BTM_BUTTON_1_y + MENU_BUTTON_HEIGHT + MENU_BUTTON_y_CLE
//----------------------------------------------
//ABOUT
#define 	WIN_ABT_X						220
#define 	WIN_ABT_Y						80
#define 	WIN_ABT_W						420
#define 	WIN_ABT_H						280
#define 	WIN_ABT_COL						rgb8882565(0x9F79EE)
#define 	WIN_ABT_FONT_X				WIN_ABT_X+60
#define 	WIN_ABT_FONT_Y				WIN_ABT_Y+75
//DENO
#define 	WIN_DEMO_X						220
#define 	WIN_DEMO_Y						80
#define 	WIN_DEMO_W						420
#define 	WIN_DEMO_H						280
#define 	WIN_DEMO_COL					rgb8882565(0x228B22)
#define 	WIN_DEMO_FONT_X				WIN_DEMO_X+30
#define 	WIN_DEMO_FONT_Y			    WIN_DEMO_Y+30
//DENO
#define 	WIN_ALM_X						220
#define 	WIN_ALM_Y						80
#define 	WIN_ALM_W						420
#define 	WIN_ALM_H						280
#define 	WIN_ALM_COL					RED_4_4
#define 	WIN_ALM_FONT_X				WIN_ALM_X+30
#define 	WIN_ALM_FONT_Y			    WIN_ALM_Y+80

//MESS
#define 	WIN_MESS_X						220
#define 	WIN_MESS_Y						80
#define 	WIN_MESS_W						420
#define 	WIN_MESS_H						280
#define 	WIN_MESS_COL					0x0
#define 	WIN_MESS_FONT_X				WIN_MESS_X+30
#define 	WIN_MESS_FONT_Y			    WIN_MESS_Y+30
//----------------------------------------------
#define AQI_1	50
#define AQI_2	100
#define AQI_3	150
#define AQI_4	200
	
#define AQI_COL_1	GREEN_2_4
#define AQI_COL_2	YELLOW_2_4
#define AQI_COL_3	0xFFFF
#define AQI_COL_4	0xFFFF
#define AQI_COL_5	0xFFFF

#define AQI_X		METRO_X_DATA*4 + 30

//----------------------------------------------
#define FLAG_WIFI_X			790
#define FLAG_WIFI_Y			30
#define FLAG_WIFI_FON_COL	WHITE_4_4

//----------------------------------------------
typedef enum 
{
	MENU_BUTTON_1,
	MENU_BUTTON_2
}enumBtnName;

typedef struct
{
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
	BOOL	is_touch;
	void * callback;
	enumBtnName name;
}struButtom;

#define		BUTTON_NUM	3
//----------------------------------------------

/////////////////////////////////////////////////////////
extern struIcon 	icon_num ;
extern struIcon 	icon_pic ;
extern struIcon     icon_xm;
extern struIcon     icon_xh;
extern struData		sensor_data_now;//store sensor data;
////////////////////////////////////////////////////////
void  LCD_Digital_U16_Asc16(uint16_t , uint16_t , uint16_t , uint16_t , uint16_t );
void  LCD_Digital_U8_Asc16( uint16_t , uint16_t , uint16_t , uint16_t , uint8_t  );
char  Get_HextoASC_Disp(char );
void  LCD_DigHex_U8_Asc16( uint16_t , uint16_t , uint16_t , uint16_t , uint8_t  );
void  LCD_DigHex_U16_Asc16(uint16_t , uint16_t , uint16_t , uint16_t , uint16_t );

void  LCD_Digital_4_Asc16(uint16_t, uint16_t, uint16_t , uint16_t , uint16_t );
void  LCD_Digital_2_Asc16(uint16_t, uint16_t, uint16_t , uint16_t , uint16_t );

void  LCD_Digital_U16_Asc24(uint16_t,uint16_t,uint16_t , uint16_t , uint16_t );

void  tftDisp_Touch_XY(struTouch *);
void  tftDisp_Test_Val(uint16_t, uint16_t);     // 显示 valuetest 的值
void  tftDisp_DataTime(struRTC );
void  tftDisp_AllDataTime(struRTC );
void  Disp_ADC1_Val(uint16_t , uint16_t , uint16_t , uint16_t );


void  tftDisp_Main(struWin * win_now);

void  tftDisp_SensorData(struWin * win_now);
void  tftDisp_PM25(struData *);
void  tftDisp_SensorAlarm(struData *);
void  tftDisp_SensorPic(void);

void  tftDisp_Logo(void);
void  tftDisp_Weather(void);
void  tftDisp_CMSIS(void);

void  tftDisp_fresh(struWin *);
void  tftDisp_menu_l();
void  tftDisp_debug();
void  tftDisp_about();
void  tftDisp_demo();
void  tftDisp_alarm(BOOL is_rev);
void  tftDisp_welcome();
void  tftDisp_wifi_flag(BOOL is_show,BOOL is_red);

void  tftDisp_btn_init(struButtom ** but_list);
void  tftDisp_draw_btn(struButtom ** but_list);

void tftDisp_mess(const char * mess);
void tftDisp_bar(uint16_t leng);
#endif
