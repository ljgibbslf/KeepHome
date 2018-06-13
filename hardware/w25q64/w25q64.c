#include  "w25q64.h" 
#include  "spi.h"
//#include  "string.h"
//#include  "stdlib.h"
#include  "common.h"
// д�ֿ�ʱ��
//#include  "ascii.h"
//#include  "hzk16.h"
#include  "hzk24_hi.h"

uint8_t W25Q64_ReadSR(void)   
{   
    uint8_t stx[2],srx[2]; 
    
    stx[0] = W25X_READSTATUSREG;
    W25Q64_CS_0();                              //ʹ������   
    HAL_SPI_TransmitReceive(&hspi2, stx,srx,2,100); //���Ͷ�ȡ״̬�Ĵ�������  ����1���ֽڣ�����һ���ֽڣ� ����Ҫ2�ֽ�      
    W25Q64_CS_1();                              //ȡ��Ƭѡ     
    return srx[1];   
} 
//дSPI_FLASH״̬�Ĵ���
//ֻ��SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)����д!!!
void W25Q64_Write_SR(uint8_t sr)   
{ 
    uint8_t stx[2],srx[2];
    
    stx[0] = W25X_WRITESTATUSREG; 
    stx[1] = sr;
    W25Q64_CS_0();                              //ʹ������   
    HAL_SPI_TransmitReceive(&hspi2, stx,srx,2,100); //����дȡ״̬�Ĵ�������,��д��sr    
    W25Q64_CS_1();                              //ȡ��Ƭѡ      
}   
//SPI_FLASHдʹ�� 
//��WEL��λ   
void W25Q64_Write_Enable(void)   
{
    uint8_t stx[2],srx[2]; 
    
    stx[0] = W25X_WRITEENABLE;    
    W25Q64_CS_0();                              //ʹ������   
    HAL_SPI_TransmitReceive(&hspi2, stx,srx,1,100); //����дʹ�� û�з���ֵ��ֻҪдһ�ξͿ�����
    W25Q64_CS_1();                              //ȡ��Ƭѡ      
} 
//SPI_FLASHд��ֹ       
//��WEL����  
void W25Q64_Write_Disable(void)   
{ 
    uint8_t stx[2],srx[2]; 
    
    stx[0] = W25X_WRITEDISABLE;        
    W25Q64_CS_0();                            //ʹ������   
    HAL_SPI_TransmitReceive(&hspi2, stx,srx,1,100); //����дʹ�� û�з���ֵ��ֻҪдһ�ξͿ�����
    W25Q64_CS_1();                            //ȡ��Ƭѡ      
}       
//��ȡоƬID W25X16��ID:0XEF14
uint16_t W25Q64_ReadID(void)
{
    uint16_t tmp16 = 0;       
    uint8_t stx[6],srx[6];
    
    stx[0]=0x90;stx[1]=0x00;stx[2]=0x00;stx[3]=0x00;
    stx[4]=0xff;stx[5]=0xff;
    W25Q64_CS_0();        
    HAL_SPI_TransmitReceive(&hspi2, stx,srx,6,100);//���Ͷ�ȡID���� 
    W25Q64_CS_1();    
    tmp16 = srx[4];
    tmp16 = (tmp16<<8) + srx[5];
    return tmp16;
} 

//
//void SPI1_FLASH_ReadUniqueID(uint32_t *Temp1, uint32_t *Temp2)
//{
//    SPI1_FLASH_CS_0();
//    SPI1_ReadWriteByte(0x4B);//���Ͷ�ȡ����IDָ��
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
        
//��ȡSPI FLASH  
//��ָ����ַ��ʼ��ȡָ�����ȵ�����
//pBuffer:���ݴ洢��
//ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
//NumByteToRead:Ҫ��ȡ���ֽ���(���65535)

