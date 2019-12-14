
#define F_CPU 128000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  
  DDRB |= (1 << DDB5); // Set port B5 (the LED pin) as output

  // repeat one lone blink followed by two short blinks

  while(1) {

    PORTB |= (1 << PB5); // turn on port B5
    _delay_ms(500);
    
    PORTB &= ~(1 << PB5); // turn off port B5
    _delay_ms(200);
    
    PORTB |= (1 << PB5); // turn on port B5
    _delay_ms(100);

    PORTB &= ~(1 << PB5); // turn off port B5
    _delay_ms(200);
    
    PORTB |= (1 << PB5); // turn on port B5
    _delay_ms(100);

    PORTB &= ~(1 << PB5); // turn off port B5
    _delay_ms(400);

  }
}
