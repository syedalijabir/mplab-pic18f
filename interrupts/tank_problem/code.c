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

#include <p18f4520.h>

#pragma config OSC=HS
#pragma config DEBUG=OFF
#pragma config LVP=ON
#pragma config WDT=OFF

void WLS1_ISR(void);
void WLS2_ISR(void);
void T0_ISR(void);


#define S1 PORTCbits.RC6
#define S2 PORTCbits.RC7

#pragma interrupt polls
void polls (void)
{
if (INTCONbits.TMR0IF == 1)
	T0_ISR();
if (INTCON3bits.INT2IF == 1)
	WLS2_ISR();
if (INTCON3bits.INT1IF == 1)
	WLS1_ISR();
}

# pragma code high_vector = 0x008	// High Interrupt Location
void my_HPI (void)
{
_asm
GOTO polls
_endasm
}
#pragma code


int count = 0;

void main()
{
	TRISCbits.TRISC6 = 0;
	TRISCbits.TRISC7 = 0; // configured as output
	S1 = 0;
	S2 = 0;	


	INTCON3bits.INT1IE = 1;
	INTCON3bits.INT1IF = 0;
	INTCON3bits.INT2IE = 1;
	INTCON3bits.INT2IF = 0;
	INTCON2bits.INTEDG2 = 0; // Negative Edge

	INTCONbits.GIE = 1;

	T0CON = 0x07;
	INTCONbits.TMR0IE = 1;
	INTCONbits.TMR0IF = 0;
			
while(1)
{
// idle
}

}

void WLS1_ISR()
{
	INTCON3bits.INT1IF = 0;
	// Tank Filled, Turn OFF Motor
	S1 = 0;
	S2 = 0;
}

void WLS2_ISR()
{
	INTCON3bits.INT2IF = 0;
	// Tank Empty, Turn ON Motor
	S1 = 0;
	S2 = 1;
	TMR0L = 0;
	TMR0H = 0;
	T0CONbits.TMR0ON = 1;
}

void T0_ISR()
{
	T0CONbits.TMR0ON = 0;
	INTCONbits.TMR0IF = 0;
	count++;
	if (count == 134)
	{
		// 15min ho gaye
		// Saab ji motor band kar deo
		S1 = 0;
		S2 = 0;
		count = 0;
	}
	else
	{
		TMR0L = 0;
		TMR0H = 0;
		T0CONbits.TMR0ON = 1;
	}
}