void W25Q64_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead)   
{  
    uint8_t stx[4],srx[4];
    
    stx[0] = W25X_READDATA;
    stx[1] = (uint8_t)((ReadAddr)>>16);
    stx[2] = (uint8_t)((ReadAddr)>>8 );
    stx[3] = (uint8_t)ReadAddr;
    W25Q64_CS_0();                           //ʹ������   
    HAL_SPI_TransmitReceive(&hspi2, stx, srx, 4, 100);
    HAL_SPI_TransmitReceive(&hspi2, pBuffer, pBuffer, NumByteToRead, 100);
    W25Q64_CS_1();                            //ȡ��Ƭѡ
}  

//SPI��һҳ(0~65535)��д������256���ֽڵ�����
//��ָ����ַ��ʼд�����256�ֽڵ�����
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!! 
void W25Q64_Write_Page(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)
{
    uint8_t stx[4],srx[4];
    
    W25Q64_Write_Enable();                  //SET WEL 
    stx[0] = W25X_PAGEPROGRAM;
    stx[1] = (uint8_t)((WriteAddr)>>16);
    stx[2] = (uint8_t)((WriteAddr)>>8 );
    stx[3] = (uint8_t)WriteAddr;
    
    W25Q64_CS_0();                            //ʹ������   
    HAL_SPI_TransmitReceive(&hspi2, stx,srx,4,100);
    HAL_SPI_Transmit(&hspi2, pBuffer, NumByteToWrite, 100);
    
    W25Q64_CS_1();                            //ȡ��Ƭѡ 
    W25Q64_Wait_Busy();                     //�ȴ�д�����
} 
//�޼���дSPI FLASH 
//����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
//�����Զ���ҳ���� 
//��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)
//CHECK OK
void W25Q64_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)   
{   
    uint16_t pageremain;  
    
    pageremain = 256 - WriteAddr % 256; //��ҳʣ����ֽ���    
    if(NumByteToWrite <= pageremain) pageremain = NumByteToWrite;//������256���ֽ�
    while(1)
    {   
        W25Q64_Write_Page(pBuffer, WriteAddr, pageremain);
        if(NumByteToWrite==pageremain)break;//д�������
        else //NumByteToWrite>pageremain
        {
            pBuffer   += pageremain;
            WriteAddr += pageremain;  

            NumByteToWrite -= pageremain;             //��ȥ�Ѿ�д���˵��ֽ���
            if(NumByteToWrite > 256) { pageremain = 256; }             //һ�ο���д��256���ֽ�
            else                     { pageremain = NumByteToWrite; }  //����256���ֽ���
        }
    }   
} 

//дSPI FLASH  
//��ָ����ַ��ʼд��ָ�����ȵ�����
//�ú�������������!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)  
static  uint8_t SPI1_FLASH_BUF[4096];    
void W25Q64_Write(uint8_t *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)   
{ 
    uint32_t  secpos;
    uint16_t  secoff;
    uint16_t  secremain;  
    uint16_t  i;  
    
    secpos    = WriteAddr / 4096;//������ַ 0~511 for w25x16
    secoff    = WriteAddr % 4096;//�������ڵ�ƫ��
    secremain = 4096 - secoff;   //����ʣ��ռ��С   
    if(NumByteToWrite <= secremain)  secremain = NumByteToWrite;//������4096���ֽ�
    while(1) 
    {   
        W25Q64_Read(SPI1_FLASH_BUF, secpos*4096, 4096);   //������������������
        for(i=0;i<secremain;i++)//У������
        { 
            if(SPI1_FLASH_BUF[secoff+i] != 0XFF)  break; 
        }     //��Ҫ����   
        if(i < secremain)//��Ҫ����
        {   
            W25Q64_Erase_Sector(secpos); //�����������
            for(i=0;i<secremain;i++)         //����
            {   SPI1_FLASH_BUF[i+secoff]=pBuffer[i];    }
            W25Q64_Write_NoCheck(SPI1_FLASH_BUF, secpos*4096, 4096);//д����������  
        }
        else W25Q64_Write_NoCheck(pBuffer, WriteAddr, secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 
        
        if(NumByteToWrite==secremain)  break;//д�������
        else//д��δ����
        {
            secpos++;  //������ַ��1
            secoff = 0;//ƫ��λ��Ϊ0  

            pBuffer   += secremain;  //ָ��ƫ��
            WriteAddr += secremain;//д��ַƫ��   
            NumByteToWrite -= secremain;              //�ֽ����ݼ�
            if(NumByteToWrite>4096) { secremain=4096; } //��һ����������д����
            else                    { secremain=NumByteToWrite; } //��һ����������д����
        }   
    }       
}

//��������оƬ
//��Ƭ����ʱ��:
//W25X16:25s 
//W25X32:40s 
//W25X64:40s 
//�ȴ�ʱ�䳬��...
void W25Q64_Erase_Chip(void)   
{   
    uint8_t stx[2],srx[2]; 

    W25Q64_Write_Enable();                  //SET WEL 
    W25Q64_Wait_Busy();                         
    stx[0] = W25X_CHIPERASE; 
    W25Q64_CS_0();                           //ʹ������   
    HAL_SPI_TransmitReceive(&hspi2, stx,srx,1,100); 
    W25Q64_CS_1();                           //ȡ��Ƭѡ
    W25Q64_Wait_Busy();                     //�ȴ�оƬ��������
}   
//����һ������
//Dst_Addr:������ַ 0~511 for w25x16
//����һ��ɽ��������ʱ��:150ms
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
    W25Q64_CS_0();                           //ʹ������   
    HAL_SPI_TransmitReceive(&hspi2, stx,srx,4,100);
    W25Q64_CS_1();                            //ȡ��Ƭѡ
    W25Q64_Wait_Busy();                     //�ȴ��������
}  

