#ifndef __LCD_DRIVE_H__
#define __LCD_DRIVE_H__ 
////////////////////////////////////////////////////////////////////////////////// 
#include "stm32f4xx_hal.h"

//////////////////////////////////////////////////////////////////////////////////
// LCD 复位引脚
#define     LCD_RST_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOC_CLK_ENABLE()
#define     LCD_RST_GPIOx               GPIOC        // LCD_RST 驱动引脚所在的端口
#define     LCD_RST_PIN                 GPIO_PIN_5
#define     LCD_RST_ON()                HAL_GPIO_WritePin(LCD_RST_GPIOx, LCD_RST_PIN, GPIO_PIN_RESET)
#define     LCD_RST_OFF()               HAL_GPIO_WritePin(LCD_RST_GPIOx, LCD_RST_PIN, GPIO_PIN_SET)

// LCD 背光引脚
#define     LCD_BKLED_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define     LCD_BKLED_GPIOx             GPIOA        // LCD_BKLED 驱动引脚所在的端口
#define     LCD_BKLED_PIN               GPIO_PIN_15
#define     LCD_BKLED_ON()              HAL_GPIO_WritePin(LCD_BKLED_GPIOx, LCD_BKLED_PIN, GPIO_PIN_SET)
#define     LCD_BKLED_OFF()             HAL_GPIO_WritePin(LCD_BKLED_GPIOx, LCD_BKLED_PIN, GPIO_PIN_RESET)


/////////////////////////////////////////////////////////////////////////////////////
//#define   BLACK                0x0000                // 黑色：    0,   0,   0 //
//#define   WHITE                0xFFFF                // 白色：  255, 255, 255 //

//#define   BLUE                 0x001F                // 红色：    0,   0, 255 //
//#define   RED                  0xF800                // 蓝色：  255,   0,   0 //
//#define   GREEN                0x07E0                // 绿色：    0, 255,   0 //

//#define   CYAN                (BLUE | GREEN)         // 青色：    0, 255, 255 //
//#define   MAGENTA             (BLUE | RED  )         // 品红：  255,   0, 255 //
//#define   YELLOW              (RED  | GREEN)         // 黄色：  255, 255, 0   //

//#define   NAVY                 0x000F                // 深蓝色：  0,   0, 128 //
//#define   DGREEN               0x03E0                // 深绿色：  0, 128,   0 //
//#define   DCYAN                0x03EF                // 深青色：  0, 128, 128 //
//#define   MAROON               0x7800                // 深红色：128,   0,   0 //
//#define   PURPLE               0x780F                // 紫色：  128,   0, 128 //
//#define   OLIVE                0x7BE0                // 橄榄绿：128, 128,   0 //
//#define   LGRAY                0xC618                // 灰白色：192, 192, 192 //
//#define   DGRAY                0x7BEF                // 深灰色：128, 128, 128 //
/////////////////////////////////////////////////////////////////////////////////////
//硬件相关的子函数
#define     Bank1_LCD_D    ((uint32_t)0x60020000)    //Disp Data ADDR
#define     Bank1_LCD_C    ((uint32_t)0x60000000)    //Disp Reg ADDR


//-------------------------屏幕物理像素设置--------------------------------------//
#define LCD_X_SIZE          480
#define LCD_Y_SIZE          854

/////////////////////////////////////用户配置区/////////////////////////////////// 
//支持横竖屏快速定义切换
#define USE_HORIZONTAL          1   //定义了使用横屏  注释掉则为竖屏

#ifdef USE_HORIZONTAL//如果定义了横屏 
    #define X_MAX_PIXEL         LCD_Y_SIZE
    #define Y_MAX_PIXEL         LCD_X_SIZE
#else
    #define X_MAX_PIXEL         LCD_X_SIZE
    #define Y_MAX_PIXEL         LCD_Y_SIZE
#endif

#define		BK_COLOR	0x000F
//////////////////////////////////////////////////////////////////////////////////
#define     BLACK              0x0000
#define     RED_4_4            0xf800
#define     GREEN_4_4          0x07e0
#define     BLUE_4_4           0x001f

