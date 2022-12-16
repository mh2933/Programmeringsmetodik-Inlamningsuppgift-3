#include "header.h"


/* static gör funktionen lokal till setup.c filen, inline klistrar in innehållet
och kan bara anropas i samma fil. Vid kompilering så kompileras varje fil för sig */

///deklarationer av statiska funktioner: static enbart synlig i denna fil, inline klistrar in koden i stället för att hoppa,
///om koden är liten så är det inte lönt att hoppa då klistrar man in koden istället detta spar tid
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

/* init_ports: sätter lysdiodernas pinnar till utportar och sätter tryckknapparnas pinnar till aktiva inportar
			   (insignalerna blir alltid 0 eller 1) underförstått är att pullup-resistorer aktiveras med kommandot PORT och ettställning */
static void init_ports(void)
{
	DDRB = (1 << LED1) | (1 << LED2) | (1 << LED3); //PORTarna sätts till utport
	PORTB = (1 << BUTTON); // pullup resistorer aktiveras
	
	PORTD = (BUTTON2);
	return;
}

static void init_interrupts(void)
{
	asm("SEI"); // SET INTERRUPT FLAG aktiverar globalt avbrott assembler instruktion
	PCICR = (1 << PCIE0); // PIN CHANGE INTERRUPT på PORT B = 0, C = 1, D = 2
	PCMSK0 = (1 << BUTTON); // PCI avbrott på pin 11, 12 och 13// går även att skriva PCINT3, PCINT4 och PCINT5 kolla pin ritning i början
	
	EICRA = ((1 << ISC00) | (1 << ISC01)); // Aktiverar avbrott INT0 på stigande flank.
	EIMSK = (1 << INT0); // Aktiverar avbrott PIN 2 / PORTD2.
	
	return;
}