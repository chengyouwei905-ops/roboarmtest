#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "LED.h"
#include "Timer3.h"
#include "Key.h"

uint16_t test = 520;

int main(void)
{
    Serial_Init();
    OLED_Init();
    OLED_Printf(0, 0, OLED_8X16, "Hello, %3d", test);
    OLED_Update();
    LED_Init();
    Timer3_Init();
    Key_Init();

    while (1) {
        test = Key_GetNum();
        if (test) {
            LED_Turn();
        }
    }
}

void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET) {
        Key_Tick();
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}
