/*************************************************
//File name:	OV7670.c
//File info:	W&R OV7670
//Author:		fan Li
//Date:
*************************************************/


#include "OV7670.h"

uint8_t Wr_OV7670_Reg(uint8_t reg,uint8_t val)
{
	SCCB_Start();
	
	SCCB_Send_Byte(0x42);
	Delay_us(30);
	SCCB_Send_Byte(reg);
	Delay_us(30);
	SCCB_Send_Byte(val);
	
	SCCB_Stop();
	return 0;
}
uint8_t Rd_OV7670_Reg(uint8_t reg,uint8_t * val)
{
	SCCB_Start();
	SCCB_Send_Byte(0x42);
	Delay_us(30);	
	
	SCCB_Send_Byte(reg);
	SCCB_Stop();
	Delay_us(30);
	
	SCCB_Start();
	SCCB_Send_Byte(0x43);
	Delay_us(30);
	
	*val = SCCB_Read_Byte(0);
	SCCB_NoAck();
	SCCB_Stop();
	return 0;
}
void OV7670_Init(void)
{
	OV7670_RST_OFF();
	Delay_ms(20);
	OV7670_CTL_OFF();
	Delay_ms(5);
	OV7670_RST_ON();
	Delay_ms(20);
	SCCB_GPIO_Init();
	Delay_ms(5);
	Wr_OV7670_Reg(0x12,0x80);
	uint8_t temp;
	Rd_OV7670_Reg(0x0a,&temp);
	Rd_OV7670_Reg(0x0b,&temp);

	OV7670_set_reg();
	//OV7670_config_win(271,12,320,240);
	set_qvga();//QVGA 
}

//----------------------------------------------
void OV7670_config_win(uint16_t startx,uint16_t starty,uint16_t width,uint16_t height)
{
	uint16_t endx,endy;
	uint8_t tmp_reg1,tmp_reg2;
	
	endx = startx + width;
	//TODO why:
	endy = starty + height * 2;//??wired?? 
	
	Rd_OV7670_Reg(0x03,&tmp_reg1); // reg 0x03 store LSB2 of vref stop&start respectively(4 bit)
	tmp_reg1 &= 0xf0;
	Rd_OV7670_Reg(0x32,&tmp_reg2); // reg 0x32 store LSB3 of href stop & start 
	tmp_reg2 &= 0xc0;
	
	//H
	uint8_t tmp = tmp_reg2 | (endx & 0x07 << 3 ) | (startx & 0x07);//tmp:8bit
	Wr_OV7670_Reg(0x32,tmp);
	tmp = (startx & 0x07F8) >> 3;
	Wr_OV7670_Reg(0x17,tmp); //hstart
	tmp = (endx & 0x7F8) >> 3;
	Wr_OV7670_Reg(0x18,tmp); //hstop
	
	//V
	tmp = tmp_reg1 | ((endy & 0x03) << 2) | (starty & 0x03);//tmp:8bit
	Wr_OV7670_Reg(0x03,tmp);
	tmp = starty >> 2;
	Wr_OV7670_Reg(0x19,tmp);//vstat
	tmp = endy >> 2;
	Wr_OV7670_Reg(0x1A,tmp);//vstop
}

void set_qvga(void)        //??QVGA??
{   
        Wr_OV7670_Reg(0x12, 0x14);//??????RAW,??QVGA
        Wr_OV7670_Reg(0x17, 0x16);//HSTART,????-???????(????HREF[2:0])
        Wr_OV7670_Reg(0x18, 0x04);        //HSTOP,????-???????(????HREF[5:3])
        Wr_OV7670_Reg(0x19, 0x03); //VSTRT, ????-???????(????VREF[1:0])
        Wr_OV7670_Reg(0x1A, 0x7B); //VSTOP,????-???????(????VREF[3:2])
        Wr_OV7670_Reg(0x03, 0x0a);        //VREF        ?[3:2]VREF??????(????VSTOP[7:0])
                                                                        //?[1:0]VREF??????(????VSTOP[7:0])
        Wr_OV7670_Reg(0x70, 0x35);        //SCALING_XSC,??????
        Wr_OV7670_Reg(0x71, 0x3a);         //SCALING_YSC,??????
        Wr_OV7670_Reg(0x72, 0x11);        //SCALING_DCWCTR,DCW??
        Wr_OV7670_Reg(0x73, 0xF7);        //SCALING_PC,??DSP????????
        Wr_OV7670_Reg(0xA2, 0x02);        //SCALING_PCLK_DELAY,??????
        Wr_OV7670_Reg(0xac, 0x0);        //??
}

