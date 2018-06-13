/**
  ******************************************************************************
  * File Name          : DAC.h
  * Description        : This file provides code for the configuration
  *                      of the DAC instances.
  ******************************************************************************
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __dac_H
#define __dac_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern DAC_HandleTypeDef hdac;

/* USER CODE BEGIN Private defines */
//#define     SAMPLE_128        // 一个周期采样128点
#define     SAMPLE_16           // 一个周期采样16点

#ifdef   SAMPLE_256
  #define  SAMPLE_DOTS     256
  const  static  uint16_t  Sine12bit[SAMPLE_DOTS] = 
  { 
    2048, 2098, 2148, 2198, 2248, 2298, 2348, 2398, 2447, 2496,
    2545, 2594, 2642, 2690, 2737, 2785, 2831, 2877, 2923, 2968,
    3013, 3057, 3100, 3143, 3185, 3227, 3267, 3307, 3347, 3385,
    3423, 3460, 3496, 3531, 3565, 3598, 3631, 3662, 3692, 3722,
    3750, 3778, 3804, 3829, 3854, 3877, 3899, 3920, 3940, 3958,
    3976, 3992, 4007, 4021, 4034, 4046, 4056, 4065, 4073, 4080,
    4086, 4090, 4093, 4095, 4095, 4095, 4093, 4090, 4086, 4080,
    4073, 4065, 4056, 4046, 4034, 4021, 4007, 3992, 3976, 3958,
    3940, 3920, 3899, 3877, 3854, 3829, 3804, 3778, 3750, 3722,
    3692, 3662, 3631, 3598, 3565, 3531, 3496, 3460, 3423, 3385,
    3347, 3307, 3267, 3227, 3185, 3143, 3100, 3057, 3013, 2968,
    2923, 2877, 2831, 2785, 2737, 2690, 2642, 2594, 2545, 2496,
    2447, 2398, 2348, 2298, 2248, 2198, 2148, 2098, 2047, 1997,
    1947, 1897, 1847, 1797, 1747, 1697, 1648, 1599, 1550, 1501,
    1453, 1405, 1358, 1310, 1264, 1218, 1172, 1127, 1082, 1038,
     995,  952,  910,  868,  828,  788,  748,  710,  672,  635,
     599,  564,  530,  497,  464,  433,  403,  373,  345,  317,
     291,  266,  241,  218,  196,  175,  155,  137,  119,  103,
      88,   74,   61,   49,   39,   30,   22,   15,    9,    5,
       2,    0,    0,    0,    2,    5,    9,   15,   22,   30,
      39,   49,   61,   74,   88,  103,  119,  137,  155,  175,
     196,  218,  241,  266,  291,  317,  345,  373,  403,  433,
     464,  497,  530,  564,  599,  635,  672,  710,  748,  788,
     828,  868,  910,  952,  995, 1038, 1082, 1127, 1172, 1218,
    1264, 1310, 1358, 1405, 1453, 1501, 1550, 1599, 1648, 1697,
    1747, 1797, 1847, 1897, 1947, 1997,
  }; 
#elif defined  SAMPLE_128
    #define  SAMPLE_DOTS     128
    const  static  uint16_t  Sine12bit[SAMPLE_DOTS] = 
    { 
        2047, 2147, 2248, 2347, 2446, 2544, 2641, 2737, 2830, 2922,
        3012, 3099, 3184, 3266, 3346, 3422, 3494, 3564, 3629, 3691,
        3749, 3803, 3852, 3897, 3938, 3974, 4006, 4033, 4055, 4072,
        4084, 4092, 4094, 4092, 4084, 4072, 4055, 4033, 4006, 3974,
        3938, 3897, 3852, 3803, 3749, 3691, 3629, 3564, 3494, 3422,
        3346, 3266, 3184, 3099, 3012, 2922, 2830, 2737, 2641, 2544,
        2446, 2347, 2248, 2147, 2047, 1947, 1846, 1747, 1648, 1550,
        1453, 1357, 1264, 1172, 1082,  995,  910,  828,  748,  672,
         600,  530,  465,  403,  345,  291,  242,  197,  156,  120,
          88,   61,   39,   22,   10,    2,    0,    2,   10,   22,
          39,   61,   88,  120,  156,  197,  242,  291,  345,  403,
         465,  530,  600,  672,  748,  828,  910,  995, 1082, 1172,
        1264, 1357, 1453, 1550, 1648, 1747, 1846, 1947,
    };
