#include "main.h"    //相当于stm32中的#include "stm32f10x.h"
#include "key.h"

KEY_State Key_Num(GPIO_Handle *handle,GPIO_PIN pin)
{
    if(HAL_GPIO_GetPinValue(handle,pin) == GPIO_LOW_LEVEL)    //由硬件结构知,按键按下时GPIO输入低电平
    {
        BASE_FUNC_DELAY_MS(30);  //消抖
        if(HAL_GPIO_GetPinValue(handle,pin) == GPIO_LOW_LEVEL) //如果仍然按下
        {
            while(!HAL_GPIO_GetPinValue(handle,pin));
            return KEY_DOWN;
        }
        return KEY_UP;
    }
}

void LED_Turn(GPIO_Handle *handle,GPIO_PIN pin)
{
    if(HAL_GPIO_GetPinValue(handle,pin)==1)
        HAL_GPIO_SetValue(handle,pin,0);
    else
        HAL_GPIO_SetValue(handle,pin,1);
}