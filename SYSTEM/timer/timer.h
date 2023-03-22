#ifndef __TIMER_H
#define __TIMER_H

#include "sys.h"


#define TIMER_BUZ							TIM2
#define TIMER_BUZ_RCC_APB		  RCC_APB1Periph_TIM2
#define TIMER_BUZ_IRQ					TIM2_IRQn
#define TIMER_BUZ_IRQ_HANDLER	void TIM2_IRQHandler(void)

void Timer_BUZ_Config(void);
#endif