//�ȴ�����
void W25Q64_Wait_Busy(void)   
{   
    while ((W25Q64_ReadSR()&0x01)==0x01);   // �ȴ�BUSYλ���
}  
//�������ģʽ
void W25Q64_PowerDown(void)   
{ 
    uint8_t stx[2],srx[2];
    
    stx[0] = W25X_POWERDOWN; 
    W25Q64_CS_0();                            //ʹ������   
    HAL_SPI_TransmitReceive(&hspi2, stx,srx,1,100); //���͵�������  
    W25Q64_CS_1();                            //ȡ��Ƭѡ  
    Delay(15);  
}   
//����
void W25Q64_WAKEUP(void)   
{  
    uint8_t stx[2],srx[2];
    
    stx[0] = W25X_RELEASEPOWERDOWN; 
    W25Q64_CS_0();                            //ʹ������   
    HAL_SPI_TransmitReceive(&hspi2, stx,srx,1,100); //���͵�������    
    W25Q64_CS_1();                            //ȡ��Ƭѡ 
    Delay(15); 
} 




/************************************************************************
// �� �� ��:      void  Read_aAscii_Dot(u8 chr,u8 *dot)
// ������������:  ��W25Q64�ж�ȡһ��ASCII�ַ���16�е���                
// ��������:      u8 chr :  Ҫ��ȡ��һ��ASCII�ַ�
                  u8 *dot:  ������ASCII�ַ���16�е���
// �� �� ֵ:      ��
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     ��ɲ���
// ������Σ�     ������ʾ����ʾ��������--������ܲ�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                                                                         
// �޸����ڣ�     201x-xx-xx
************************************************************************/ 
void  Read_aAsc16_Dot(uint32_t chr,uint8_t *dot)
{
   uint32_t  asc_dot_addr;

   asc_dot_addr = (chr * ASC16_nByte) + ASC16_START_ADRESS; // ascii����Ŀ�ʼ��ַ  
   W25Q64_Read(dot,asc_dot_addr,ASC16_nByte);
}

