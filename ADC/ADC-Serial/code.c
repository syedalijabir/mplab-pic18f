#include<p18f4520.h>

#pragma config OSC=HS
#pragma config DEBUG=OFF
#pragma config LVP=OFF
#pragma config WDT=OFF

void ADC_ISR(void);
void TX_ISR(void);
void RX_ISR(void);
void packet_TX(char,char);

char msg[]="\r\rThis is A HyperTerminal Simulation\rPress 1 to Compute a ADC Value\r\r";
int len = 70;//strlen(msg);

#pragma interrupt polls
void polls (void)
{
if (PIR1bits.ADIF == 1)
	ADC_ISR();
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

char ch,flag=0,frx=0;
char i=0,count,num;
char ADCH,ADCL;
char brr[4];

void main()
{
// ADC Settings
TRISAbits.TRISA0 = 1; 	// Use as Analog Input
ADCON1 = 0x07;
ADCON0 = 0x00;
ADCON2 = 0xAD;

// Configure Serial Port
TRISCbits.TRISC6 = 1;
TRISCbits.TRISC7 = 1;
TXSTA = 0x20;	// Low Baud Rate, 8-bit Asynchronous
RCSTA = 0x90;	// Enable Receiving
BAUDCONbits.BRG16 = 0;
SPBRG = 15;

// Configure ADC & Serial Interrupt
PIR1bits.ADIF = 0;
PIE1bits.ADIE = 1;
PIE1bits.TXIE = 1;
PIE1bits.RCIE = 1;
INTCONbits.GIE = 1;
INTCONbits.PEIE = 1;

TRISB = 0;
TRISD = 0;

while(5);
}

void ADC_ISR()
{
PIR1bits.ADIF = 0;
ADCH = ADRESH;
ADCL = ADRESL;
PORTD = ADCL;
PORTB = ADCH;
ADCON0bits.GO_DONE=0;
packet_TX(ADCH,ADCL);
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
if (ch=='1')
{
	ADCON0bits.ADON = 1; 	// Turn ON ADC
	ADCON0bits.GO_DONE=1;
}
else if (ch=='0')
{
	ADCON0bits.ADON = 0; 	// Turn OFF ADC
	ADCON0bits.GO_DONE=0;
}
else
{}
}

void packet_TX(char HB,char LB)
{
int res=0,temp,k;
int arr[4];

// Calculate Decimal Value of {HB,LB}
for (k=1;k<=128;k=k*2)
{
	temp = LB;
	temp = temp & k;
	res += temp;
}
for (k=1;k<=2;k=k*2)
{
	temp = HB;
	temp = temp & k;
	temp = temp * 256;
	res += temp;
}

k = 0;
if (res==0)
{
for (k=0;k<4;k++)
	brr[k]='0';
}
else
{
while(res!=0)
{
	arr[k] = res%10;
	brr[k] = arr[k]+48;
	res = res/10;
	k++;
}
}
flag  = 1;
count = k-1;
TXREG = brr[count];
PIE1bits.TXIE=1;
}