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

/* 	SPI Master
	Recieve Data from
	Master and Display
	on PORTD
*/
#include <p18f4520.h>

#pragma config OSC=HS
#pragma config DEBUG=OFF
#pragma config LVP=ON
#pragma config WDT=OFF

#define SS PORTCbits.RC2

void SPI_ISR(void);

#pragma interrupt polls
void polls (void)
{
if (PIR1bits.SSPIF == 1)
	SPI_ISR();
}

# pragma code high_vector = 0x008	// High Interrupt Location
void my_HPI (void)
{
_asm
GOTO polls
_endasm
}
#pragma code

char ch=0;

void main (void)
{
int i,j,count=0;
TRISD = 0;
TRISCbits.TRISC5 = 0; //SDO
TRISCbits.TRISC4 = 1; //SDI
TRISCbits.TRISC3 = 0; //SCK
TRISCbits.TRISC2 = 0; //SS

SS = 1;	

SSPCON1 = 0x20;
SSPSTAT = 0;

PIR1bits.SSPIF = 0;
PIE1bits.SSPIE = 1;
INTCONbits.GIE  = 1;
INTCONbits.PEIE = 1;

//ch = SSPBUF;

SS = 0;
SSPBUF = count;
while(1)
{
//	SSPBUF = count;
//	for (i=0; i<100; i++)
//		for (j=0; j<1000; j++);
//	count++;
}
}

void SPI_ISR(void)
{
PIR1bits.SSPIF = 0;
count++;
ch = SSPBUFF;
SSPBUF = count;
}
