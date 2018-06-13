#include "flash.h"

#define STM32_FLASH_BASE 0x08000000
#define FLASH_WAITETIME 1000

//读取指定地址的字(32 位数据)  
//faddr:读地址  
//返回值:对应数据. 
uint32_t STMFLASH_ReadWord(uint32_t faddr) 
{  
  return *(uint32_t *)faddr;  
} 
 
//获取某个地址所在的 flash 扇区 
//addr:flash 地址 
//返回值:0~11,即 addr 所在的扇区 
uint8_t STMFLASH_GetFlashSector(uint32_t Address) 
{  
  uint8_t sector = 0;
 
  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_Sector_0; 
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_Sector_1; 
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_Sector_2; 
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_Sector_3; 
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_Sector_4; 
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_Sector_5; 
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_Sector_6; 
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_Sector_7; 
  }
  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_Sector_8; 
  }
  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_Sector_9; 
  }
  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_Sector_10; 
  }
  else/*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
  {
    sector = FLASH_Sector_11; 
  }

  return sector;
}

//OTP 区域地址范围:0X1FFF7800~0X1FFF7A0F(最后 16 字节用于 OTP 数据块锁定) 
//WriteAddr:起始地址(此地址必须为 4 的倍数!!) 
//pBuffer:数据指针 
//NumToWrite:字(32 位)数(就是要写入的 32 位数据的个数.) 
void STMFLASH_Write(uint32_t WriteAddr,uint32_t *pBuffer,uint32_t NumToWrite)  
{     
   FLASH_EraseInitTypeDef FlashEraseInit;    
   HAL_StatusTypeDef FlashStatus=HAL_OK;    
   uint32_t SectorError=0; 
   uint32_t addrx=0,endaddr=0;     
   if(WriteAddr<STM32_FLASH_BASE||WriteAddr%4)return; //非法地址         
   HAL_FLASH_Unlock();             //解锁  
   addrx=WriteAddr;    //写入的起始地址 
   endaddr=WriteAddr+NumToWrite*4; //写入的结束地址         
   if(addrx<0X1FFF0000)    
   {       
     while(addrx<endaddr)  //扫清一切障碍.(对非 FFFFFFFF 的地方,先擦除)    
     {     
       if(STMFLASH_ReadWord(addrx)!=0XFFFFFFFF) //有非 0XFFFFFFFF 的地方,要擦除这个扇区     
       {               
         FlashEraseInit.TypeErase=FLASH_TYPEERASE_SECTORS; //类型扇区擦除             
         FlashEraseInit.Sector=STMFLASH_GetFlashSector(addrx);   //要擦除的扇区 notice：现在固定为扇区7           
         FlashEraseInit.NbSectors=1;                        //一次只擦除一个扇区            
         FlashEraseInit.VoltageRange=FLASH_VOLTAGE_RANGE_3;//VCC=2.7~3.6V            
         if(HAL_FLASHEx_Erase(&FlashEraseInit,&SectorError)!=HAL_OK)             
              {                 
                break;//发生错误了             
              }     
       }else addrx+=4;                 
       FLASH_WaitForLastOperation(FLASH_WAITETIME); //等待上次操作完成      
     }   
   }   
   FlashStatus=FLASH_WaitForLastOperation(FLASH_WAITETIME); //等待上次操作完成  
      if(FlashStatus==HAL_OK)  
      {    
        while(WriteAddr<endaddr)//写数据    
        {            
          if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, WriteAddr,*pBuffer)!=HAL_OK)//写入数据     
          {       
            break; //写入异常     
          }     
          WriteAddr+=4;     
          pBuffer++;   
        }     
      }  HAL_FLASH_Lock();           //上锁 
}  
//从指定地址开始读出指定长度的数据 
//ReadAddr:起始地址  pBuffer:数据指针   NumToRead:字(32 位)数 
void STMFLASH_Read(uint32_t ReadAddr,uint32_t *pBuffer,uint32_t NumToRead)     
{ 
  uint32_t i;  
  for(i=0;i<NumToRead;i++)  
  {   
    pBuffer[i]=STMFLASH_ReadWord(ReadAddr);//读取 4 个字节.   
    ReadAddr+=4;//偏移 4 个字节.   
  } 
} 
 
//////////////////////////////////////////测试用/////////////////////////////////////////// 
//WriteAddr:起始地址    WriteData:要写入的数据 
void Test_Write(uint32_t WriteAddr,uint32_t WriteData)     
{  
  STMFLASH_Write(WriteAddr,&WriteData,1);//写入一个字  
} 
 