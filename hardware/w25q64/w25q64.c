#include  "w25q64.h" 
#include  "spi.h"
//#include  "string.h"
//#include  "stdlib.h"
#include  "common.h"
// 写字库时打开
//#include  "ascii.h"
//#include  "hzk16.h"
#include  "hzk24_hi.h"

uint8_t W25Q64_ReadSR(void)   
{   
    uint8_t stx[2],srx[2]; 
    
    stx[0] = W25X_READSTATUSREG;
    W25Q64_CS_0();                              //使能器件   
    HAL_SPI_TransmitReceive(&hspi2, stx,srx,2,100); //发送读取状态寄存器命令  发送1个字节，接收一个字节， 所以要2字节      
    W25Q64_CS_1();                              //取消片选     
    return srx[1];   
} 
//写SPI_FLASH状态寄存器
//只有SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)可以写!!!
void W25Q64_Write_SR(uint8_t sr)   
{ 
    uint8_t stx[2],srx[2];
    
    stx[0] = W25X_WRITESTATUSREG; 
    stx[1] = sr;
    W25Q64_CS_0();                              //使能器件   
    HAL_SPI_TransmitReceive(&hspi2, stx,srx,2,100); //发送写取状态寄存器命令,并写入sr    
    W25Q64_CS_1();                              //取消片选      
}   
//SPI_FLASH写使能 
//将WEL置位   
void W25Q64_Write_Enable(void)   
{
    uint8_t stx[2],srx[2]; 
    
    stx[0] = W25X_WRITEENABLE;    
    W25Q64_CS_0();                              //使能器件   
    HAL_SPI_TransmitReceive(&hspi2, stx,srx,1,100); //发送写使能 没有返回值，只要写一次就可以了
    W25Q64_CS_1();                              //取消片选      
} 
//SPI_FLASH写禁止       
//将WEL清零  
void W25Q64_Write_Disable(void)   
{ 
    uint8_t stx[2],srx[2]; 
    
    stx[0] = W25X_WRITEDISABLE;        
    W25Q64_CS_0();                            //使能器件   
    HAL_SPI_TransmitReceive(&hspi2, stx,srx,1,100); //发送写使能 没有返回值，只要写一次就可以了
    W25Q64_CS_1();                            //取消片选      
}       
//读取芯片ID W25X16的ID:0XEF14
uint16_t W25Q64_ReadID(void)
{
    uint16_t tmp16 = 0;       
    uint8_t stx[6],srx[6];
    
    stx[0]=0x90;stx[1]=0x00;stx[2]=0x00;stx[3]=0x00;
    stx[4]=0xff;stx[5]=0xff;
    W25Q64_CS_0();        
    HAL_SPI_TransmitReceive(&hspi2, stx,srx,6,100);//发送读取ID命令 
    W25Q64_CS_1();    
    tmp16 = srx[4];
    tmp16 = (tmp16<<8) + srx[5];
    return tmp16;
} 

//
//void SPI1_FLASH_ReadUniqueID(uint32_t *Temp1, uint32_t *Temp2)
//{
//    SPI1_FLASH_CS_0();
//    SPI1_ReadWriteByte(0x4B);//发送读取特有ID指令
//    SPI1_ReadWriteByte(0xFF);
//    SPI1_ReadWriteByte(0xFF);
//    SPI1_ReadWriteByte(0xFF);
//    SPI1_ReadWriteByte(0xFF);
//    *Temp1|=SPI1_ReadWriteByte(0xFF)<<24;
//    *Temp1|=SPI1_ReadWriteByte(0xff)<<16;
//    *Temp1|=SPI1_ReadWriteByte(0XFF)<<8;
//    *Temp1|=SPI1_ReadWriteByte(0XFF);
//    *Temp2|=SPI1_ReadWriteByte(0xFF)<<24;
//    *Temp2|=SPI1_ReadWriteByte(0xFF)<<16;
//    *Temp2|=SPI1_ReadWriteByte(0xFF)<<8;
//    *Temp2|=SPI1_ReadWriteByte(0xFF);
//    SPI1_FLASH_CS_1();    
//}
        
