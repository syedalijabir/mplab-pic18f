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

/* Calculate factorial while
also generating a delay using
Timer0 using interrupt*/

#include <p18f4520.h>

#pragma config OSC=HS
#pragma config DEBUG=OFF
#pragma config LVP=ON
#pragma config WDT=OFF

#define myport PORTD

#pragma interrupt my_isr
void my_isr (void)
{
// Write ISR here
T0CONbits.TMR0ON=0;
INTCONbits.T0IF = 0;
myport = myport+2; // 
TMR0L = 225;
T0CONbits.TMR0ON=1;
}

# pragma code high_vector = 0x008	// High Interrupt Location
void my_HPI (void)
{
_asm
GOTO my_isr
_endasm
}
#pragma code

void main (void)
{
int i=21,j,fact=1;
TRISB = 0;
INTCON = 0xE0;
T0CON = 0x40; // 8-bit, No prescalar
TMR0L = 225;
T0CONbits.TMR0ON=1;

myport = 0;
while(1)
{
	// Calculate Factorial
	for (j=i;j>0;j--)
		fact = fact*j;
}
}

