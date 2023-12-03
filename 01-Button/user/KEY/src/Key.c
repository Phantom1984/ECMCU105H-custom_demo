#include "main.h"    //�൱��stm32�е�#include "stm32f10x.h"
#include "key.h"

KEY_State Key_Num(GPIO_Handle *handle,GPIO_PIN pin)
{
    if(HAL_GPIO_GetPinValue(handle,pin) == GPIO_LOW_LEVEL)    //��Ӳ���ṹ֪,��������ʱGPIO����͵�ƽ
    {
        BASE_FUNC_DELAY_MS(30);  //����
        if(HAL_GPIO_GetPinValue(handle,pin) == GPIO_LOW_LEVEL) //�����Ȼ����
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