//读取SPI FLASH  
//在指定地址开始读取指定长度的数据
//pBuffer:数据存储区
//ReadAddr:开始读取的地址(24bit)
//NumByteToRead:要读取的字节数(最大65535)

void W25Q64_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead)   
{  
    uint8_t stx[4],srx[4];
    
    stx[0] = W25X_READDATA;
    stx[1] = (uint8_t)((ReadAddr)>>16);
    stx[2] = (uint8_t)((ReadAddr)>>8 );
    stx[3] = (uint8_t)ReadAddr;
    W25Q64_CS_0();                           //使能器件   
    HAL_SPI_TransmitReceive(&hspi2, stx, srx, 4, 100);
    HAL_SPI_TransmitReceive(&hspi2, pBuffer, pBuffer, NumByteToRead, 100);
    W25Q64_CS_1();                            //取消片选
}  

//SPI在一页(0~65535)内写入少于256个字节的数据
//在指定地址开始写入最大256字节的数据
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!! 
void W25Q64_Write_Page(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)
{
    uint8_t stx[4],srx[4];
    
    W25Q64_Write_Enable();                  //SET WEL 
    stx[0] = W25X_PAGEPROGRAM;
    stx[1] = (uint8_t)((WriteAddr)>>16);
    stx[2] = (uint8_t)((WriteAddr)>>8 );
    stx[3] = (uint8_t)WriteAddr;
    
    W25Q64_CS_0();                            //使能器件   
    HAL_SPI_TransmitReceive(&hspi2, stx,srx,4,100);
    HAL_SPI_Transmit(&hspi2, pBuffer, NumByteToWrite, 100);
    
    W25Q64_CS_1();                            //取消片选 
    W25Q64_Wait_Busy();                     //等待写入结束
} 
//无检验写SPI FLASH 
//必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
//具有自动换页功能 
//在指定地址开始写入指定长度的数据,但是要确保地址不越界!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大65535)
//CHECK OK
void W25Q64_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)   
{   
    uint16_t pageremain;  
    
    pageremain = 256 - WriteAddr % 256; //单页剩余的字节数    
    if(NumByteToWrite <= pageremain) pageremain = NumByteToWrite;//不大于256个字节
    while(1)
    {   
        W25Q64_Write_Page(pBuffer, WriteAddr, pageremain);
        if(NumByteToWrite==pageremain)break;//写入结束了
        else //NumByteToWrite>pageremain
        {
            pBuffer   += pageremain;
            WriteAddr += pageremain;  

            NumByteToWrite -= pageremain;             //减去已经写入了的字节数
            if(NumByteToWrite > 256) { pageremain = 256; }             //一次可以写入256个字节
            else                     { pageremain = NumByteToWrite; }  //不够256个字节了
        }
    }   
} 

//写SPI FLASH  
//在指定地址开始写入指定长度的数据
//该函数带擦除操作!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大65535)  
static  uint8_t SPI1_FLASH_BUF[4096];    
void W25Q64_Write(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)   
{ 
    uint32_t  secpos;
    uint16_t  secoff;
    uint16_t  secremain;  
    uint16_t  i;  
    
    secpos    = WriteAddr / 4096;//扇区地址 0~511 for w25x16
    secoff    = WriteAddr % 4096;//在扇区内的偏移
    secremain = 4096 - secoff;   //扇区剩余空间大小   
    if(NumByteToWrite <= secremain)  secremain = NumByteToWrite;//不大于4096个字节
    while(1) 
    {   
        W25Q64_Read(SPI1_FLASH_BUF, secpos*4096, 4096);   //读出整个扇区的内容
        for(i=0;i<secremain;i++)//校验数据
        { 
            if(SPI1_FLASH_BUF[secoff+i] != 0XFF)  break; 
        }     //需要擦除   
        if(i < secremain)//需要擦除
        {   
            W25Q64_Erase_Sector(secpos); //擦除这个扇区
            for(i=0;i<secremain;i++)         //复制
            {   SPI1_FLASH_BUF[i+secoff]=pBuffer[i];    }
            W25Q64_Write_NoCheck(SPI1_FLASH_BUF, secpos*4096, 4096);//写入整个扇区  
        }
        else W25Q64_Write_NoCheck(pBuffer, WriteAddr, secremain);//写已经擦除了的,直接写入扇区剩余区间. 
        
        if(NumByteToWrite==secremain)  break;//写入结束了
        else//写入未结束
        {
            secpos++;  //扇区地址增1
            secoff = 0;//偏移位置为0  

            pBuffer   += secremain;  //指针偏移
            WriteAddr += secremain;//写地址偏移   
            NumByteToWrite -= secremain;              //字节数递减
            if(NumByteToWrite>4096) { secremain=4096; } //下一个扇区还是写不完
            else                    { secremain=NumByteToWrite; } //下一个扇区可以写完了
        }   
    }       
}

