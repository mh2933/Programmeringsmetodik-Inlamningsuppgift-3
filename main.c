/********************************************************************************
* main.c: Demonstration av dynamisk vektor för lagring och styrning av multipla
*         lysdioder.
********************************************************************************/
#include "led.h"
#include "button.h"
#include "led_vector.h"

/* globala variabler */
static struct button b1;
static volatile bool leds_enabled = false;


ISR(PCINT0_vect)
{
	if (button_is_pressed(&b1))
	{
		leds_enabled = !leds_enabled; // Inverterar mellan true och false.
	}
}


/********************************************************************************
* main: Ansluter tre lysdioder till pin 8 - 10 och lagrar i en dynamisk vektor.
*       Ansluter en tryckknapp till pin 13. Vid nedtryckning av tryckknappen
*       blinkar lysdioderna i en slinga var 100:e millisekund, annars blinkar
*       de kollektivt var 500:e millisekund.
********************************************************************************/
int main(void)
{
	struct led l1, l2, l3;
	struct led_vector v1;

    button_init(&b1, 13);
    button_enable_interrupt(&b1);

	led_init(&l1, 8);
	led_init(&l2, 9);
	led_init(&l3, 10);
	
	led_vector_init(&v1);
	led_vector_push(&v1, &l1);
	led_vector_push(&v1, &l2);
	led_vector_push(&v1, &l3);
		

	while (1)
	{
	   
	   if (leds_enabled)
	   {
		   led_vector_blink_sequentially(&v1, 100);
	   }
	   else
	   {
		   led_vector_blink_colletively(&v1, 500); 
	   }
	}

	return 0;
}
