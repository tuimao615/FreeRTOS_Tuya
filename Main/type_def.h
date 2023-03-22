#ifndef __TYPE_DEF_H
#define	__TYPE_DEF_H

#include "sys.h"

typedef enum
{
  WORK_MODE_ZIDONG = 0,
  WORK_MODE_JINGHUA,
  WORK_MODE_XIANGXUN,
  WORK_MODE_SHAJUN,
  WORK_MODE_HONGGAN,
  WORK_MODE_CHUNJING,
  WORK_MODE_MAX
} WorkMode;

//分辨是云端改变的模式还是自动改变的模式
typedef enum
{
  WIFI_CONTROL = 0,
  AUTO_CONTROL
} WorkType;

typedef enum
{
  OFF = 0,
  ON
} SensorStatus;

typedef enum
{
  KEY_NONE = 0,
  KEY_RESET,
  KEY_NUM_0,
  KEY_NUM_1,
  KEY_NUM_2,
  KEY_NUM_3,
  KEY_NUM_4,
  KEY_NUM_5,
  KEY_NUM_6,
  KEY_NUM_7,
  KEY_NUM_8,
  KEY_NUM_9,
  KEY_MODE_JINGHUA,  //右边五个按键
  KEY_MODE_XIANGXUN,
  KEY_MODE_SHAJUN,
  KEY_MODE_HONGGAN,
  KEY_MODE_ZIDONG,
  KEY_ALT_CONFIG,
  KEY_MAX
} MmiKey;


typedef enum
{
  LED_NUMBER_1,	//数字
  LED_NUMBER_2,
  LED_NUMBER_3,
  LED_NUMBER_4,
  LED_DOT,
  LED_TEMPERATURE, //温湿度
  LED_HUMIDITY,
  LED_BT, //四个状态指示
  LED_WIFI,
  LED_CLOCK,
  LED_ALARM,
  LED_MODE_JINGHUA, //五个功能键
  LED_MODE_XIANGXUN,
  LED_MODE_SHAJUN,
  LED_MODE_HONGGAN,
  LED_MODE_ZIDONG,
  LED_MAX
} LedLight;


typedef enum
{
  EVENT_NONE = 0,
  /* BT */
  EVENT_BT_CONNECT,
  EVENT_BT_DISCONNECT,
  /* WIFI */
  EVENT_WIFI_RELOAD_FACTORYSET,
  EVENT_WIFI_SMART_BLE_LINK,
  EVENT_WIFI_CONNECT,
  EVENT_WIFI_DISCONNECT,
  /* Alarm */
  EVENT_ALARM_HOT,
  EVENT_ALARM_POLLUTION,
  /* Mode */
  EVENT_MODE_JINGHUA,
  EVENT_MODE_XIANGXUN,
  EVENT_MODE_SHAJUN,
  EVENT_MODE_HONGGAN,
  EVENT_MODE_ZIDONG,
  EVNET_MAX
} MmiEvent;



#define MSG_WIFI_RELOAD_FACTORYSET  	((uint16_t)0x0001) /* WIFI */
#define MSG_WIFI_SMART_BLE_LINK  			((uint16_t)0x0002)

#define MSG_ALARM_HOT               	((uint16_t)0x0010) /* Alarm */
#define MSG_ALARM_POLLUTION          	((uint16_t)0x0020)

#define MSG_MODE_MASK									((uint16_t)0x8F00) /* Mode */
#define MSG_MODE_JINGHUA              ((uint16_t)0x0100)
#define MSG_MODE_XIANGXUN             ((uint16_t)0x0200)
#define MSG_MODE_SHAJUN               ((uint16_t)0x0400)
#define MSG_MODE_HONGGAN              ((uint16_t)0x0800)
#define MSG_MODE_ZIDONG               ((uint16_t)0x8000)

#endif
