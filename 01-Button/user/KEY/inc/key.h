#ifndef __KEY_H
#define __KEY_H

typedef enum {
    KEY_DOWN = 0,
    KEY_UP = 1,
} KEY_State;

KEY_State Key_Num(GPIO_Handle *handle, GPIO_PIN pin);
void LED_Turn(GPIO_Handle *handle,GPIO_PIN pin);
#endif
