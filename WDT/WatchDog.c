#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

void sleep()
{
  SMCR |= 0b00000100; //for entering power down mode 
  MCUCR |= 0b01100000;// for disabling BOD ( BODSE nad BODS bits set to high)
  MCUCR &= 0b01000000;// for disabling Bod within three clock cycles( source reference manual pg 45 sec 10.11.2)
  PRR |= 0b11101111;// for disabling TWI ,all timers , SPI, uSART ,ADC 
  SMCR |= 0b00000001; // for enabling sleep mode
  sleep_cpu ();
}
int main()
{
  DDRB|=0x20; // setting 13 pin as output
  cli(); // disable interrupts
  wdt_reset();// resetting the value in watchdog timer
  WDTCSR |= 0x18;// WatchDog Current Status Register  for entering kind of setup mode
  WDTCSR = 0x4e;// for 1000ms time - out
  sei(); // enabling interrupts
  sleep();
  while(1){}; 
}
ISR(WDT_vect)
{
  PORTB^=0x20; // toggling led
  wdt_reset(); // to stop watchdog from resetting the MCU (because in Interrupt & System Reset Mode)
  sleep(); // for again making the MCU sleep as it was woke up by interrupt
}