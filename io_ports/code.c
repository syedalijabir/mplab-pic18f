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

#define myport PORTB

void main (void)
{
    int i;
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
    myport = 1;
    while(1)
    {
        for(i=0;i<25000;i++);
            myport = 2;
        for(i=0;i<25000;i++);
            myport = 4;
        for(i=0;i<25000;i++);
            myport = 8;
        for(i=0;i<25000;i++);
            myport = 16;
        for(i=0;i<25000;i++);
            myport = 32;
        for(i=0;i<25000;i++);
            myport = 64;
        for(i=0;i<25000;i++);
            myport = 128;
    }
}
