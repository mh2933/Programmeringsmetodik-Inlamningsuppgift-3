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
static int count;

ISR(PCINT0_vect)
{
	if (!button_is_pressed(&b1))
	{
		count++;
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
		// if satserna -> efter 5 knapptryck skiftar blinksekvensen riktning
	   if (leds_enabled && count > 4)
	   {
		   led_vector_blink_sequentially(&v1, 100);
		   
		    if (count > 9)
		    {
			    count = 0;
		    }
	   }
	   if (!leds_enabled && count > 4)
	   {
		   led_vector_blink_sequentially(&v1, 100);
		   
		   if (count > 9)
		   {
			   count = 0;
		   }
	   }
	   else if (!leds_enabled && count < 5)
	   {
		   led_vector_blink_sequentially_reversed(&v1, 200);
		   
	   }
	   else if (leds_enabled && count < 5)
	   {
		    led_vector_blink_sequentially_reversed(&v1, 200);
	   }
	}

	return 0;
}
