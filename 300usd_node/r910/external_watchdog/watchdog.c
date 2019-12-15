
#define F_CPU 128000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>

// How long to sleep between battery voltage checks
// as a multiple of 8 seconds
#define SLEEP_TIME (38) // ~5 minutes

ISR(WDT_vect) {
	// WDIE & WDIF is cleared in hardware upon entering this ISR
	wdt_disable();
}

// sleep for the maximum 8 seconds using SLEEP_MODE_PWR_DOWN
void deep_sleep_8_seconds() {
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
}

void deep_sleep() {
  int i;
  for(i=0; i < SLEEP_TIME; i++) {
    deep_sleep_8_seconds();
  }
}


// initialize but don't start ADC
void adc_init() {
  // Enable REFS0 to use VCC as voltage reference
  // Enable MUX bits 1 and 2 to select ADC channel 6
  ADMUX = (1 << REFS0) | (1 << MUX1) | (1 << MUX2);

  // ADPS0-2 sets prescaler to 128 resulting in 1 kHz ADC frequency
  ADCSRA = (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
}

void adc_stop() {
  ADCSRA &= ~(1 << ADEN); // disable ADC
}

void adc_start() {
  ADCSRA |= (1 << ADEN); // enable ADC
}

uint16_t adc_read() {
  adc_start();
  // start conversion
  ADCSRA |= (1 << ADSC);
 
  // wait for conversion to complete
  while(ADCSRA & (1 << ADSC));

  adc_stop();
  return ADC;
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

int get_battery_voltage() {
  uint16_t val;

  val = adc_read();
  
  return (int) val;
}

int main(void) {

  int battery_voltage = 0;
  int i = 1;
  
  DDRB |= (1 << DDB5); // Set port B5 (the LED pin) as output
  adc_init();
  
  // TODO
  // read ADC value
  // if ADC value is above threshold, turn on GPIO port for 5 seconds
  
  while(1) {
    blink(i++);
    battery_voltage = get_battery_voltage();
    deep_sleep();
  }
  
}
