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

/* 	PWM with CCP
	70% Duty Cycle
	1KHz Frequency
	10Mhz Crystal
*/
#include <p18f4520.h>

#pragma config OSC=HS
#pragma config DEBUG=OFF
#pragma config LVP=ON
#pragma config WDT=OFF

void T2_ISR(void);

#pragma interrupt polls
void polls (void)
{
if (PIR1bits.TMR2IF == 1)
	T2_ISR();
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
//CCP1CON = 0x00;			// Clear Register
PR2 = 155;				// Fpwm = 1KHz
CCPR1L = 108;			// 155*70% = 108.5
TRISCbits.TRISC2 = 0;	// Make CCP pin as Output
T2CON = 0x02;			// 16 Prescalar No Postscalar
TMR2  = 0;
CCP1CON = 0x2C;			// Configure as PWM

PIR1bits.TMR2IF = 0;
PIE1bits.TMR2IE = 1;
T2CONbits.TMR2ON = 1;		// Turn ON T2
INTCONbits.GIE  = 1;
INTCONbits.PEIE = 1;

while(1);

}

void T2_ISR(void)
{
PIR1bits.TMR2IF = 0;
}
