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
	Priority disabled
	Toggle bits with respect to delay in
	T0 and T1
*/
#include <p18f4520.h>

#pragma config OSC=HS
#pragma config DEBUG=OFF
#pragma config LVP=ON
#pragma config WDT=OFF

#define T0_bit PORTCbits.RC5
#define T1_bit PORTCbits.RC7

void T0_ISR(void);
void T1_ISR(void);

#pragma interrupt polls
void polls (void)
{
if (INTCONbits.TMR0IF == 1)
	T0_ISR();
if (PIR1bits.TMR1IF == 1)
	T1_ISR();
}

# pragma code high_vector = 0x008	// High Interrupt Location
void my_HPI (void)
{
_asm
GOTO polls
_endasm
}
#pragma code

void main (void)
{
TRISCbits.TRISC5 = 0;
TRISCbits.TRISC7 = 0; // configure as output
INTCONbits.TMR0IF = 0;
PIR1bits.TMR1IF = 0;
INTCONbits.TMR0IE = 1;
PIE1bits.TMR1IE = 1;
INTCONbits.GIE = 1;

T0CON = 0x40; // 8-bit, No prescalar
TMR0L = 225;
T0CONbits.TMR0ON=1;

T1CON = 0x88; // 16-bit, No prescalar
TMR1H = 0xFF;
TMR1L = 0x55;
T1CONbits.TMR1ON=1;

T0_bit = 1;
T1_bit = 1;

while(1)
{
	// Idle
}
}

void T0_ISR(void)
{
T0CONbits.TMR0ON = 0;
INTCONbits.TMR0IF = 0;
T0_bit = ~T0_bit;
TMR0L = 225;
T0CONbits.TMR0ON=1;
}

void T1_ISR(void)
{
T1CONbits.TMR1ON = 0;
PIR1bits.TMR1IF = 0;
T1_bit = ~T1_bit;
TMR1H = 0xFF;
TMR1L = 0x55;
T1CONbits.TMR1ON=1;
}
