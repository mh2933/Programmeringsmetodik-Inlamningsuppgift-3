#include "header.h"


/* avbrottsrutin f�r PCI-avbrott */
// om pin 11 - 13 trycks ned s� uppdateras tillst�ndsmaskinens tillst�nd. 
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

ISR (INT0_vect) // Avbrottsrutin f�r externt avbrott p� PIN 2 / PORTD2.
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