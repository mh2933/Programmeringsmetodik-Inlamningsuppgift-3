/********************************************************************************
* fsm.c: Finite State Machine 
         Steg två är att definiera funktionerna som först var deklarerade i headerfilen. 
         Innehåller funktionalitet för implementering av tillståndsmaskinen
*        för styrning av lysdioderna. Pekare används vid passering av
*        blinkhastigheten för att direkt kunna avbryta en blinkning ifall
*        aktuellt tillstånd övergår från blinkande till annat tillstånd.
*        Fördröjningstiden som refereras till nollställs när detta sker,
*        vilket medför att kvarvarande fördröjningstid sätts till noll.
********************************************************************************/

#include "header.h"

//static är enbart lokal i denna fil, och den sparas i RAM-minnet den existerar hela programmets längd, typ som en global variabel
static state_t state = STATE_OFF;
static uint16_t speed_ms = 0;

/* alla variabler som läggs inne i funktionerna sparas på stacken och försvinner när vi når return; förutom dom som är definerade som static*/
void fsm_reset(void)
{
	state = STATE_OFF;
    speed_ms = 0;	
	LEDS_OFF;
	return;
}

// kollar vilket tillstånd finite state machine befinner sig i
void fsm_update(void)
{
	switch (state)
	{
		case STATE_OFF:
		{
			 if (BUTTON)
			{
				state = STATE_ON;
			}

			break;
		}

		case STATE_ON:
		{
			if (BUTTON)
			{
				state = STATE_OFF;
			}

			break;
		}

		default: // om något går fel i koden så har vi en default som resettar
		{
			fsm_reset();
			break;
		}
	}

	if (state == STATE_OFF) speed_ms = 0;
	else if (state == STATE_ON) speed_ms = 500;
	return;
}

void fsm_set_output(void) // uppdaterar lysdioderna efter det nya tillståndet. 
{
	LEDS_OFF;
	
	if (STATE_ON)
	{
		leds_blink(speed_ms);
	}
	else
	{
		fsm_reset();
	}
	return;
}