/************************************************************************
// �� �� ��:      void  Read_aAsc24_Dot(u8 chr,u8 *dot)
// ������������:  ��W25Q64�ж�ȡһ��ASCII�ַ���24�е���                
// ��������:      u8 chr :  Ҫ��ȡ��һ��ASCII�ַ�
                  u8 *dot:  ������ASC24�ַ���24�е���, 48�ֽ�
// �� �� ֵ:      ��
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     ��ɲ���
// ������Σ�     ������ʾ����ʾ��������--������ܲ�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                                                                         
// �޸����ڣ�     201x-xx-xx
************************************************************************/ 
void  Read_aAsc24_Dot(uint32_t chr,uint8_t *dot)
{
   uint32_t  asc_dot_addr;

   asc_dot_addr = (chr * ASC24_nByte) + ASC24_START_ADRESS; // ascii����Ŀ�ʼ��ַ  
   W25Q64_Read(dot,asc_dot_addr,ASC24_nByte);
}

/************************************************************************
// �� �� ��:      void  Read_aAsc32_Dot(u8 chr,u8 *dot)
// ������������:  ��W25Q64�ж�ȡһ��ASCII�ַ���32�е���                
// ��������:      u8 chr :  Ҫ��ȡ��һ��ASCII�ַ�
                  u8 *dot:  ������ASC32�ַ���32�е���, 64�ֽ�
// �� �� ֵ:      ��
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     ��ɲ���
// ������Σ�     ������ʾ����ʾ��������--������ܲ�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                                                                         
// �޸����ڣ�     201x-xx-xx
************************************************************************/ 
void  Read_aAsc32_Dot(uint32_t chr,uint8_t *dot)
{
    uint32_t  asc_dot_addr;

    asc_dot_addr = (chr * ASC32_nByte) + ASC32_START_ADRESS; // ascii����Ŀ�ʼ��ַ  
    W25Q64_Read(dot,asc_dot_addr,ASC32_nByte);
}


/************************************************************************
// �� �� ��:      Read_aWord_Dot(u16 aword,u8 *dot)
// ������������:  ��W25Q64�ж�ȡһ�����ֵ�16�е���32���ֽ�                
// ��������:      u16 aword :  Ҫ��ȡ��һ�����ֵĻ����루ת��Ϊ��λ�룩
                  u8 *dot:     �����ĺ��ֵ�16�е���32���ֽ�
// �� �� ֵ:      ��
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     ��ɲ���
// ������Σ�     ������ʾ����ʾ��������--������ܲ�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                                                   
// �޸����ڣ�     201x-xx-xx
************************************************************************/ 
void  Read_aWord_Hzk16_Dot(uint32_t aword,uint8_t *dot)
{
   uint32_t   ch1,ch2,hzk_dot_addr;

   ch2 =  aword & 0xff;
   ch1 = (aword>>8) & 0xff;

   hzk_dot_addr =  ((ch1-0xa1)*94 + ch2-0xa1) * HZK16_nByte + HZK16_START_ADRESS;   // �����������ֿ��е�ƫ����
    
   W25Q64_Read(dot,hzk_dot_addr,HZK16_nByte);
}

/************************************************************************
// �� �� ��:      Read_aWord_Dot(u16 aword,u8 *dot)
// ������������:  ��W25Q64�ж�ȡһ�����ֵ�24�е���72���ֽ�                
// ��������:      u16 aword :  Ҫ��ȡ��һ�����ֵ���λ��
                  u8 *dot:     �����ĺ��ֵ�24�е���72���ֽ�
// �� �� ֵ:      ��
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     ��ɲ���
// ������Σ�     ������ʾ����ʾ��������--������ܲ�

// �� �� �ˣ�     zhaoweiliang
// ���ڣ�         2016-3-20
// �� �� �ˣ�                                    
// �޸����ڣ�     201x-xx-xx
************************************************************************/ 
void  Read_aWord_Hzk24_Dot(uint32_t aword,uint8_t *dot)
{
    uint32_t   ch1,ch2,hzk_dot_addr;

    ch2 =  aword & 0xff;
    ch1 = (aword>>8) & 0xff;

    hzk_dot_addr =  ((ch1-0xa1)*94 + ch2-0xa1) * HZK24_nByte + HZK24_START_ADRESS;  // �����������ֿ��е�ƫ����
    
    W25Q64_Read(dot,hzk_dot_addr,HZK24_nByte);
}


void  pic_SaveTo_Flash(struPic *pic,uint16_t sector)
{
	
}


