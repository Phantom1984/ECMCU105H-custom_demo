/**
  * @copyright Copyright (c) 2022, HiSilicon (Shanghai) Technologies Co., Ltd. All rights reserved.
  * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
  * following conditions are met:
  * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
  * disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
  * following disclaimer in the documentation and/or other materials provided with the distribution.
  * 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote
  * products derived from this software without specific prior written permission.
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
  * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
  * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
  * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  * @file    sample_timer_interrupt.c
  * @author  MCU Driver Team
  * @brief   timer sample module.
  * @details This file provides users with sample code to help use TIMER function:
  *          1) TIMER runs period and triggers an interrupt every second.
  *          2) Change the period during TIMER running
  *          Phenomenon:
  *          The interrupt handler is executed every 1 second, after 10 second, the interrupt handler execute
  *          every 0.5 second and print "In interrupt" on the serial port.
  */
#include "sample_timer_interrupt.h"

unsigned char second = 0;
unsigned char minute = 0;
unsigned char hour   = 0;
extern unsigned char rxStr[20];
extern char RxDataPkg[20];

void TIMER0_InterruptProcess(void *handle);

/**
  * @brief Timer run and triggers an interrupt.
  * @param None.
  * @retval None.
  */

void Run_Clock(void)
{
    if(second==60)
    { 
       ++minute;
       second = 0;
       if(minute==60)
       {
          ++hour;
          minute = 0;
          if(hour==24)
          {
            hour=0;minute=0;second=0;
          }
       }
    }
}
//鲁棒性还有问题待优化,目前尽量不要输入错误的数据格式
/*数据格式*/
/*
          0! 暂停
          1! 启动
  @xx-xx-xx! 设置时间
*/
void Set_Time(void)
{
    // if(RxDataPkg[0]=='@')
    // {
    //     //时钟数据解析实现
    //     // unsigned char h=hour,m=minute,s=second;    //创建副本,保存当前时刻
    //     // sscanf(RxDataPkg, "@%hhu-%hhu-%hhu!", &h, &m, &s);
    //     // if(h>24||m>60||s>60)
    //     // {
    //     //   DBG_PRINTF("  Please Enter the Correct Time!\r\n");
    //     // }
    //     // else
    //     // {
    //     //   hour=h;  minute=m;  second=s;     //写入新时刻
    //     //   DBG_PRINTF("  Time Set!\r\n");
    //     // }
    //     //检查帧尾是否存在
    //     if (RxDataPkg[strlen(RxDataPkg) - 1] != '!')
    //     {
    //         DBG_PRINTF("Incomplete data frame.\r\n");
    //         return;
    //     }
    //     // 时钟数据解析实现
    //     unsigned char h = hour, m = minute, s = second; // 创建副本,保存当前时刻
    //     if (sscanf(RxDataPkg, "@%hhu-%hhu-%hhu!", &h, &m, &s) == 3)
    //     {
    //         if (h > 24 || m > 60 || s > 60)
    //         {
    //             DBG_PRINTF("Please Enter the Correct Time!\r\n");
    //             return;
    //         }
    //         else
    //         {
    //             hour = h;
    //             minute = m;
    //             second = s;
    //             DBG_PRINTF("Time Set!\r\n");
    //         }
    //     }
    //     else
    //     {
    //         DBG_PRINTF("Incorrect Time format. Please enter in the format '@HH-MM-SS!'\r\n");
    //         return;
    //     }
    // }
    // else if(RxDataPkg[0]=='0')
    // {
    //     HAL_TIMER_Stop(&g_timerHandle);
    //     DBG_PRINTF("  Time Stop!\r\n");
    // }
    // else if(RxDataPkg[0]=='1')
    // {
    //     HAL_TIMER_Start(&g_timerHandle);
    //     DBG_PRINTF("  Time Go on!\r\n");
    // }
    // else
    // {
    //   DBG_PRINTF("Please Enter right format!\r\n");
    // }
    // memset(RxDataPkg,0,20);  //清空数组
    if(RxDataPkg[0]=='@')
    {
        //时钟数据解析实现
        unsigned char h=hour,m=minute,s=second;    //创建副本,保存当前时刻
        sscanf(RxDataPkg, "@%hhu-%hhu-%hhu!", &h, &m, &s);
        if(h>24||m>60||s>60)
        {
          DBG_PRINTF("  Please Enter the Correct Time!\r\n");
        }
        else
        {
          hour=h;  minute=m;  second=s;     //写入新时刻
          DBG_PRINTF("  Time Set!\r\n");
        }
    }
    else if(RxDataPkg[0]=='0')
    {
        HAL_TIMER_Stop(&g_timerHandle);
        DBG_PRINTF("  Time Stop!\r\n");
    }
    else if(RxDataPkg[0]=='1')
    {
        HAL_TIMER_Start(&g_timerHandle);
        DBG_PRINTF("  Time Go on!\r\n");
    }
    else
    {
        DBG_PRINTF("Please Enter right format!\r\n");
    }
    memset(RxDataPkg,0,20);  //清空数组
}
void TIMER_SampleMain(void)
{
    TIMER_Handle timerHandle;

    SystemInit();
    DBG_PRINTF("TIMER_SampleMain begin\r\n");
    HAL_TIMER_Start(&g_timerHandle);
}

/**
  * @brief Timer Interrupt callback function
  * @param handle Handle of Timer
  * @retval None.
  */
void TIMER0_InterruptProcess(void *handle)
{
    /* USER CODE BEGIN TIMER0_InterruptProcess */
    TIMER_Handle *timerHandle = (TIMER_Handle *)handle;

    TIMER_ASSERT_PARAM(timerHandle != NULL);
    TIMER_ASSERT_PARAM(timerHandle->baseAddress != NULL);

    HAL_TIMER_IrqClear(timerHandle);
    second++;
    Run_Clock();
    DBG_PRINTF("Time:%02d-%02d-%02ds\r\n", hour, minute, second);   
    /* USER CODE END TIMER0_InterruptProcess */
}
