#define mybit PORTCbits.RC5
void main()
{
	TRISCbits.TRISC5 = 0;
	mybit = 0;

	T0CON = 0x48; // T0 8bit Mode No prescaler
while(1)
{
	TMR0L = 62;
	mybit = 1;
	T0CONbits.TMR0ON = 1;
	while(INTCONbits.T0IF == 0);
	T0CONbits.TMR0ON = 0;
	mybit = 0;
	INTCONbits.T0IF = 0;
	TMR0L = 172;
	T0CONbits.TMR0ON = 1;
	while(INTCONbits.T0IF == 0);
	T0CONbits.TMR0ON = 0;
	INTCONbits.T0IF = 0;
}	
	
}