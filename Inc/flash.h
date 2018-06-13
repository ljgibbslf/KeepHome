#ifndef __MYFLASH_H
#define __MYFLASH_H
//#include "stm32f4xx_hal_flash.h"
//#include "stm32f4xx_hal_flash_ex.h"//不能includ这两个
#include "stm32f4xx_hal.h"
#include "main.h"

#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

#define FLASH_Sector_0 0
#define FLASH_Sector_1 1
#define FLASH_Sector_2 2
#define FLASH_Sector_3 3
#define FLASH_Sector_4 4
#define FLASH_Sector_5 5
#define FLASH_Sector_6 6
#define FLASH_Sector_7 7
#define FLASH_Sector_8 8
#define FLASH_Sector_9 9
#define FLASH_Sector_10 10
#define FLASH_Sector_11 11

#define FLASH_SAVE_ADDR  0x08040000  //设置 FLASH 保存地址(必须为 4 的倍数， 
//且所在扇区,要大于本代码所占用到的扇区.否则,写操作的时候 
//,可能会导致擦除整个扇区,从而引起部分程序丢失.引起死机. 


uint32_t STMFLASH_ReadWord(uint32_t faddr);
uint8_t STMFLASH_GetFlashSector(uint32_t addr);
void STMFLASH_Write(uint32_t WriteAddr,uint32_t *pBuffer,uint32_t NumToWrite);
void STMFLASH_Read(uint32_t ReadAddr,uint32_t *pBuffer,uint32_t NumToRead);
void Test_Write(uint32_t WriteAddr,uint32_t WriteData);
#endif