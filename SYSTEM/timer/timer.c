#include "timer.h"
#include "config.h"
#include "device_gpio.h"
unsigned int buz_time = 0;

void Timer_BUZ_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	//TIM_OCInitTypeDef  TIM_OCInitStructure;
	//GPIO_InitTypeDef GPIO_InitStructure;

	//Clock
	RCC_APB1PeriphClockCmd(TIMER_BUZ_RCC_APB, ENABLE); 
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
	//定时器定时时间T计算公式：T=(TIM_Period+1)*(TIM_Prescaler+1)/TIMxCLK
	TIM_TimeBaseStructure.TIM_Period = (3600-1);//自动重装载值10--定时时间(10*4800/48M)s 
	TIM_TimeBaseStructure.TIM_Prescaler	 =(2-1);//预分频值，+1为分频系数 
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//TIM向上计数模式
	TIM_TimeBaseInit(TIMER_BUZ, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	
	//中断
	NVIC_Enable(TIMER_BUZ_IRQ, 3, 3);
	
	TIM_ITConfig(TIMER_BUZ,TIM_IT_Update,ENABLE);	//使能中断源


	//TIM_Cmd(TIMER_BUZ, ENABLE);					 	
}
TIMER_BUZ_IRQ_HANDLER							//
{
  if(TIM_GetITStatus(TIMER_BUZ, TIM_IT_Update) != RESET) //是否发生中断
    {

      if(1)
        {
          if(buz_time < 200)
            {
              buz_time++;
              BUZ_ON();
            }
          else
            {
              buz_time++;
              BUZ_OFF();
            }
          if(buz_time == 400)
            {
              buz_time = 0;
            }
        }				      
				TIM_ClearITPendingBit(TIMER_BUZ, TIM_FLAG_Update);     //清除中断待处理


    }


}
