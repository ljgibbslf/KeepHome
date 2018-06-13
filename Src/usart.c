/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

#include "gpio.h"
#include "dma.h"

/* USER CODE BEGIN 0 */
extern uniWifiMess 		wifi_Rec_Mess;
extern uniWifiMess 		wifi_Sed_Mess;
extern BOOL 	  		flag_Rec_mess;
extern BOOL 			flag_userConf_mode;
extern BOOL				flag_userConf_get;
extern uint8_t	  		user_conf_buffer[100];
extern BOOL      flag_AT_mode;
extern  uint8_t   UDebug_Rec_Buffer[UDebug_REC_MAX_BYTES];   // UDebug  接收缓存区 
extern  uint16_t  UDebug_Rec_Point;                      // UDebug  接收指针
extern  uint8_t	  debug_Label;
uint8_t           debug_RxBuf;                         

extern  uint8_t   UDebug_Send_Buffer[UDebug_SEND_MAX_BYTES]; // UDebug  发送缓存区

extern  uint8_t   UWifi_Rec_Buffer[UWifi_REC_MAX_BYTES];   // UWifi 接收缓存区 
extern  uint16_t  UWifi_Rec_Point;                      // UWifi  接收指针
uint8_t           WifiRxBuf;         
uint8_t           WifiRxBuf_old;
extern  uint8_t   UWifi_Send_Buffer[UWifi_SEND_MAX_BYTES]; // UWifi  发送缓存区

extern	uint8_t   UPm25_Rec_Buffer[PM25_DATA_LENGTH * PM25_BUFFER_NUM];// UPm25  接收缓存区 
extern  uint16_t  UPm25_Rec_Point;                      // UPm25  接收指针
uint8_t           Pm25RxBuf;

extern	uint8_t   UCH2O_Rec_Buffer[CH2O_DATA_LENGTH * CH2O_BUFFER_NUM];// UCH2O  接收缓存区 
extern  uint16_t  UCH2O_Rec_Point;                      // UCH2O  接收指针
uint8_t           CH2ORxBuf;


/* USER CODE END 0 */

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;
DMA_HandleTypeDef hdma_usart6_rx;
DMA_HandleTypeDef hdma_usart6_tx;

