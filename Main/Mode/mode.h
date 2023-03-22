#ifndef __MODE_H
#define __MODE_H

#include "type_def.h"

#define HEAT_TIME				120					//加热片单片加热时长 单位/秒


void Mode_Task(void);

WorkMode get_work_mode(void);
WorkType get_work_type(void);
SensorStatus get_cy_status(void);

void set_work_type(WorkType type);

void enter_zidong_mode(void);
void enter_jinghua_mode(void);
void enter_xiangxun_mode(void);
void enter_shajun_mode(void);
void enter_honggan_mode(void);
void enter_chunjing_mode(void);

void run_zidong_mode(void);
void run_jinghua_mode(void);
void run_xiangxun_mode(void);
void run_shajun_mode(void);
void run_honggan_mode(void);
void run_chunjing_mode(void);

#endif
