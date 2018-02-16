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
#include <string.h>

char msg[]="\r\rThis is A HyperTerminal Simulation\r\rPress a button between 0 and 9 to calculate factorial\r\n\r\n";
int len = 95;//strlen(msg);

#pragma config OSC=HS
#pragma config DEBUG=OFF
#pragma config LVP=OFF
#pragma config WDT=OFF

void TX_ISR(void);
void RX_ISR(void);
void packet_TX(int);
int factorial(int);

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

int i=0,count,num;
char ch=20,flag=0,frx=0;
char brr[10];

void main()
{
int j,k,f;
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
if(frx)
{
	frx = 0;
	num = ch - 48;	// 48 is decimal of '0'
	if (num>=0 && num <=9)
	{
		f = factorial(num);
		packet_TX(f);
	}
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
if(flag)
{
	count--;
	TXREG = brr[count];
	if(count==-1)
	{
		flag = 0;
		i=0;
	}
}
else
	PIE1bits.TXIE = 0;
}

}

void RX_ISR()
{
ch = RCREG;
frx = 1;
}

void packet_TX(int res)
{
int k,x,y;
int arr[10];
k = 0;
while(res!=0)
{
	arr[k] = res%10;
	brr[k] = arr[k]+48;
	res = res/10;
	k++;
}
flag = 1;
count = k-1;
TXREG = brr[count];
PIE1bits.TXIE=1;
}

int factorial(int a)
{
int j,f=1;
for(j=a; j>0; j--)
{
	f = f*j;
}
return f;
}
