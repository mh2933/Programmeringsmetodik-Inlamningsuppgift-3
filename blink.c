
#include "header.h"

// blink.c implementerar blinksekvensen

bool leds_blink()//const volatile uint16_t* blink_speed_ms
{
	while(true)
	{
	 LEDS_OFF;
	 LED1_ON;
	 _delay_ms(100); // blink_speed_ms

	 LED1_OFF;
	 LED2_ON;
	 _delay_ms(100); // blink_speed_ms

	 LED2_OFF;
	 LED3_ON;
	 _delay_ms(100); // blink_speed_ms

	 LED3_OFF;
	if(BUTTON2)
	{
		LEDS_OFF;
	}
	}
}

/*
void delay_ms(const volatile uint16_t* delay_time_ms)
{
	for (uint16_t i = 0; i < *delay_time_ms; ++i)
	{
		_delay_ms(1);
	}
	return;
}*/