void OV7670_set_reg()
{
	Wr_OV7670_Reg(0x3a, 0x04);
	Wr_OV7670_Reg(0x40, 0xd0);// 00-FF  5:4 00: normal RGB ? what is noramal RGB 01 RGB565
	Wr_OV7670_Reg(0x8c, 0x0);
	Wr_OV7670_Reg(0x12, 0x14); // RGB 
	Wr_OV7670_Reg(0x32, 0x80);
	Wr_OV7670_Reg(0x17, 0x16);
	Wr_OV7670_Reg(0x18, 0x04);
	Wr_OV7670_Reg(0x19, 0x02);
	Wr_OV7670_Reg(0x1a, 0x7b);
	Wr_OV7670_Reg(0x03, 0x06);
	Wr_OV7670_Reg(0x0c, 0x04);//MSB or LSB
	Wr_OV7670_Reg(0x3e, 0x00);// pclk / 1
	Wr_OV7670_Reg(0x70, 0x3a);
	Wr_OV7670_Reg(0x71, 0x35);
	Wr_OV7670_Reg(0x72, 0x11);
	Wr_OV7670_Reg(0x73, 0x00);
	Wr_OV7670_Reg(0xa2, 0x02);//out delay
	Wr_OV7670_Reg(0x11, 0x81);//clock: mclk / 1
	
	Wr_OV7670_Reg(0x7a, 0x20);//who care ?? 
	Wr_OV7670_Reg(0x7b, 0x1c);
	Wr_OV7670_Reg(0x7c, 0x28);
	Wr_OV7670_Reg(0x7d, 0x3c);
	Wr_OV7670_Reg(0x7e, 0x55);
	Wr_OV7670_Reg(0x7f, 0x68);
	Wr_OV7670_Reg(0x80, 0x76);
	Wr_OV7670_Reg(0x81, 0x80);
	Wr_OV7670_Reg(0x82, 0x88);
	Wr_OV7670_Reg(0x83, 0x8f);
	Wr_OV7670_Reg(0x84, 0x96);
	Wr_OV7670_Reg(0x85, 0xa3);
	Wr_OV7670_Reg(0x86, 0xaf);
	Wr_OV7670_Reg(0x87, 0xc4);
	Wr_OV7670_Reg(0x88, 0xd7);
	Wr_OV7670_Reg(0x89, 0xe8);
	
	Wr_OV7670_Reg(0x13, 0xe0);//acg
	Wr_OV7670_Reg(0x00, 0x00);
	
	Wr_OV7670_Reg(0x10, 0x00);//bao guang
	Wr_OV7670_Reg(0x0d, 0x00);//whindow size 100%
	Wr_OV7670_Reg(0x14, 0x28);//acg
	Wr_OV7670_Reg(0xa5, 0x05);
	Wr_OV7670_Reg(0xab, 0x07);
	Wr_OV7670_Reg(0x24, 0x75);
	Wr_OV7670_Reg(0x25, 0x63);
	Wr_OV7670_Reg(0x26, 0xA5);
	Wr_OV7670_Reg(0x9f, 0x78);
	Wr_OV7670_Reg(0xa0, 0x68);
	Wr_OV7670_Reg(0xa1, 0x03);
	Wr_OV7670_Reg(0xa6, 0xdf);
	Wr_OV7670_Reg(0xa7, 0xdf);
	Wr_OV7670_Reg(0xa8, 0xf0);
	Wr_OV7670_Reg(0xa9, 0x90);
	Wr_OV7670_Reg(0xaa, 0x94);
	Wr_OV7670_Reg(0x13, 0xe5);

	Wr_OV7670_Reg(0x0e, 0x61);
	Wr_OV7670_Reg(0x0f, 0x4b);
	Wr_OV7670_Reg(0x16, 0x02);
	Wr_OV7670_Reg(0x1e, 0x07);
	Wr_OV7670_Reg(0x21, 0x02);
	Wr_OV7670_Reg(0x22, 0x91);
	Wr_OV7670_Reg(0x29, 0x07);
	Wr_OV7670_Reg(0x33, 0x0b);
	Wr_OV7670_Reg(0x35, 0x0b);
	Wr_OV7670_Reg(0x37, 0x1d);
	Wr_OV7670_Reg(0x38, 0x71);
	Wr_OV7670_Reg(0x39, 0x2a);
	Wr_OV7670_Reg(0x3c, 0x78);
	Wr_OV7670_Reg(0x4d, 0x40);
	Wr_OV7670_Reg(0x4e, 0x20);
	Wr_OV7670_Reg(0x69, 0x00);
	Wr_OV7670_Reg(0x6b, 0x60);
	Wr_OV7670_Reg(0x74, 0x19);
	Wr_OV7670_Reg(0x8d, 0x4f);
	Wr_OV7670_Reg(0x8e, 0x00);
	Wr_OV7670_Reg(0x8f, 0x00);
	Wr_OV7670_Reg(0x90, 0x00);
	Wr_OV7670_Reg(0x91, 0x00);
	Wr_OV7670_Reg(0x92, 0x00);
	Wr_OV7670_Reg(0x96, 0x00);
	Wr_OV7670_Reg(0x9a, 0x80);
	Wr_OV7670_Reg(0xb0, 0x84);
	Wr_OV7670_Reg(0xb1, 0x0c);
	Wr_OV7670_Reg(0xb2, 0x0e);
	Wr_OV7670_Reg(0xb3, 0x82);
	Wr_OV7670_Reg(0xb8, 0x0a);



	Wr_OV7670_Reg(0x43, 0x14);
	Wr_OV7670_Reg(0x44, 0xf0);
	Wr_OV7670_Reg(0x45, 0x34);
	Wr_OV7670_Reg(0x46, 0x58);
	Wr_OV7670_Reg(0x47, 0x28);
	Wr_OV7670_Reg(0x48, 0x3a);
	Wr_OV7670_Reg(0x59, 0x88);
	Wr_OV7670_Reg(0x5a, 0x88);
	Wr_OV7670_Reg(0x5b, 0x44);
	Wr_OV7670_Reg(0x5c, 0x67);
	Wr_OV7670_Reg(0x5d, 0x49);
	Wr_OV7670_Reg(0x5e, 0x0e);
	Wr_OV7670_Reg(0x64, 0x04);
	Wr_OV7670_Reg(0x65, 0x20);
	Wr_OV7670_Reg(0x66, 0x05);
	Wr_OV7670_Reg(0x94, 0x04);
	Wr_OV7670_Reg(0x95, 0x08);
	Wr_OV7670_Reg(0x6c, 0x0a);
	Wr_OV7670_Reg(0x6d, 0x55);
	Wr_OV7670_Reg(0x6e, 0x11);
	Wr_OV7670_Reg(0x6f, 0x9f);
	Wr_OV7670_Reg(0x6a, 0x40);
	Wr_OV7670_Reg(0x01, 0x40);
	Wr_OV7670_Reg(0x02, 0x40);
	Wr_OV7670_Reg(0x13, 0xe7);
	Wr_OV7670_Reg(0x15, 0x00);  
	
	
	Wr_OV7670_Reg(0x4f, 0x80);
	Wr_OV7670_Reg(0x50, 0x80);
	Wr_OV7670_Reg(0x51, 0x00);
	Wr_OV7670_Reg(0x52, 0x22);
	Wr_OV7670_Reg(0x53, 0x5e);
	Wr_OV7670_Reg(0x54, 0x80);
	Wr_OV7670_Reg(0x58, 0x9e);
	
	Wr_OV7670_Reg(0x41, 0x08);
	Wr_OV7670_Reg(0x3f, 0x00);
	Wr_OV7670_Reg(0x75, 0x05);
	Wr_OV7670_Reg(0x76, 0xe1);
	Wr_OV7670_Reg(0x4c, 0x00);
	Wr_OV7670_Reg(0x77, 0x01);
	Wr_OV7670_Reg(0x3d, 0xc2);	
	Wr_OV7670_Reg(0x4b, 0x09);
	Wr_OV7670_Reg(0xc9, 0x60);
	Wr_OV7670_Reg(0x41, 0x38);
	Wr_OV7670_Reg(0x56, 0x40);
	
	Wr_OV7670_Reg(0x34, 0x11);
	Wr_OV7670_Reg(0x3b, 0x02); 
								
	Wr_OV7670_Reg(0xa4, 0x89);
	Wr_OV7670_Reg(0x96, 0x00);
	Wr_OV7670_Reg(0x97, 0x30);
	Wr_OV7670_Reg(0x98, 0x20);
	Wr_OV7670_Reg(0x99, 0x30);
	Wr_OV7670_Reg(0x9a, 0x84);
	Wr_OV7670_Reg(0x9b, 0x29);
	Wr_OV7670_Reg(0x9c, 0x03);
	Wr_OV7670_Reg(0x9d, 0x4c);
	Wr_OV7670_Reg(0x9e, 0x3f);
	Wr_OV7670_Reg(0x78, 0x04);
	
	Wr_OV7670_Reg(0x79, 0x01);
	Wr_OV7670_Reg(0xc8, 0xf0);
	Wr_OV7670_Reg(0x79, 0x0f);
	Wr_OV7670_Reg(0xc8, 0x00);
	Wr_OV7670_Reg(0x79, 0x10);
	Wr_OV7670_Reg(0xc8, 0x7e);
	Wr_OV7670_Reg(0x79, 0x0a);
	Wr_OV7670_Reg(0xc8, 0x80);
	Wr_OV7670_Reg(0x79, 0x0b);
	Wr_OV7670_Reg(0xc8, 0x01);
	Wr_OV7670_Reg(0x79, 0x0c);
	Wr_OV7670_Reg(0xc8, 0x0f);
	Wr_OV7670_Reg(0x79, 0x0d);
	Wr_OV7670_Reg(0xc8, 0x20);
	Wr_OV7670_Reg(0x79, 0x09);
	Wr_OV7670_Reg(0xc8, 0x80);
	Wr_OV7670_Reg(0x79, 0x02);
	Wr_OV7670_Reg(0xc8, 0xc0);
	Wr_OV7670_Reg(0x79, 0x03);
	Wr_OV7670_Reg(0xc8, 0x40);
	Wr_OV7670_Reg(0x79, 0x05);
	Wr_OV7670_Reg(0xc8, 0x30);
	Wr_OV7670_Reg(0x79, 0x26); 
	Wr_OV7670_Reg(0x09, 0x00);	
}