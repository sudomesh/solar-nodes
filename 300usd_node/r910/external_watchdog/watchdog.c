
#define F_CPU 128000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>

ISR(WDT_vect) {
	// WDIE & WDIF is cleared in hardware upon entering this ISR
	wdt_disable();
}

// sleep for the maximum 8 seconds using SLEEP_MODE_PWR_DOWN
void power_down_for_8_seconds() {
  ADCSRA &= ~(1 << ADEN); // disable ADC
  wdt_enable(WDTO_8S); // sleep for 8 seconds
  WDTCSR |= (1 << WDIE); // watchdog interrupt enable  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  cli(); // clear global interrupt flag (prevent interrupts)
  sleep_enable(); // set the 'sleep enable' bit
  // We would disable brown-out detection here
  // but we should've already disabled it with e-fuses
  // so why bother.

  sei(); // If we don't do this then we don't wake up
  sleep_cpu(); // actually sleep

  // we've woken up!
  
  sleep_disable(); // clear the 'sleep enable' bit
  sei(); // set global interrupt flag (re-enable global interrupts)
  ADCSRA |= (1 << ADEN); // enable ADC
}


void blink(int short_blinks) {
  int i;
  
  PORTB |= (1 << PB5); // turn on port B5
  _delay_ms(500);
  
  PORTB &= ~(1 << PB5); // turn off port B5
  _delay_ms(200);
  
  for(i=0; i < short_blinks; i++) {
    PORTB |= (1 << PB5); // turn on port B5
    _delay_ms(100);
    
    PORTB &= ~(1 << PB5); // turn off port B5
    _delay_ms(200);
  }
}

int main(void) {

  int i = 1;
  
  DDRB |= (1 << DDB5); // Set port B5 (the LED pin) as output
    
  // TODO
  // read ADC value
  // if ADC value is above threshold, turn on GPIO port for 5 seconds
  
  while(1) {
    power_down_for_8_seconds();
    blink(i++);
  }
  
}
