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

void main()
{
// ADC Settings
TRISAbits.TRISA0 = 1; 	// Use as Analog Input
ADCON1 = 0x07;
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

while(5);
}

void ADC_ISR()
{
PIR1bits.ADIF = 0;
PORTD = ADRESH;
PORTC = ADRESL;
ADCON0bits.GO_DONE=1;
}
