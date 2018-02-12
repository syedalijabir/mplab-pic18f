/*
	Two Analog inputs
	sample and show on PORTC
	and PORTD
	using AN0 and AN1
*/

#include<p18f4520.h>

#pragma config OSC=HS
#pragma config DEBUG=OFF
#pragma config LVP=OFF
#pragma config WDT=OFF

void ADC_ISR(void);

#pragma interrupt polls
void polls (void)
{
if (PIR1bits.ADIF == 1)
	ADC_ISR();
}

# pragma code high_vector = 0x008	// High Interrupt Location
void my_HPI (void)
{
_asm
GOTO polls
_endasm
}
#pragma code

char dataH,dataL;
char channel = 0;

void main()
{
// ADC Settings
TRISAbits.TRISA0 = 1; 	// Use as Analog Input
TRISAbits.TRISA1 = 1; 	// Use as Analog Input
ADCON1 = 0x0D;
ADCON0 = 0x00;
ADCON2 = 0xAD;
ADCON0bits.ADON = 1; 	// Turn ON ADC

// Configure ADC Interrupt
PIR1bits.ADIF = 0;
PIE1bits.ADIE = 1;
INTCONbits.GIE = 1;
INTCONbits.PEIE = 1;

TRISC = 0;
TRISD = 0; 	// Configure as Output

ADCON0bits.GO_DONE=1;

while(5)
{
	
}

void ADC_ISR()
{
PIR1bits.ADIF = 0;
dataH = ADRESH;
dataL = ADRESL;
if (channel == 1)
	{
		PORTD = dataH;
		// Settings for AN0
		ADCON0 = 0x00;
		channel = 0;
	}
	else
	{
		PORTC = dataH;
		// settings for AN1
		ADCON0 = 0x04;
		channel = 1;
	}
ADCON0bits.GO_DONE=1;
}