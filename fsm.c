/********************************************************************************
* fsm.c: Finite State Machine 
         Steg tv� �r att definiera funktionerna som f�rst var deklarerade i headerfilen. 
         Inneh�ller funktionalitet f�r implementering av tillst�ndsmaskinen
*        f�r styrning av lysdioderna. Pekare anv�nds vid passering av
*        blinkhastigheten f�r att direkt kunna avbryta en blinkning ifall
*        aktuellt tillst�nd �verg�r fr�n blinkande till annat tillst�nd.
*        F�rdr�jningstiden som refereras till nollst�lls n�r detta sker,
*        vilket medf�r att kvarvarande f�rdr�jningstid s�tts till noll.
********************************************************************************/

#include "header.h"

//static �r enbart lokal i denna fil, och den sparas i RAM-minnet den existerar hela programmets l�ngd, typ som en global variabel
static state_t state = STATE_OFF;
static uint16_t speed_ms = 0;

/* alla variabler som l�ggs inne i funktionerna sparas p� stacken och f�rsvinner n�r vi n�r return; f�rutom dom som �r definerade som static*/
void fsm_reset(void)
{
	state = STATE_OFF;
    speed_ms = 0;	
	LEDS_OFF;
	return;
}

// kollar vilket tillst�nd finite state machine befinner sig i
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

		default: // om n�got g�r fel i koden s� har vi en default som resettar
		{
			fsm_reset();
			break;
		}
	}

	if (state == STATE_OFF) speed_ms = 0;
	else if (state == STATE_ON) speed_ms = 500;
	return;
}

void fsm_set_output(void) // uppdaterar lysdioderna efter det nya tillst�ndet. 
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