//擦除整个芯片
//整片擦除时间:
//W25X16:25s 
//W25X32:40s 
//W25X64:40s 
//等待时间超长...
void W25Q64_Erase_Chip(void)   
{   
    uint8_t stx[2],srx[2]; 

    W25Q64_Write_Enable();                  //SET WEL 
    W25Q64_Wait_Busy();                         
    stx[0] = W25X_CHIPERASE; 
    W25Q64_CS_0();                           //使能器件   
    HAL_SPI_TransmitReceive(&hspi2, stx,srx,1,100); 
    W25Q64_CS_1();                           //取消片选
    W25Q64_Wait_Busy();                     //等待芯片擦除结束
}   
//擦除一个扇区
//Dst_Addr:扇区地址 0~511 for w25x16
//擦除一个山区的最少时间:150ms
void W25Q64_Erase_Sector(uint32_t Dst_Addr)   
{   
    uint8_t stx[4],srx[4];
    
    Dst_Addr *= 4096;
    stx[0]    = W25X_SECTORERASE;
    stx[1]    = (uint8_t)((Dst_Addr)>>16);
    stx[2]    = (uint8_t)((Dst_Addr)>>8 );
    stx[3]    = (uint8_t)Dst_Addr;
    
    W25Q64_Write_Enable();                  //SET WEL  
    W25Q64_Wait_Busy();   
    W25Q64_CS_0();                           //使能器件   
    HAL_SPI_TransmitReceive(&hspi2, stx,srx,4,100);
    W25Q64_CS_1();                            //取消片选
    W25Q64_Wait_Busy();                     //等待擦除完成
}  

//等待空闲
void W25Q64_Wait_Busy(void)   
{   
    while ((W25Q64_ReadSR()&0x01)==0x01);   // 等待BUSY位清空
}  
//进入掉电模式
void W25Q64_PowerDown(void)   
{ 
    uint8_t stx[2],srx[2];
    
    stx[0] = W25X_POWERDOWN; 
    W25Q64_CS_0();                            //使能器件   
    HAL_SPI_TransmitReceive(&hspi2, stx,srx,1,100); //发送掉电命令  
    W25Q64_CS_1();                            //取消片选  
    Delay(15);  
}   
//唤醒
void W25Q64_WAKEUP(void)   
{  
    uint8_t stx[2],srx[2];
    
    stx[0] = W25X_RELEASEPOWERDOWN; 
    W25Q64_CS_0();                            //使能器件   
    HAL_SPI_TransmitReceive(&hspi2, stx,srx,1,100); //发送掉电命令    
    W25Q64_CS_1();                            //取消片选 
    Delay(15); 
} 




/************************************************************************
// 函 数 名:      void  Read_aAscii_Dot(u8 chr,u8 *dot)
// 函数功能描述:  从W25Q64中读取一个ASCII字符的16行点阵                
// 参数描述:      u8 chr :  要读取的一个ASCII字符
                  u8 *dot:  读到的ASCII字符的16行点阵
// 返 回 值:      无
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     完成测试
// 函数层次：     面向显示屏显示文字内容--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2016-3-20
// 修 改 人：                                                                         
// 修改日期：     201x-xx-xx
************************************************************************/ 
void  Read_aAsc16_Dot(uint32_t chr,uint8_t *dot)
{
   uint32_t  asc_dot_addr;

   asc_dot_addr = (chr * ASC16_nByte) + ASC16_START_ADRESS; // ascii点阵的开始地址  
   W25Q64_Read(dot,asc_dot_addr,ASC16_nByte);
}

