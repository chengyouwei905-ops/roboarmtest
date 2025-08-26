#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint16_t test = 520;

int main(void)
{
    Serial_Init();
    OLED_Init();
    OLED_Printf(0, 0, OLED_8X16, "Hello, %3d", test);
    OLED_Update();
    while (1) {
        Serial_Printf("Hello,world!");
		Delay_ms(100);
    }
}
