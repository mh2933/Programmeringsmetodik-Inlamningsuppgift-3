#include "header.h"


/* static g�r funktionen lokal till setup.c filen, inline klistrar in inneh�llet
och kan bara anropas i samma fil. Vid kompilering s� kompileras varje fil f�r sig */

///deklarationer av statiska funktioner: static enbart synlig i denna fil, inline klistrar in koden i st�llet f�r att hoppa,
///om koden �r liten s� �r det inte l�nt att hoppa d� klistrar man in koden ist�llet detta spar tid
static inline void init_ports();
static inline void init_interrupts();

/* setup: initierar mikrodatorn vid start */
void setup(void)
{
	init_ports();
	init_interrupts();
	//fsm_reset();
	return;
}

/* init_ports: s�tter lysdiodernas pinnar till utportar och s�tter tryckknapparnas pinnar till aktiva inportar
			   (insignalerna blir alltid 0 eller 1) underf�rst�tt �r att pullup-resistorer aktiveras med kommandot PORT och ettst�llning */
static void init_ports(void)
{
	DDRB = (1 << LED1) | (1 << LED2) | (1 << LED3); //PORTarna s�tts till utport
	PORTB = (1 << BUTTON); // pullup resistorer aktiveras
	
	PORTD = (BUTTON2);
	return;
}

static void init_interrupts(void)
{
	asm("SEI"); // SET INTERRUPT FLAG aktiverar globalt avbrott assembler instruktion
	PCICR = (1 << PCIE0); // PIN CHANGE INTERRUPT p� PORT B = 0, C = 1, D = 2
	PCMSK0 = (1 << BUTTON); // PCI avbrott p� pin 11, 12 och 13// g�r �ven att skriva PCINT3, PCINT4 och PCINT5 kolla pin ritning i b�rjan
	
	EICRA = ((1 << ISC00) | (1 << ISC01)); // Aktiverar avbrott INT0 p� stigande flank.
	EIMSK = (1 << INT0); // Aktiverar avbrott PIN 2 / PORTD2.
	
	return;
}