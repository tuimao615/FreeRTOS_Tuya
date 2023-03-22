#include "Func.h"
#include "mode.h"
#include "device_gpio.h"
#include "device.h"

int pir_window = 0;

void PirDetect(void)
{
  if(GPIO_ReadInputDataBit(PIR_GPIO, PIR_GPIO_PIN) == 0 && pir_window == 0)		//û��⵽�˲�ֹͣCY��UV ���߻ָ�
    {
      pir_window = 3;
      if(get_work_mode() == WORK_MODE_JINGHUA)
        {
          FAN_turn(1);							//��������
          FLZ_turn(1);
          //����˿̳�����Ҫ��������
          if(get_cy_status() == ON)
            {
              CY_turn(1);							//��������
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
      //��⵽��ֹͣCY��UV
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
