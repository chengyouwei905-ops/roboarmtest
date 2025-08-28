#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "LED.h"
#include "Timer3.h"
#include "Key.h"
#include "PWM.h"

uint16_t keyval   = 520;
uint16_t angle    = 500;
uint8_t direction = 0;

int main(void)
{
    Serial_Init();
    OLED_Init();
    OLED_Printf(0, 0, OLED_8X16, "Hello, 520");
    OLED_Update();
    LED_Init();
    Timer3_Init();
    Key_Init();
    PWM_Init();

    while (1) {
        keyval = Key_GetNum();
        if (keyval) {
            if (direction == 0) {
                angle += 50;
            } else if (direction == 1) {
                angle -= 50;
            }
            if (angle >= 2500)
                direction = 1;
            else if (angle <= 500)
                direction = 0;
            OLED_Printf(0, 16, OLED_8X16, "%d", angle);
            OLED_Update();
            LED_Turn();
        }
    }
}

void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET) {
        Key_Tick();
        PWM_SetCompare1(angle);
        PWM_SetCompare2(angle);
        PWM_SetCompare3(angle);
        PWM_SetCompare4(angle);
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}
