# Analog to Digital Converter (ADC)

## Basics
**Resolution**
* ADC has an n-bit resolution, where n can be 8, 10, 12, 16 or even 24
* Higher resolution provides smaller step size
* Step Size is the smallest change that ADC can differentiate
* Resolution of ADC can not be changed after its fabrication but step size can be changed by varying Vref

**Vref**
* Input voltage used as reference voltage
* Voltage connected to this pin and resolution of ADC dictate the step size
* For an n-bit ADC, 𝐬𝐭𝐞𝐩 𝐬𝐢𝐳𝐞 = 𝑽𝒓𝒆𝒇/𝟐^𝒏

**Digital Data Output**

Output of the ADC in n-bits (according to resolution of ADC)
𝑫𝒐𝒖𝒕 = 𝑽𝒊𝒏/(𝒔𝒕𝒆𝒑_𝒔𝒊𝒛𝒆)

## PIC18F ADC
The ADC peripheral of PIC18F has following charateristics
* 13 input analog channels (AN0 to AN12)
* 10-bit Resolution
Five Registers
* A/D Result High Register (ADRESH)
* A/D Result Low Register (ADRESL)
* A/D Control Register 0 (ADCON0)
* A/D Control Register 1 (ADCON1)
* A/D Control Register 2 (ADCON2)
