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
	
	//��ʱ����ʱʱ��T���㹫ʽ��T=(TIM_Period+1)*(TIM_Prescaler+1)/TIMxCLK
	TIM_TimeBaseStructure.TIM_Period = (3600-1);//�Զ���װ��ֵ10--��ʱʱ��(10*4800/48M)s 
	TIM_TimeBaseStructure.TIM_Prescaler	 =(2-1);//Ԥ��Ƶֵ��+1Ϊ��Ƶϵ�� 
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIMER_BUZ, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	
	//�ж�
	NVIC_Enable(TIMER_BUZ_IRQ, 3, 3);
	
	TIM_ITConfig(TIMER_BUZ,TIM_IT_Update,ENABLE);	//ʹ���ж�Դ


	//TIM_Cmd(TIMER_BUZ, ENABLE);					 	
}
TIMER_BUZ_IRQ_HANDLER							//
{
  if(TIM_GetITStatus(TIMER_BUZ, TIM_IT_Update) != RESET) //�Ƿ����ж�
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
				TIM_ClearITPendingBit(TIMER_BUZ, TIM_FLAG_Update);     //����жϴ�����


    }


}
