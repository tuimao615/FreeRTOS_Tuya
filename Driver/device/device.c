#include "device.h"
#include "device_gpio.h"
#include "delay.h"

static int g_device_initialized = 0;

static u8 g_light_on = 0;
static u8 g_heat_on = 0;

static u8 g_fan_on = 0;
static u8 g_flz_on = 0;
static u8 g_cy_on = 0;
static u8 g_xx_on = 0;
static u8 g_uv_on = 0;



void Device_Init(void)
{
	Device_GPIO_Config();
	
	HEATONE_OFF();
	HEATTWO_OFF();
	FAN_OFF();
	FLZ_OFF();
	CY_OFF();
	XX_OFF();
	UV_OFF();
	BUZ_OFF();

	g_device_initialized = 1;
}

u8 LIGHT_is_On(void)
{
	return g_light_on;
}

u8 HEAT_is_On(void)
{
	return g_heat_on;
}

u8 FAN_is_On(void)
{
	return g_fan_on;
}

u8 FLZ_is_On(void)
{
	return g_flz_on;
}

u8 CY_is_On(void)
{
	return g_cy_on;
}

u8 XX_is_On(void)
{
	return g_xx_on;
}

u8 UV_is_On(void)
{
	return g_uv_on;
}


void HEAT_turn(u8 on)
{
	if(g_device_initialized == 0)
		return;
		
	if(g_heat_on == on)
		return;

	g_heat_on = on;
	
	if(g_heat_on)
	{
		HEATONE_ON();
		HEATTWO_OFF();
		//HEATTWO_ON();
	}
	else
	{
		HEATONE_OFF();
		HEATTWO_OFF();
	}
		
}

void FAN_turn(u8 on)
{
	if(g_device_initialized == 0)
		return;
	
	if(g_fan_on == on)
		return;

	g_fan_on = on;
	
	if(g_fan_on)
		FAN_ON();
	else
		FAN_OFF();
}

void FLZ_turn(u8 on)
{
	if(g_device_initialized == 0)
		return;

	if(g_flz_on == on)
		return;
	
	g_flz_on = on;
	
	if(g_flz_on)
		FLZ_ON();
	else
		FLZ_OFF();	
}

void CY_turn(u8 on)
{
	if(g_device_initialized == 0)
		return;
	
	if(g_cy_on == on)
		return;
	
	g_cy_on = on;
	
	if(g_cy_on)
		CY_ON();
	else
		CY_OFF();	
}

void XX_turn(u8 on)
{
	if(g_device_initialized == 0)
		return;
	
	if(g_xx_on == on)
		return;
	
	g_xx_on = on;
	
	if(g_xx_on)
		XX_ON();
	else
		XX_OFF();	
}

void UV_turn(u8 on)
{
	if(g_device_initialized == 0)
		return;

	if(g_uv_on == on)
		return;
		
	g_uv_on = on;
	
	if(g_uv_on)
		UV_ON();
	else
		UV_OFF();	
}

void ALL_turn_off(void)
{
	HEAT_turn(0);
	FAN_turn(0);
	FLZ_turn(0);
	CY_turn(0);
	XX_turn(0);
	UV_turn(0);
}
