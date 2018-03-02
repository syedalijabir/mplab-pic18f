# General Purpose I/O Ports
* Five, bit addressable I/O ports. PORT A through PORT E

* Most I/O pins are multiplexed

* Generally have eight I/O pins with a few exceptions

* Addresses already assigned to these ports in the design stage

* Each port is identified by its assigned SFR

Each port has three registers for its operation. These registers are:
 
* TRIS register (data direction register)

* PORT register (reads the levels on the pins of the device)

* LAT register (output latch)

## PORTA
 
8-bit wide, bidirectional port (direction set by TRISA)

Setting a TRISA bit = 1 will make corresponding PORTA bit as input

Setting a TRISA bit = 0 will make corresponding PORTA bit as output


Note: Pins RA6 and RA7 are being utilized by Crystal Oscillator
So we have 6 pins left to be used

**Setting complete Port A as output**

```
#include <p18f4520.h>

#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config DEBUG = OFF,  LVP = OFF

void main (void)
{

TRISA = 0x00;

PORTA = 0xAB;

while(1);
}
```

**Setting Pin0 of Port A as input**
```
#include <p18f4520.h>

#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config DEBUG = OFF,  LVP = OFF

void main (void)
{

TRISAbits.TRISA0 = 1; 	// cannot assign value now

while(1);
}
```

## PORTB
 
* 8-bit wide, bidirectional port (direction set by TRISB)

* Setting a TRISB bit = 1 will make corresponding PORTA bit as input

* Setting a TRISB bit = 0 will make corresponding PORTA bit as output

**Setting complete Port B as output**
```
#include <p18f4520.h>

#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config DEBUG = OFF,  LVP = OFF

void main (void)
{

TRISB = 0x00;

PORTB = 0x24;

while(1);
}
```
**Setting Pin2 of Port B as input and Pin7 as output**
```
#include <p18f4520.h>

#pragma config OSC = HS
#pragma config WDT = OFF
#pragma config DEBUG = OFF,  LVP = OFF

void main (void)
{

TRISBbits.TRISB2 = 1; 	// cannot change value 
TRISBbits.TRISB7 = 0;

PORTBbits.RB7 = 1;

while(1);
}
```

