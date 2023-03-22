#include "Func.h"
#include "mode.h"
#include "sensor_DHT20.h"
#include "sensor_JW01.h"
void AutoRun(void)
{
  if(get_work_mode() == WORK_MODE_ZIDONG)
    {
      //���¶�<10������ʪ��>65���������ģʽ
      if(DHT20_get_temperature() < 10 || DHT20_get_humidity() > 65)					//�ж��¶ȴ���25��ʪ�ȴ���65
        {
          enter_honggan_mode();
//          AlarmTIMEset();
        }
      //TVOC>0.6������CH2O>0.1������CO2>700����������ģʽ
      if(JW01_get_TVOC() !=0 && JW01_get_CH2O() !=0 && JW01_get_CO2() !=0)
        {
          if(JW01_get_TVOC() > 700 || JW01_get_CH2O() > 100 || JW01_get_CO2() > 1200)						//�ж�  �ָ�
            {
              enter_jinghua_mode();
//          AlarmTIMEset();
            }
        }

    }
  if(get_work_mode() == WORK_MODE_HONGGAN && get_work_type() == AUTO_CONTROL)		//������ɺ�ﵽ����ֹͣ���
    {
      //�¶�>10����ʪ��<50����������ģʽ�����Զ�ģʽ
      if(DHT20_get_temperature() > 10 && DHT20_get_humidity() < 45)					//�ж�ʪ��С��50
        {
          enter_zidong_mode();
//          AlarmTIMEreset();

        }
    }
  if(get_work_mode() == WORK_MODE_JINGHUA && get_work_type() == AUTO_CONTROL)		//����������ﵽ����ֹͣ����
    {
      //TVOC<0.4����CH2O<0.05����CO2<500�����������ģʽ�����Զ�ģʽ
      if(JW01_get_TVOC() < 400 && JW01_get_CH2O() < 50 && JW01_get_CO2() < 600)					//�ж�   �ָ�
        {
          enter_zidong_mode();
//          AlarmTIMEreset();
        }
    }
}
