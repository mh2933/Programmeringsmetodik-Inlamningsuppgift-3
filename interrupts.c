#include "header.h"


/* avbrottsrutin för PCI-avbrott */
// om pin 11 - 13 trycks ned så uppdateras tillståndsmaskinens tillstånd. 
ISR(PCINT0_vect) // Pin 11 - 13.
{
	//led_enabled = !led_enabled;
	if (BUTTON_PRESSED)
	{
		leds_blink();
	}
	else if(leds_blink() && BUTTON)
	{
		LEDS_OFF;
	}
	//return;
}

ISR (INT0_vect) // Avbrottsrutin för externt avbrott på PIN 2 / PORTD2.
{

	//led_enabled = !led_enabled;
	if (BUTTON2_PRESSED)
	{
		LEDS_OFF;
	}
	else if(leds_blink() && BUTTON)
	{
		LEDS_OFF;
	}
	//return;
}