/************************************************************************
// 函 数 名:      void  Read_aAsc24_Dot(u8 chr,u8 *dot)
// 函数功能描述:  从W25Q64中读取一个ASCII字符的24行点阵                
// 参数描述:      u8 chr :  要读取的一个ASCII字符
                  u8 *dot:  读到的ASC24字符的24行点阵, 48字节
// 返 回 值:      无
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     完成测试
// 函数层次：     面向显示屏显示文字内容--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2016-3-20
// 修 改 人：                                                                         
// 修改日期：     201x-xx-xx
************************************************************************/ 
void  Read_aAsc24_Dot(uint32_t chr,uint8_t *dot)
{
   uint32_t  asc_dot_addr;

   asc_dot_addr = (chr * ASC24_nByte) + ASC24_START_ADRESS; // ascii点阵的开始地址  
   W25Q64_Read(dot,asc_dot_addr,ASC24_nByte);
}

/************************************************************************
// 函 数 名:      void  Read_aAsc32_Dot(u8 chr,u8 *dot)
// 函数功能描述:  从W25Q64中读取一个ASCII字符的32行点阵                
// 参数描述:      u8 chr :  要读取的一个ASCII字符
                  u8 *dot:  读到的ASC32字符的32行点阵, 64字节
// 返 回 值:      无
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     完成测试
// 函数层次：     面向显示屏显示文字内容--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2016-3-20
// 修 改 人：                                                                         
// 修改日期：     201x-xx-xx
************************************************************************/ 
void  Read_aAsc32_Dot(uint32_t chr,uint8_t *dot)
{
    uint32_t  asc_dot_addr;

    asc_dot_addr = (chr * ASC32_nByte) + ASC32_START_ADRESS; // ascii点阵的开始地址  
    W25Q64_Read(dot,asc_dot_addr,ASC32_nByte);
}


/************************************************************************
// 函 数 名:      Read_aWord_Dot(u16 aword,u8 *dot)
// 函数功能描述:  从W25Q64中读取一个汉字的16行点阵，32个字节                
// 参数描述:      u16 aword :  要读取的一个汉字的机内码（转换为区位码）
                  u8 *dot:     读到的汉字的16行点阵，32个字节
// 返 回 值:      无
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     完成测试
// 函数层次：     面向显示屏显示文字内容--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2016-3-20
// 修 改 人：                                                   
// 修改日期：     201x-xx-xx
************************************************************************/ 
void  Read_aWord_Hzk16_Dot(uint32_t aword,uint8_t *dot)
{
   uint32_t   ch1,ch2,hzk_dot_addr;

   ch2 =  aword & 0xff;
   ch1 = (aword>>8) & 0xff;

   hzk_dot_addr =  ((ch1-0xa1)*94 + ch2-0xa1) * HZK16_nByte + HZK16_START_ADRESS;   // 计算文字在字库中的偏移量
    
   W25Q64_Read(dot,hzk_dot_addr,HZK16_nByte);
}

/************************************************************************
// 函 数 名:      Read_aWord_Dot(u16 aword,u8 *dot)
// 函数功能描述:  从W25Q64中读取一个汉字的24行点阵，72个字节                
// 参数描述:      u16 aword :  要读取的一个汉字的区位码
                  u8 *dot:     读到的汉字的24行点阵，72个字节
// 返 回 值:      无
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     完成测试
// 函数层次：     面向显示屏显示文字内容--软件功能层

// 创 建 人：     zhaoweiliang
// 日期：         2016-3-20
// 修 改 人：                                    
// 修改日期：     201x-xx-xx
************************************************************************/ 
void  Read_aWord_Hzk24_Dot(uint32_t aword,uint8_t *dot)
{
    uint32_t   ch1,ch2,hzk_dot_addr;

    ch2 =  aword & 0xff;
    ch1 = (aword>>8) & 0xff;

    hzk_dot_addr =  ((ch1-0xa1)*94 + ch2-0xa1) * HZK24_nByte + HZK24_START_ADRESS;  // 计算文字在字库中的偏移量
    
    W25Q64_Read(dot,hzk_dot_addr,HZK24_nByte);
}


void  pic_SaveTo_Flash(struPic *pic,uint16_t sector)
{
	
}


