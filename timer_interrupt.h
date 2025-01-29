#ifndef __TIMER_INTERRUPT_H
#define __TIMER_INTERRUPT_H

// =============================================================================
#ifdef DEBUG
  #define debug_init     {Serial.begin(38400); while(!Serial);}
  #define debug_echo(X)  Serial.println(X)
#endif  
// =============================================================================

#define INIT_TIMER_INTERRUPT(MS) \
static_assert(MS < 4194, "Timer: Max 4193 milliseconds supported"); \
init_timer_interrupt(MS);

void init_timer_interrupt(unsigned int ms)
{
  unsigned int prescaler;
  byte prescaler_bits;
  
  if      (ms <=   32) {prescaler = 8;    prescaler_bits = (1<<CS11);}
  else if (ms <=  262) {prescaler = 64;   prescaler_bits = (1<<CS10)|(1<<CS11);}
  else if (ms <= 1048) {prescaler = 256;  prescaler_bits = (1<<CS12);}
  else /* ms < 4194 */ {prescaler = 1024; prescaler_bits = (1<<CS10)|(1<<CS12);};
  
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 16000L * ms / prescaler - 1;
  TCCR1B |= (1<<WGM12);
  TCCR1B |= prescaler_bits;
  TIMSK1 |= (1<<OCIE1A);
  interrupts();
}

#define SET_TIMER_ISR(X) ISR(TIMER1_COMPA_vect) X

#endif
