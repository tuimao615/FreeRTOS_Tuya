#include "Func.h"
#include "mode.h"
#include "device_gpio.h"

int heat_flag = 1;					//加热片片选标志
int heat_time = HEAT_TIME;

void TimeHeat(void)
{
  if(get_work_mode() == WORK_MODE_HONGGAN)
    {
      if(heat_flag == 1)
        {
          if(heat_time == 5)
            {
              heat_time --;
              HEATONE_OFF();

            }
          else if(heat_time == 0)
            {
              HEATTWO_ON();
              heat_flag = 0;
              heat_time = HEAT_TIME;
            }
          else
            {
              heat_time --;
            }
        }
      if(heat_flag == 0)
        {
          if(heat_time == 5)
            {

              heat_time --;
              HEATTWO_OFF();

            }
          else if(heat_time == 0)
            {
              HEATONE_ON();
              heat_flag = 1;
              heat_time = HEAT_TIME;
            }
          else
            {
              heat_time --;
            }
        }
    }
}