#elif defined  SAMPLE_64  
    #define  SAMPLE_DOTS     64
    const  static  uint16_t  Sine12bit[SAMPLE_DOTS] = 
    {   //    x=[0:2*pi/64:2*pi];  y=round(sin(x)*2047+2047) ; matlab 四舍五入法 获取
        2047, 2248, 2446, 2641, 2830, 3012, 3184, 3346, 3494, 3629,
        3749, 3852, 3938, 4006, 4055, 4084, 4094, 4084, 4055, 4006,
        3938, 3852, 3749, 3629, 3494, 3346, 3184, 3012, 2830, 2641,
        2446, 2248, 2047, 1846, 1648, 1453, 1264, 1082,  910,  748,
         600,  465,  345,  242,  156,   88,   39,   10,    0,   10,
          39,   88,  156,  242,  345,  465,  600,  748,  910, 1082,
        1264, 1453, 1648, 1846,
    };
#elif defined  SAMPLE_32  
    #define  SAMPLE_DOTS     32
    const  static  uint16_t  Sine12bit[SAMPLE_DOTS] = 
    {   //    x=[0:2*pi/32:2*pi];  y=round(sin(x)*2047+2047) ; matlab 四舍五入法 获取
        2047, 2446, 2830, 3184, 3494, 3749, 3938, 4055, 4094, 4055, 
        3938, 3749, 3494, 3184, 2830, 2446, 2047, 1648, 1264,  910,
         600,  345,  156,   39,    0,   39,  156,  345,  600,  910,
        1264, 1648,
    };    
#elif defined  SAMPLE_16
    #define  SAMPLE_DOTS     16   //
    //    x=[0:2*pi/16:2*pi];  y=round(sin(x)*2047+2047) ; matlab 四舍五入法 获取
    const  static  uint16_t  Sine12bit[SAMPLE_DOTS] = 
    {  2047, 2830, 3494, 3938, 4094, 3938, 3494, 2830, 2047, 1264,  600,  156,  0,  156,  600, 1264,  };
#elif defined  SAMPLE_8
        #define  SAMPLE_DOTS     8   //
    //    x=[0:2*pi/16:2*pi];  y=round(sin(x)*2047+2047) ; matlab 四舍五入法 获取
    const  static  uint16_t  Sine12bit[SAMPLE_DOTS] = 
    {  2047,  3494,  4094,  3494,  2047,  600,   0,    600,  };
#elif defined  SAMPLE_100
    #define  SAMPLE_DOTS     100
    const  static  uint16_t  Sine12bit[SAMPLE_DOTS] = 
    { 
        2047, 2176, 2304, 2431, 2556, 2680, 2801, 2919, 3033, 3144,
        3250, 3352, 3448, 3539, 3624, 3703, 3775, 3841, 3899, 3950,
        3994, 4030, 4058, 4078, 4090, 4094, 4090, 4078, 4058, 4030,
        3994, 3950, 3899, 3841, 3775, 3703, 3624, 3539, 3448, 3352,
        3250, 3144, 3033, 2919, 2801, 2680, 2556, 2431, 2304, 2176,
        2047, 1918, 1790, 1663, 1538, 1414, 1293, 1175, 1061,  950,
         844,  742,  646,  555,  470,  391,  319,  253,  195,  144,
         100,   64,   36,   16,    4,    0,    4,   16,   36,   64,
         100,  144,  195,  253,  319,  391,  470,  555,  646,  742,
         844,  950, 1061, 1175, 1293, 1414, 1538, 1663, 1790, 1918,
    };
    
#endif
/* USER CODE END Private defines */

extern void Error_Handler(void);

void MX_DAC_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ dac_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
