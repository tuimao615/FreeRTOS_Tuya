#include "Func.h"
#include "mode.h"
#include "device_gpio.h"
#include "device.h"

int pir_window = 0;

void PirDetect(void)
{
  if(GPIO_ReadInputDataBit(PIR_GPIO, PIR_GPIO_PIN) == 0 && pir_window == 0)		//没检测到人不停止CY、UV 或者恢复
    {
      pir_window = 3;
      if(get_work_mode() == WORK_MODE_JINGHUA)
        {
          FAN_turn(1);							//开启风扇
          FLZ_turn(1);
          //如果此刻臭氧需要开启则开启
          if(get_cy_status() == ON)
            {
              CY_turn(1);							//开启臭氧
            }
        }
      if(get_work_mode() == WORK_MODE_SHAJUN)
        {
          UV_turn(1);
        }
    }
  else if(GPIO_ReadInputDataBit(PIR_GPIO, PIR_GPIO_PIN) == 1)
    {
      pir_window = 3;
      //检测到人停止CY、UV
      if(get_work_mode() == WORK_MODE_JINGHUA)
        {
          FAN_turn(0);
          FLZ_turn(0);
          CY_turn(0);
        }
      if(get_work_mode() == WORK_MODE_SHAJUN)
        {
          UV_turn(0);
        }
    }
  pir_window --;
}
