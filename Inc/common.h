#ifndef  __COMMON_H__
#define  __COMMON_H__

#include "stm32f4xx_hal.h"
////////////////////////////////////////
//flag : whether in debug (not in use now) 
#define IS_DEBUG 1
//#define IS_DEBUG 0

//flag: whether in wifi debug(usart1&2 send each other)
#define IS_WIFI_DEBUG 1
//#define IS_WIFI_DEBUG 0


////////////////////////////////////////
// 将接收到的按IEEE741存储的float型的数转换为真实的浮点数
typedef union{
    float     f;
    uint32_t  uint32;
}U32toFloat;
////////////////////////////////////////
typedef  enum{
    FALSE = 0,
    TRUE  = !FALSE,
}BOOL;


////////////////////////////////////////
// 一个字节中的bit定义
typedef struct {
    uint8_t  b0:1;
    uint8_t  b1:1;
    uint8_t  b2:1;
    uint8_t  b3:1;
    uint8_t  b4:1;
    uint8_t  b5:1;
    uint8_t  b6:1;
    uint8_t  b7:1;
}bitDef;

typedef  union{
    bitDef   bits8;
    uint8_t  abyte;
}uniBit8Byte;


//----------------------------------------------
typedef struct//存放全局传感参数
{
	uint16_t 	data_temp;
	uint16_t	data_humi;
	uint16_t 	data_cho;
	uint16_t	data_pm25;
	uint16_t	data_ch4;//ADC sample	
	uint16_t    data_pm10;
	uint16_t 	data_sp1_temp;
	uint16_t	data_sp1_humi;
	BOOL		show_sub_dev;
	BOOL		flag_ch4_on;
}struData;

typedef struct//存放全局设置
{
	BOOL		flag_bk_clo;
	BOOL		flag_offline;
	BOOL		flag_infWake_on;
	BOOL		flag_cam_on;
	BOOL		flag_debug_mode;
	BOOL		flag_otg_mode;
	BOOL		flag_xxx;
	uint16_t    bk_col;
	uint8_t		temp;
}struSet;


typedef struct
{
//	BOOL is_TransReady;
//	BOOL is_TransConf;
	BOOL is_NetConf;
	BOOL is_net_conn;
//	BOOL is_Wait_NetConf;
//	BOOL is_UserReg;
//	BOOL is_wait_userConf;
	uint8_t  ssid[30];
	uint8_t  pwd[30];
	uint8_t  addr[16];
	uint16_t port;
	uint32_t  user_id;
	uint32_t  user_key;
}struWifi;


typedef struct
{
	uint16_t			xSize;
	uint16_t			ySize;
	uint16_t const *	ptrPic;
	uint16_t			start_sector;//0 stands for embedded flash otherwise stands for extern flash and ptrPic is NULL
	BOOL				is_load;//res
	BOOL    			is_fill_white;//是否用背景色覆盖白色纯白那种
}struPic;
//----------------------------------------------
typedef struct
{
	uint16_t			x;
	uint16_t			y;
	uint8_t const *		buf;
	uint8_t				icon_num;
}struIcon;

#define	HZ_X	16
#define	HZ_Y	48

//----------------------------------------------
typedef enum 
{
	WIN_MAIN,
	WIN_MENU,
	WIN_ABOUT,
	WIN_SETTING,
	WIN_ALARM,
	WIN_DEMO,
	WIN_WELCOME,
	WIN_MESS
}enumWinMode;


typedef struct
{
	enumWinMode	old_mode;
	enumWinMode	mode;
	BOOL		is_rev;
	BOOL		show_subdev_data;
}struWin;

//----------------------------------------------
typedef struct
{
	FunctionalState    enable_ReadTemp;
	FunctionalState    enable_ReadCH4;
	FunctionalState    enable_ReadSensor;//hcho pm25
	FunctionalState    enable_ReadInf;
	FunctionalState    enable_ReadTouch;
	FunctionalState    enable_ReadWin;
	FunctionalState    enable_SendReport;//send period message
	FunctionalState    enable_SendHeart;//heart bump
	FunctionalState    enable_Led;
	FunctionalState    enable_ReadRTC;
	FunctionalState	   enable_PowerOn;//poweron 
	FunctionalState	   enable_ReadWifiConf;//read conf
	FunctionalState	   enable_SecOneTask;
	FunctionalState	   enable_CH4_onoff;
	FunctionalState	   enable_win_count;
	uint8_t			   win_count;
	uint8_t			   net_conn_count;
	
}struTimerTask;


//----------------------------------------------
typedef struct
{
	BOOL 	flag_wifitt_out;
	BOOL	flag_light_on_off;
}struButtomEvent;



//----------------------------------------------
#define		WIFI_CONFIG_ADDR       0xDC000
#define		SYS_CONFIG_ADDR		  0xD8000
#define		WIFI_CONFIG_ADDR_END	  0xE0000 //size:4000
#define		WIFI_CONFIG_SECTOR	  220
#define		SYS_CONFIG_SECTOR	  220
///////////////////////////////////////////
void  Delay_ms(uint32_t );
void  Delay(volatile uint32_t );
void  Delay_10us(volatile uint32_t );
void  Delay_us(volatile uint32_t );



uint16_t  Digital4_BCD4(uint16_t );
uint32_t  Digital6_BCD6(uint32_t );
uint32_t  Digital8_BCD8(uint32_t );

uint8_t  Swap_bit7_bit0(uint8_t );

#endif

