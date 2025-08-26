#include "stm32f10x.h"                  // Device header
#include "Delay.h"

uint8_t keynum = 0;

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
/// @brief use in main while. if press, it will return de keynum for once.
/// @param  void
/// @return the key number you have press.
uint8_t Key_GetNum(void)
{
    uint8_t temp;
    temp = keynum;
    keynum = 0;
    return temp;
}

uint8_t Key_GetState(void)
{
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2) == 0)
	{
        return 1;
    }
	else
        return 0;
}
/// @brief use in timerhandler to turn on the key function.
/// @param  void
void Key_Tick(void)
{
    static uint8_t count;
    static uint8_t nowstate, laststate;

    count++;
	if(count >= 20)
	{
        count = 0;
        laststate = nowstate;
        nowstate  = Key_GetState();
		if(nowstate == 0 && laststate == 1)
		{
            keynum = nowstate;
        }
    }
}
