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

/* 	Capture with CCP
	Unknown Frequency at CCP pin
	10Mhz Crystal
*/

#include <p18f4520.h>

#pragma config OSC=HS
#pragma config DEBUG=OFF
#pragma config LVP=ON
#pragma config WDT=OFF

void CCP1_ISR(void);

#pragma interrupt polls
void polls (void)
{
if (PIR1bits.CCP1IF == 1)
	CCP1_ISR();
}

# pragma code high_vector = 0x008	// High Interrupt Location
void my_HPI (void)
{
_asm
GOTO polls
_endasm
}
#pragma code

unsigned int cur,prev;
char flag=0;
double time;


void main (void)
{
TRISD = 0;
CCP1CON = 0x00;			
TRISCbits.TRISC2 = 1;	// Make CCP pin as Input
T1CON = 0x80;			// 16 Prescalar No Postscalar
T3CON = 0x20;
TMR1L  = 0;
TMR1H  = 0;
CCP1CON = 0x06;			// Configure as Capture 4th Rising Edge


PIR1bits.TMR1IF = 0;
PIE1bits.CCP1IE = 1;
PIR1bits.CCP1IF = 0;
INTCONbits.GIE  = 1;
INTCONbits.PEIE = 1;
T1CONbits.TMR1ON = 1;


while(1)
{
if (flag)
{
	time = (cur - prev)*0.4e-6/4;
}
}
}

void CCP1_ISR(void)
{
PIR1bits.CCP1IF = 0;
if (flag == 0)
{
	prev = CCPR1H;
	prev = prev << 8;
	prev = prev + CCPR1L;
	flag = 1;
}
else
{
	cur = CCPR1H;
	cur = cur << 8;
	cur = cur + CCPR1L;
	flag = 0;
}
}
