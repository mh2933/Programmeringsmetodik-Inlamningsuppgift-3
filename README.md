# Programmeringsmetodik-Inlamningsuppgift-3

Uppgiften gick ut på att implementera strukt objekt och led-vektorer i main i ett redan skrivet bibliotek.  
Dessa objekt var lysdioder och tryckknappar. 

Några "bitar" som var svåra och som Erik hjälpte till med först och främst är begreppen struktar och vektorer, dessa är fortfarande svåra att särskilja.
Men en stor skillnad är att vektorer hanterar minnesallokeringen men push och pop funktioner. Medan atruktar är lite lik 
enum fast man kan ha olika datatyper inne i en strukt.   
Man kan använda programmet någorlunda bra utan att känna till alla detaljer men såklart blir kodningen bättre med mer förståelse.
Nu får man möjlighet att avgöra vad för typ av kodning man vill hålla på med, om det ska vara mera åt drivrutiner eller om man vill mer använda 
färdiga drivrutiner med hjälp av bibliotek, jag vet inte riktigt än men min kunskapsnivå är inte riktigt på drivrutinsnivå ännu. 

Den andra svåra "biten" var att man skulle använda en global button b1 strukt-variabel(objekt) i main, detta gör objektet synlig i hela programemt och under
hela dess längd det sparas alltså i ram minnet.

Den tredje lärdomen var att man använde sig av en global bool leds_enabled = false variabel i main för att toggla led sekvensen, man inverterar värdet 
på leds_enbaled med NOT operatorn och implemnterar detta sedan i en if sats som också föregicks av en if sats ovanför main i ISR interrupt rutinen.

Fjärde lärdomen var att med hjälp av NOT operatorn framför !button_is_pressed(&b1) så fungerande detta som en flankstyrning vid uppsläpp av knappen, 
galet simpelt, jag körde fast helt här erik steg in och ordnade saken lätt. 

Väl i main så initieras struktar och funktioner: 
led objekten först
sedan led vektorn
sedan button_init()
sedan button_enable_interrupt()
sedan led_init()
sedan led_vector_init()
sedan led_vector_push()

till sist en while loop tillammans med nästlade
if satser, kanske inte den vackraste koden men det 
fungerade efter många försök och bra support från erik.

Det är de sista dagarna på året och denna kurs och nu 
ökar svårighetsgraden markant!
