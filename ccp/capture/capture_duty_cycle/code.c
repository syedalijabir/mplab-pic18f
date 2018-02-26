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
	Calculate DC and TP
	10Mhz Crystal
*/

#include <p18f4520.h>

#pragma config OSC=HS
#pragma config DEBUG=OFF
#pragma config LVP=ON
#pragma config WDT=OFF

void CCP1_ISR(void);
void T1_ISR(void);

#pragma interrupt polls
void polls (void)
{
if (PIR1bits.CCP1IF == 1)
	CCP1_ISR();
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

unsigned int cur,prev,count=0,TP,DC;
char flag=0,football=0;
unsigned int beech_ki_billi;


void main (void)
{
TRISD = 0;
CCP1CON = 0x00;			
TRISCbits.TRISC2 = 1;	// Make CCP pin as Input
T1CON = 0x80;			// 16 Prescalar No Postscalar
T3CON = 0x20;
TMR1L  = 0;
TMR1H  = 0;
CCP1CON = 0x05;			// Configure as Capture Every Rising Edge


PIR1bits.TMR1IF = 0;
PIE1bits.TMR1IE = 1;
PIE1bits.CCP1IE = 1;
PIR1bits.CCP1IF = 0;
INTCONbits.GIE  = 1;
INTCONbits.PEIE = 1;
T1CONbits.TMR1ON = 1;


while(1)
{

}
}

void T1_ISR(void)
{
PIR1bits.TMR1IF = 0;
count++;
}

void CCP1_ISR(void)
{
PIR1bits.CCP1IF = 0;
if (flag == 0)
{
	if (football == 1)
	{
		cur = CCPR1;
		TP = (65535-prev) + cur + (count - 1)*65536; 
		DC = beech_ki_billi - prev;
		football = 0;
		prev = cur;
	}
	else
	{
		prev = CCPR1;
	}
flag = 1;
CCP1CON = 0x04;
}
else 
{
	beech_ki_billi = CCPR1;
	flag = 0;
	football = 1;
	CCP1CON = 0x05;
}

}

