#include "Func.h"
#include "mode.h"
#include "sensor_DHT20.h"
#include "sensor_JW01.h"
void AutoRun(void)
{
  if(get_work_mode() == WORK_MODE_ZIDONG)
    {
      //当温度<10，或者湿度>65，启动烘干模式
      if(DHT20_get_temperature() < 10 || DHT20_get_humidity() > 65)					//判断温度大于25，湿度大于65
        {
          enter_honggan_mode();
//          AlarmTIMEset();
        }
      //TVOC>0.6，或者CH2O>0.1，或者CO2>700，启动净化模式
      if(JW01_get_TVOC() !=0 && JW01_get_CH2O() !=0 && JW01_get_CO2() !=0)
        {
          if(JW01_get_TVOC() > 700 || JW01_get_CH2O() > 100 || JW01_get_CO2() > 1200)						//判断  恢复
            {
              enter_jinghua_mode();
//          AlarmTIMEset();
            }
        }

    }
  if(get_work_mode() == WORK_MODE_HONGGAN && get_work_type() == AUTO_CONTROL)		//开启烘干后达到条件停止烘干
    {
      //温度>10并且湿度<50，则结束烘干模式返回自动模式
      if(DHT20_get_temperature() > 10 && DHT20_get_humidity() < 45)					//判断湿度小于50
        {
          enter_zidong_mode();
//          AlarmTIMEreset();

        }
    }
  if(get_work_mode() == WORK_MODE_JINGHUA && get_work_type() == AUTO_CONTROL)		//开启净化后达到条件停止净化
    {
      //TVOC<0.4并且CH2O<0.05并且CO2<500，则结束净化模式返回自动模式
      if(JW01_get_TVOC() < 400 && JW01_get_CH2O() < 50 && JW01_get_CO2() < 600)					//判断   恢复
        {
          enter_zidong_mode();
//          AlarmTIMEreset();
        }
    }
}
