#ifndef __GUI_H__
#define __GUI_H__

#include "stm32f4xx_hal.h"
#include "common.h"

extern struIcon icon_num ;
extern struIcon icon_pic ;
extern struIcon icon_ascii ;
extern struIcon icon_ascii_16_32;
extern struIcon icon_about;
extern struIcon icon_slogan;
extern struIcon 	icon_title ;
#define RGB888TO565(color) rgb8882565(color)
//////////////////////////////////////////////////////////////////
void  Gui_Draw_aPixel(uint16_t ,uint16_t ,uint16_t );
void  Gui_Draw_Line(uint16_t , uint16_t , uint16_t , uint16_t , uint16_t );
void  Gui_Circle(uint16_t ,uint16_t ,uint16_t ,uint16_t ); 
void  Gui_Draw_Rect(uint16_t , uint16_t , uint16_t , uint16_t , uint16_t );
void  Gui_Draw_Asc16_Hzk16(uint16_t , uint16_t , uint16_t , uint16_t , uint8_t *);
void  Gui_Draw_Asc24_Hzk24(uint16_t , uint16_t , uint16_t , uint16_t , uint8_t *);
void  Gui_Draw_A_Asc16(uint16_t , uint16_t , uint16_t , uint16_t , uint8_t );
void  Gui_Draw_Asc32_String(uint16_t , uint16_t , uint16_t , uint16_t , uint8_t *);

void Gui_Draw_24_Dig_U16_Decimal(uint16_t , uint16_t , uint16_t , uint16_t , uint16_t );
void Gui_Draw_16_Dig_U16_Decimal(uint16_t , uint16_t , uint16_t , uint16_t , uint16_t );
void Gui_Draw_32_Dig_U16_Decimal(uint16_t , uint16_t , uint16_t , uint16_t , uint16_t );

void Gui_Draw_24_Dig_U16_Hex(uint16_t , uint16_t , uint16_t , uint16_t , uint16_t );
void Gui_Draw_16_Dig_U16_Hex(uint16_t , uint16_t , uint16_t , uint16_t , uint16_t );
void Gui_Draw_32_Dig_U16_Hex(uint16_t , uint16_t , uint16_t , uint16_t , uint16_t );

void Gui_Draw_24_Dig_U8_Decimal(uint16_t , uint16_t , uint16_t , uint16_t , uint8_t );
void Gui_Draw_16_Dig_U8_Decimal(uint16_t , uint16_t , uint16_t , uint16_t , uint8_t );
void Gui_Draw_32_Dig_U8_Decimal(uint16_t , uint16_t , uint16_t , uint16_t , uint8_t );

void Gui_Draw_24_Dig_U8_Hex(uint16_t , uint16_t , uint16_t , uint16_t , uint8_t );
void Gui_Draw_16_Dig_U8_Hex(uint16_t , uint16_t , uint16_t , uint16_t , uint8_t );
void Gui_Draw_32_Dig_U8_Hex(uint16_t , uint16_t , uint16_t , uint16_t , uint8_t );

void Gui_Draw_x_y_Pic();
void Gui_Draw_Pic(struPic*,uint16_t x ,uint16_t y,uint16_t bkcolor);
void Gui_Draw_Pic_Ext(struPic*,uint16_t x ,uint16_t y,uint16_t bkcolor);

void  Gui_Draw_A_Hz(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,const uint8_t * buff);
void  Gui_Draw_A_Icon(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,struIcon * icon,uint8_t index );
void  gui_draw_a_icon_str(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,struIcon * icon,uint8_t first_index,uint8_t last_index);

void Gui_Draw_My_Num(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,uint16_t num,BOOL is_dot);

void gui_draw_slogan(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor);
void gui_draw_about(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor);
void gui_draw_a_Ascii(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,uint8_t index );
void gui_draw_a_str(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,uint8_t *str);
void gui_draw_a_title_str(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,uint8_t first_index,uint8_t count);
void gui_draw_a_16_Ascii(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,uint8_t index );
void gui_draw_a_16_str(uint16_t x, uint16_t y, uint16_t forcolor, uint16_t bkcolor,uint8_t *str);
uint16_t rgb8882565(uint32_t color);
#endif

