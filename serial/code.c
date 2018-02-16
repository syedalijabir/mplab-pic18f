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

/*
A HyperTerminal based UI
Displays Welcome Message
and ask for different options to
user.
User replies and Controller
responds accordingly
*/
#include <p18f4520.h>
#include <string.h>

char msg[]="Jee Ayaan Nu!\rPlease Select from 1 of the following options\r\rPress 1 for PORTB\rPress 2 for PORTD\r\r\r";
int len = 99;//strlen(msg);

#pragma config OSC=HS
#pragma config DEBUG=OFF
#pragma config LVP=OFF
#pragma config WDT=OFF

void TX_ISR(void);
void RX_ISR(void);
void welcome(void);

#pragma interrupt polls
void polls (void)
{
if (PIR1bits.TXIF == 1)
	TX_ISR();
if (PIR1bits.RCIF == 1)
	RX_ISR();
}

# pragma code high_vector = 0x008	// High Interrupt Location
void my_HPI (void)
{
_asm
GOTO polls
_endasm
}
#pragma code

int i=0;
char ch;
void main()
{
int j,k;
TRISB = 0;
TRISD = 0;
TRISCbits.TRISC6 = 1;
TRISCbits.TRISC7 = 1;
TXSTA = 0x20;	// Low Baud Rate, 8-bit Asynchronous
RCSTA = 0x90;	// Enable Receiving
BAUDCONbits.BRG16 = 0;
SPBRG = 15;
PIE1bits.TXIE = 1;
PIE1bits.RCIE = 1;
INTCONbits.GIE = 1;
INTCONbits.PEIE = 1;

//welcome();

while(1)
{
if (ch == '1')
{
	// Toggle PORTB 5 times
	for(k=0; k<5; k++)
	{
		PORTB = 0xAA;
		for(j=0; j<1000; j++);
		PORTB = 0x55;
		for(j=0; j<1000; j++);
	}
}
else if(ch == '2')
{
	// Toggle PORTD 5 times
	for(k=0; k<5; k++)
	{
		PORTD = 0xAA;
		for(j=0; j<1000; j++);
		PORTD = 0x55;
		for(j=0; j<1000; j++);
	}
}
else
{

}
}

}

void TX_ISR()
{
if(i<len)
{
	TXREG = msg[i];
	i++;
}
else
{
PIE1bits.TXIE = 0;
}
}

void RX_ISR()
{
ch = RCREG;
}

