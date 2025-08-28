#include "stm32f10x.h"
#include "PWM.h"

/* PA0~ch1~末端 PA1~ch2~最远端 PA2~ch3~中间 PA3~ch4~最近端*/
void Servo_Init(void)
{
    PWM_Init();
}

/* void Servo_Set1(uint8_t angle)
{

} */
