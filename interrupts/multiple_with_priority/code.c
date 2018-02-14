//
// Owner: Ali Jabir
// Email: syedalijabir@gmail.com
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/* 	Interrupt based Timer0 and Timer1 
	External Interrupts INT2 and INT1
	Priority Enabled
	INT2 & Timer0 -> High Priority
	INT1 & Timer1 -> Low Priority
	Toggle bits with respect to delay in
	T0 and T1
	Count Number of Interrupts with respect
	to INT0 and INT1
*/

#include <p18f4520.h>

#pragma config OSC=HS
#pragma config DEBUG=ON
#pragma config LVP=ON
#pragma config WDT=OFF

#define T0_bit PORTBbits.RB5
#define T1_bit PORTBbits.RB7

void T0_ISR(void);
void T1_ISR(void);
void INT2_ISR(void);
void INT1_ISR(void);

#pragma interrupt polls_high
void polls_high (void)
{
if (INTCONbits.TMR0IF == 1)
	T0_ISR();
if (INTCON3bits.INT2IF == 1)
	INT2_ISR();
}

#pragma interruptlow polls_low
void polls_low (void)
{
if (PIR1bits.TMR1IF == 1)
	T1_ISR();
if (INTCON3bits.INT1IF == 1)
	INT1_ISR();
}

# pragma code high_vector = 0x008	// High Interrupt Location
void my_HPI (void)
{
_asm
GOTO polls_high
_endasm
}
#pragma code

# pragma code low_vector = 0x018	// High Interrupt Location
void my_LPI (void)
{
_asm
GOTO polls_low
_endasm
}
#pragma code

int count0=0,count1=0;

void main (void)
{
ADCON1 = 0x07;			// Make pins digital
TRISBbits.TRISB5 = 0;
TRISBbits.TRISB7 = 0; // configure as output
INTCONbits.TMR0IF = 0;
PIR1bits.TMR1IF = 0;
INTCONbits.TMR0IE = 1;
PIE1bits.TMR1IE = 1;
INTCON3bits.INT1IF = 0;
INTCON3bits.INT1IE = 1;
INTCON3bits.INT2IF = 0;
INTCON3bits.INT2IE = 1;

RCONbits.IPEN = 1;		// Enable Priority
INTCON2bits.TMR0IP = 1; // High Priority
IPR1bits.TMR1IP = 0;	// Low Priority
INTCON3bits.INT2IP = 1;	// High Priority
INTCON3bits.INT1IP = 0;	// Low Priority

T0CON = 0x48; // 8-bit, No prescalar
TMR0L = 200;
T0CONbits.TMR0ON=1;

T1CON = 0x88; // 16-bit, No prescalar
TMR1H = 0xAA;
TMR1L = 0x00;
T1CONbits.TMR1ON=1;

INTCONbits.GIE = 1;
INTCONbits.PEIE = 1;

TRISC = 0;
TRISD = 0;

T0_bit = 1;
T1_bit = 1;

while(1)
{
	PORTD = count1;
	PORTC = count0;
}
}

void T0_ISR(void)
{
T0CONbits.TMR0ON = 0;
INTCONbits.TMR0IF = 0;
T0_bit = ~T0_bit;
TMR0L = 200;
T0CONbits.TMR0ON=1;
}

void INT2_ISR(void)
{
INTCON3bits.INT2IF = 0;
count0++;
}

void T1_ISR(void)
{
T1CONbits.TMR1ON = 0;
PIR1bits.TMR1IF = 0;
T1_bit = ~T1_bit;
TMR1H = 0xAA;
TMR1L = 0x00;
T1CONbits.TMR1ON=1;
}

void INT1_ISR(void)
{
INTCON3bits.INT1IF = 0;
count1++;
}