#define     RED_3_4            0xb800
#define     GREEN_3_4          0x05e0
#define     BLUE_3_4           0x0017

#define     RED_2_4            0x7800
#define     GREEN_2_4          0x02e0
#define     BLUE_2_4           0x000f

#define     RED_1_4            0x3800
#define     GREEN_1_4          0x01e0
#define     BLUE_1_4           0x0007

#define     RED_1_8            0x1800
#define     GREEN_1_8          0x00e0
#define     BLUE_1_8           0x0003

#define     RED_1_16           0x0800
#define     GREEN_1_16         0x0060
#define     BLUE_1_16          0x0001

#define     WHITE_4_4        (RED_4_4|GREEN_4_4|BLUE_4_4 )
#define     WHITE_3_4        (RED_3_4|GREEN_3_4|BLUE_3_4 )
#define     WHITE_2_4        (RED_2_4|GREEN_2_4|BLUE_2_4 )
#define     WHITE_1_4        (RED_1_4|GREEN_1_4|BLUE_1_4 )
#define     WHITE_1_8        (RED_1_8|GREEN_1_8|BLUE_1_8 )
#define     WHITE_1_16       (RED_1_16|GREEN_1_16|BLUE_1_16 )

#define     YELLOW_4_4       (RED_4_4|GREEN_4_4) // 黄色 
#define     YELLOW_3_4       (RED_3_4|GREEN_3_4)
#define     YELLOW_2_4       (RED_2_4|GREEN_2_4)
#define     YELLOW_1_4       (RED_1_4|GREEN_1_4)
#define     YELLOW_1_8       (RED_1_8|GREEN_1_8)
#define     YELLOW_1_16      (RED_1_16|GREEN_1_16)

#define     PINGKISH_4_4     (RED_4_4|BLUE_4_4)  // 品红
#define     PINGKISH_3_4     (RED_3_4|BLUE_3_4)
#define     PINGKISH_2_4     (RED_2_4|BLUE_2_4)
#define     PINGKISH_1_4     (RED_1_4|BLUE_1_4)
#define     PINGKISH_1_8     (RED_1_8|BLUE_1_8)
#define     PINGKISH_1_16    (RED_1_16|BLUE_1_16)

#define     CYAN_4_4       (GREEN_4_4|BLUE_4_4 ) // 青色
#define     CYAN_3_4       (GREEN_3_4|BLUE_3_4 )
#define     CYAN_2_4       (GREEN_2_4|BLUE_2_4 )
#define     CYAN_1_4       (GREEN_1_4|BLUE_1_4 )
#define     CYAN_1_4       (GREEN_1_4|BLUE_1_4 )
#define     CYAN_1_8       (GREEN_1_8|BLUE_1_8 )
#define     CYAN_1_16      (GREEN_1_16|BLUE_1_16 )




///////////////////////////////////////////////////////
//Lcd初始化及其低级控制函数 
void    LCD_CTRL_GPIO_Init(void);
void    LCD_init(void);
void    LCD_WR_REG(uint16_t Index,uint16_t CongfigTemp);
//Lcd高级控制函数

void  Lcd_ColorBox(uint16_t x,uint16_t y,uint16_t xLong,uint16_t yLong,uint16_t Color);
void  DrawPixel(uint16_t x, uint16_t y, uint16_t Color);
uint16_t GetPoint( uint16_t x, uint16_t y);
void  BlockWrite(uint16_t Xstart,uint16_t Xend,uint16_t Ystart,uint16_t Yend);
void  LCD_Fill_Pic(uint16_t x, uint16_t y,uint16_t pic_H, uint16_t pic_V, const unsigned char* pic);

void  Lcd_Set_Region(uint16_t , uint16_t ,uint16_t ,uint16_t );
void  Lcd_Set_XY(uint16_t , uint16_t );
void  Lcd_Clear_All(uint16_t );
void  Lcd_Clear_Some_Area(uint16_t ,uint16_t ,uint16_t ,uint16_t ,uint16_t );
void  Lcd_Clear_Some_Area_sim(uint16_t stx,uint16_t sty,uint16_t length,uint16_t width,uint16_t color);
#endif