/* UART4 init function */
void MX_UART4_Init(void)
{

  huart4.Instance = UART4;
  huart4.Init.BaudRate = 9600;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
/* USART6 init function */

void MX_USART6_UART_Init(void)
{

  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(uartHandle->Instance==UART4)
  {
  /* USER CODE BEGIN UART4_MspInit 0 */

  /* USER CODE END UART4_MspInit 0 */
    /* UART4 clock enable */
    __HAL_RCC_UART4_CLK_ENABLE();
  
    /**UART4 GPIO Configuration    
    PC10     ------> UART4_TX
    PC11     ------> UART4_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* UART4 interrupt Init */
    HAL_NVIC_SetPriority(UART4_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(UART4_IRQn);
  /* USER CODE BEGIN UART4_MspInit 1 */

  /* USER CODE END UART4_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 DMA Init */
    /* USART2_RX Init */
    hdma_usart2_rx.Instance = DMA1_Stream5;
    hdma_usart2_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_rx.Init.Mode = DMA_CIRCULAR;
    hdma_usart2_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart2_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart2_rx) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart2_rx);

    /* USART2_TX Init */
    hdma_usart2_tx.Instance = DMA1_Stream6;
    hdma_usart2_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_tx.Init.Mode = DMA_NORMAL;
    hdma_usart2_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart2_tx) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart2_tx);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 4, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();
  
    /**USART3 GPIO Configuration    
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
  else if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN USART6_MspInit 0 */

  /* USER CODE END USART6_MspInit 0 */
    /* USART6 clock enable */
    __HAL_RCC_USART6_CLK_ENABLE();
  
    /**USART6 GPIO Configuration    
    PC6     ------> USART6_TX
    PC7     ------> USART6_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* USART6 DMA Init */
    /* USART6_RX Init */
    hdma_usart6_rx.Instance = DMA2_Stream2;
    hdma_usart6_rx.Init.Channel = DMA_CHANNEL_5;
    hdma_usart6_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart6_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart6_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart6_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart6_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart6_rx.Init.Mode = DMA_NORMAL;
    hdma_usart6_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart6_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart6_rx) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart6_rx);

    /* USART6_TX Init */
    hdma_usart6_tx.Instance = DMA2_Stream6;
    hdma_usart6_tx.Init.Channel = DMA_CHANNEL_5;
    hdma_usart6_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart6_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart6_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart6_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart6_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart6_tx.Init.Mode = DMA_NORMAL;
    hdma_usart6_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart6_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart6_tx) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart6_tx);

    /* USART6 interrupt Init */
    HAL_NVIC_SetPriority(USART6_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART6_IRQn);
  /* USER CODE BEGIN USART6_MspInit 1 */

  /* USER CODE END USART6_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==UART4)
  {
  /* USER CODE BEGIN UART4_MspDeInit 0 */

  /* USER CODE END UART4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_UART4_CLK_DISABLE();
  
    /**UART4 GPIO Configuration    
    PC10     ------> UART4_TX
    PC11     ------> UART4_RX 
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_10|GPIO_PIN_11);

    /* UART4 interrupt Deinit */
    HAL_NVIC_DisableIRQ(UART4_IRQn);
  /* USER CODE BEGIN UART4_MspDeInit 1 */

  /* USER CODE END UART4_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();
  
    /**USART3 GPIO Configuration    
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

    /* USART3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN USART6_MspDeInit 0 */

  /* USER CODE END USART6_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART6_CLK_DISABLE();
  
    /**USART6 GPIO Configuration    
    PC6     ------> USART6_TX
    PC7     ------> USART6_RX 
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6|GPIO_PIN_7);

    /* USART6 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART6 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART6_IRQn);
  /* USER CODE BEGIN USART6_MspDeInit 1 */

  /* USER CODE END USART6_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
// 设定的数据接收结束，产生回调函数
void    HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{   
    // USART:DEBUG
    if(UartHandle->Instance == USART6) 
    { 
		HAL_UART_Receive_IT(&HUART_DEBUG,&debug_RxBuf,1);  // 设置接收1个字节 产生中断回调 开启下一次接收中断
		//HAL_DMA_Start(UartHandle->hdmarx,UartHandle->Instance->DR,(uint32_t)&UDebug_Rec_Buffer,4);
		//UartHandle->Instance->CR3 |= USART_CR3_DMAR;
		
        UDebug_Rec_Buffer[UDebug_Rec_Point] = debug_RxBuf;
		
		//HAL_UART_Transmit(&HUART_DEBUG,&debug_RxBuf,1,100);//send back
        
		UDebug_Rec_Point++;
        
		if(UDebug_Rec_Point >= UDebug_REC_MAX_BYTES) { UDebug_Rec_Point = 0; }
		
		debug_Label = debug_RxBuf;
        
        
    }
    //=================================
    // USART:Wifi
    if(UartHandle->Instance == USART_WIFI)
    { 
		UWifi_Rec_Buffer[UWifi_Rec_Point] = WifiRxBuf;
		//HAL_UART_Transmit(&huart2,&WifiRxBuf,1,100);//send back
        UWifi_Rec_Point++;
        if(UWifi_Rec_Point >= UWifi_REC_MAX_BYTES) { UWifi_Rec_Point = 0; }
		
		//receive conf ----------------------------------------------
		//search for userconf start and flush buffer
		if(WifiRxBuf_old == 0x5c && WifiRxBuf == 0x61 && flag_userConf_mode)
		{
			flush_Buffer(UWifi_Rec_Buffer,UWifi_REC_MAX_BYTES);
			UWifi_Rec_Point = 0x0;
		}
		
		//search for userconf stop and copy rec_buffer to conf_buffer
		if(WifiRxBuf_old == 0x5c && WifiRxBuf == 0x62 && flag_userConf_mode)
		{
			memcpy(user_conf_buffer,UWifi_Rec_Buffer,UWifi_Rec_Point - 2);
			flag_userConf_get = TRUE;
			flush_Buffer(UWifi_Rec_Buffer,UWifi_REC_MAX_BYTES);
		}
		//----------------------------------------------
		
		//receive normal message----------------------------------------------
		//接收到可能的一帧(结束位)
		if(WifiRxBuf == END_BYTE)
		{
			//定位开始位
			uint8_t start_Index;
			start_Index = UWifi_Rec_Point - MESS_LENG >= 0?UWifi_Rec_Point - MESS_LENG:UWifi_Rec_Point - MESS_LENG + UWifi_REC_MAX_BYTES;
			
			//判断是否是完整的一帧
			if(UWifi_Rec_Buffer[start_Index] == START_BYTE)
			{
				uint8_t i;
				//复制接收帧到帧缓冲区中
				if(start_Index < UWifi_Rec_Point)//考虑数组存满归零的情况
				{
					for(i = 0;i <= MESS_LENG;i++)
					{
						wifi_Rec_Mess.message_Buffer[i] = UWifi_Rec_Buffer[start_Index + i];
					}
				}
				else
				{
					for(i = 0;i <= MESS_LENG;i++)
					{
						wifi_Rec_Mess.message_Buffer[i] = UWifi_Rec_Buffer[(start_Index + i) % UWifi_REC_MAX_BYTES];
					}
				}
				flag_Rec_mess = TRUE;//置接收帧完成标志位
			}
			
		}		
        WifiRxBuf_old = WifiRxBuf;
		HAL_UART_Receive_IT(&huart2,&WifiRxBuf,1);  // 设置接收1个字节 产生中断回调 开启下一次接收中断
		
	}
	
	//=================================
    // USART:PM25 sensor
    if(UartHandle->Instance == USART_PM25)
    {
//		if(Pm25RxBuf == 0 && UPm25_Rec_Point == 0)
//		{printf("PM25 Data Rec Wrong!");}
//		else
//		{
			UPm25_Rec_Buffer[UPm25_Rec_Point] = Pm25RxBuf;
			UPm25_Rec_Point++;
//		}
		
        if(UPm25_Rec_Point >= (PM25_DATA_LENGTH * PM25_BUFFER_NUM)) { UPm25_Rec_Point = 0; }
		
		HAL_UART_Receive_IT(&huart3,&Pm25RxBuf,1);
    }   
	
	//=================================
    // USART:HCHO sensor
    if(UartHandle->Instance==UART4)
    { 
		UCH2O_Rec_Buffer[UCH2O_Rec_Point] = CH2ORxBuf;
        UCH2O_Rec_Point++;
		
        if(UCH2O_Rec_Point >= CH2O_DATA_LENGTH * CH2O_BUFFER_NUM) { UCH2O_Rec_Point = 0; }
		
		HAL_UART_Receive_IT(&huart4,&CH2ORxBuf,1);
    }       
}

//----------------------------------------------
void  UWifi_Send_String_mess(uint8_t * pstr)
{
	uint16_t  strlength;

    memset(UWifi_Send_Buffer, '\0', UWifi_SEND_MAX_BYTES);
	memcpy((char*)UWifi_Send_Buffer,(char*)pstr,MESS_LENG);
	
	
	HAL_UART_Receive_IT(&HUART_WIFI,&WifiRxBuf,1);
	
	HAL_UART_Transmit_IT(&HUART_WIFI,UWifi_Send_Buffer,MESS_LENG);
}
//----------------------------------------------
void  UWifi_Send_String(uint8_t * pstr)
{
	uint16_t  strlength;

    memset(UWifi_Send_Buffer, '\0', UWifi_SEND_MAX_BYTES);
	strcpy((char*)UWifi_Send_Buffer,(char*)pstr);
	strlength = strlen((char*)UWifi_Send_Buffer);
	
	HAL_UART_Receive_IT(&HUART_WIFI,&WifiRxBuf,1);
	
	HAL_UART_Transmit_IT(&HUART_WIFI,UWifi_Send_Buffer,strlength);
}
//----------------------------------------------
void UDebug_Send_String(uint8_t * pstr)
{
	uint16_t  strlength;

    memset(UDebug_Send_Buffer, '\0', UDebug_SEND_MAX_BYTES);
	strcpy((char*)UDebug_Send_Buffer,(char*)pstr);
	strlength = strlen((char*)UDebug_Send_Buffer);
	//prepare for rev
	//memset(U1_Rec_Buffer,'\0', U1_REC_MAX_BYTES);
	HAL_UART_Receive_IT(&HUART_DEBUG,&debug_RxBuf,1);
	
	HAL_UART_Transmit_IT(&HUART_DEBUG,UDebug_Send_Buffer,strlength);
}
//----------------------------------------------
void flush_Buffer(uint8_t * buffer,uint8_t length)
{
	uint8_t i = 0;
	for(;i < length ;i++)
	{
		*buffer = 0x0;
		buffer++;
	}
}

//----------------------------------------------
//redirect printf to USART PRINTF_USART
int fputc(int ch, FILE *f)
{
   USART_DEBUG->DR=(uint8_t)ch;
   while((USART_DEBUG->SR&0X40)==0);//The printf usart define by PRINT_USART in usart.h
   return ch;
}

void  HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{    
    if(UartHandle->Instance==USART6) {
       
    }
    
    if(UartHandle->Instance==USART2)  // 
    { 
        
    }

    if(UartHandle->Instance==USART3)  // 
    { 
        
    }
	
	if(UartHandle->Instance==UART4)  // 
    { 
        
    }
}

void  Uart_sensor_init()
{
	HAL_UART_Receive_IT(&HUART_PM25,UPm25_Rec_Buffer,1);
	HAL_UART_Receive_IT(&HUART_HCHO,UCH2O_Rec_Buffer,1);
}
/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
