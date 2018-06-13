#ifndef __W25Q64_H__
#define __W25Q64_H__

#include "stm32f4xx_hal.h"
#include "common.h"
#define     BYTESofASCIIARRAY     2048
#define     ASC16_HEIGHT          16

////////////////////////////////////////////////////////////////////////////
//W25X16��д
#define     FLASH_ID                0XEF14

#define     ASC16_START_ADRESS      0x40000     // [0x40000 - 0x40800) , ASCII 16*08 �ֿ�   , ����  2048���ֽ�
#define     ASC24_START_ADRESS      0x40800     // [0x40800 - 0x42000) , ASCII 24*12 �ֿ�   , ����  6144���ֽ�
#define     ASC32_START_ADRESS      0x42000     // [0x42000 - 0x44000) , ASCII 32*16 �ֿ�   , ����  8192���ֽ�

#define     HZK16_START_ADRESS      0           // [0       - 0x40000) , ����  16*16�����ֿ�, ���� 262144���ֽ� 
#define     HZK24_START_ADRESS      0x48000     // [0x48000 - 0xD8000) , HZK24 24*24 �ֿ�   , ���� 589824=0X90000���ֽ�
////////////////////////////////////////////////////////////////////////////
#define     ASC16_nByte             16
#define     ASC24_nByte             48
#define     ASC32_nByte             64

#define     HZK16_nByte             32
#define     HZK24_nByte             72
#define     HZK32_nByte             128

#define     ASC16_nLINE             16
#define     HZK16_nLINE             16
#define     HZK24_nLINE             24
#define     HZK32_nLINE             32

#define     ASC24_nLINE             24
#define     ASC32_nLINE             32

#define     ASC16_8PIXELperROW      8
#define     ASC24_12PIXELperROW     12
#define     ASC32_16PIXELperROW     16

////////////////////////////////////////////////////////////////////////////
//ָ���
#define     W25X_WRITEENABLE        0x06 
#define     W25X_WRITEDISABLE       0x04 
#define     W25X_READSTATUSREG      0x05 
#define     W25X_WRITESTATUSREG     0x01 
#define     W25X_READDATA           0x03 
#define     W25X_FASTREADDATA       0x0B 
#define     W25X_FASTREADDUAL       0x3B 
#define     W25X_PAGEPROGRAM        0x02 
#define     W25X_BLOCKERASE         0xD8 
#define     W25X_SECTORERASE        0x20 
#define     W25X_CHIPERASE          0xC7 
#define     W25X_POWERDOWN          0xB9 
#define     W25X_RELEASEPOWERDOWN   0xAB 
#define     W25X_DEVICEID           0xAB 
#define     W25X_MANUFACT_DEVICEID  0x90 
#define     W25X_JEDEC_DEVICEID     0x9F 
///////////////////////////////////////////////////////




uint16_t   W25Q64_ReadID(void);         //��ȡFLASH ID
uint8_t    W25Q64_ReadSR(void);         //��ȡ״̬�Ĵ��� 
void  W25Q64_Write_SR(uint8_t sr);      //д״̬�Ĵ���
void  W25Q64_Write_Enable(void);        //дʹ�� 
void  W25Q64_Write_Disable(void);       //д����
void  W25Q64_Read(uint8_t* , uint32_t , uint16_t );   //��ȡflash
void  W25Q64_Write(uint8_t* ,uint32_t , uint16_t );//д��flash
void  W25Q64_Erase_Chip(void);           //��Ƭ����
void  W25Q64_Erase_Sector(uint32_t ); //��������
void  W25Q64_Wait_Busy(void);            //�ȴ�����
void  W25Q64_PowerDown(void);            //�������ģʽ
void  W25Q64_WAKEUP(void);               //����
void  W25Q64_ReadUniqueID(uint32_t *, uint32_t *);
void W25Q64_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);
////////////////////////////////////////////////////
void  Read_aAsc16_Dot(uint32_t ,uint8_t *);
void  Read_aAsc24_Dot(uint32_t ,uint8_t *);
void  Read_aAsc32_Dot(uint32_t ,uint8_t *);
void  Read_aWord_Hzk16_Dot(uint32_t ,uint8_t *);
void  Read_aWord_Hzk24_Dot(uint32_t ,uint8_t *);

void  pic_SaveTo_Flash(struPic *pic,uint16_t sector);

//void  Asc16_SaveTo_Flash(void);
//void  Asc24_SaveTo_Flash(void);
//void  Asc32_SaveTo_Flash(void);
//void  Hzk16_SaveTo_Flash(void);
//void  Hzk24_Low4096_SaveTo_Flash(void);
//void  Hzk24_Hi4096_SaveTo_Flash(void);
#endif


