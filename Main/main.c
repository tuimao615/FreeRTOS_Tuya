#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "wifi.h"
#include "wifi_usart.h"
#include "timers.h"
#include "buzzer.h"
#include "device_gpio.h"
#include "jw01_usart.h"
#include "sensor_DHT20.h"
#include "sensor_JW01.h"
#include "device.h"
#include "mode.h"
#include "Func.h"
//�������
#define TASK1_STACK_SIZE 100
#define TASK1_PRIORITY 1

#define TASK2_STACK_SIZE 100
#define TASK2_PRIORITY 1

#define TASK3_STACK_SIZE 100
#define TASK3_PRIORITY 1


//�����ʱ����������ʱ��
#define MonitorUpdate_RELOAD_TIMER_PERIOD pdMS_TO_TICKS( 1000 )
#define Update_RELOAD_TIMER_PERIOD pdMS_TO_TICKS( 10000 )
#define ModeTask_RELOAD_TIMER_PERIOD pdMS_TO_TICKS( 60000 )
#define HeatTime_RELOAD_TIMER_PERIOD pdMS_TO_TICKS( 1000 )





//������
void MainFunction( void *pvParameters );
void AutoRunFunction( void *pvParameters );
void PirDetectFunction( void *pvParameters );

//����������
static void vMonitorUpdateTimerFunc( TimerHandle_t xTimer );
static void vUpdateFunc( TimerHandle_t xTimer );
static void vModeTaskFunc( TimerHandle_t xTimer );
static void vHeatTimeFunc( TimerHandle_t xTimer );



int main(void)
{
  TimerHandle_t xMonitorUpdateTimer,xUpdateTimer;
  TimerHandle_t xModeTaskTimer;
  TimerHandle_t xHeatTimeTimer;




  delay_init();	    	 //��ʱ������ʼ��
  Device_Init();
  Device_GPIO_Config();
  Key_Init();          		//��ʼ���밴�����ӵ�Ӳ���ӿ�
  Sensor_DHT20_Init();		//��ʪ�ȴ�������ʼ��
  Sensor_JW01_Init();			//TVOC��������ʼ��
  uart3_init(115200);

  WIFI_Init();
  WIFI_HW_Poweron();
  wifi_protocol_init();
  WIFI_USART_Enable_Rx();

  JW01_HW_Poweron();
  JW01_USART_Enable_Rx();



  /************* �������� ****************/
  xTaskCreate( MainFunction, "Task1", TASK1_STACK_SIZE, NULL, TASK1_PRIORITY, NULL );
  xTaskCreate( AutoRunFunction, "Task2", TASK2_STACK_SIZE, NULL, TASK2_PRIORITY, NULL );
  xTaskCreate( PirDetectFunction, "Task3", TASK3_STACK_SIZE, NULL, TASK3_PRIORITY, NULL );


  /************* ������ʱ�� ****************/
  //�����������¶�ʱ����ÿ1�����
  xMonitorUpdateTimer = xTimerCreate("AutoReload",MonitorUpdate_RELOAD_TIMER_PERIOD,pdTRUE,0,vMonitorUpdateTimerFunc);
  //�ϴ����ݣ�ÿ10��
  xUpdateTimer = xTimerCreate("Update",Update_RELOAD_TIMER_PERIOD,pdTRUE,0,vUpdateFunc);
  //����ģʽ������ÿ60��
  xModeTaskTimer = xTimerCreate("ModeTask",ModeTask_RELOAD_TIMER_PERIOD,pdTRUE,0,vModeTaskFunc);
  xHeatTimeTimer = xTimerCreate("HeatTime",HeatTime_RELOAD_TIMER_PERIOD,pdTRUE,0,vHeatTimeFunc);




  /* ������ʱ�� */
  xTimerStart(xMonitorUpdateTimer, 0);
  xTimerStart(xUpdateTimer, 0);
  xTimerStart(xModeTaskTimer, 0);
  xTimerStart(xHeatTimeTimer, 0);




  /* ���������� */
  vTaskStartScheduler();

  return 0;
}
  /************* ������ ****************/

void MainFunction( void *pvParameters )
{
  while(1)
    {
      wifi_uart_service();
      //��ⰴ��
      Key_Task();
      //��������ģ���Ƿ���
      Buzzer_Output();
      vTaskDelay(pdMS_TO_TICKS(100));
    }
  vTaskDelete( NULL );
}
void PirDetectFunction( void *pvParameters )
{
  while(1)
    {
      PirDetect();
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
  vTaskDelete( NULL );
}

void AutoRunFunction( void *pvParameters )
{
  while(1)
    {
      AutoRun();
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
  vTaskDelete( NULL );
}




  /************* ��ʱ������ ****************/


static void vMonitorUpdateTimerFunc( TimerHandle_t xTimer )
{
  DHT20_update();
  JW01_update();
}
static void vUpdateFunc( TimerHandle_t xTimer )
{
  all_data_update();
}
static void vModeTaskFunc( TimerHandle_t xTimer )
{
  Mode_Task();
}
static void vHeatTimeFunc( TimerHandle_t xTimer )
{
  TimeHeat();
}


