#ifndef __TIMER_INTERRUPT_H
#define __TIMER_INTERRUPT_H

// =============================================================================
  #define debug_init     {Serial.begin(38400); while(!Serial);}
  #define debug_echo(X)  Serial.write(X)
  #define EOL            "\r\n"
// =============================================================================
#if !defined(TIMER_INTERRUPT_MS)
  #error TIMER_INTERRUPT_MS must be defined first
#endif

#if TIMER_INTERRUPT_MS <= 32
  #pragma message("Prescaler = 8")
  #define INIT_TIMER_INTERRUPT           \
  noInterrupts();                        \
  TCCR1A = 0; TCCR1B = 0; TCNT1 = 0;     \
  OCR1A = 16000L*TIMER_INTERRUPT_MS/8-1; \
  TCCR1B |= (1<<WGM12);                  \
  TCCR1B |= (1<<CS11);                   \
  TIMSK1 |= (1<<OCIE1A);                 \
  interrupts()
#elif TIMER_INTERRUPT_MS <= 261
  #pragma message("Prescaler = 64")
  #define INIT_TIMER_INTERRUPT            \
  noInterrupts();                         \
  TCCR1A = 0; TCCR1B = 0; TCNT1 = 0;      \
  OCR1A = 16000L*TIMER_INTERRUPT_MS/64-1; \
  TCCR1B |= (1<<WGM12);                   \
  TCCR1B |= (1<<CS10 | (1<<CS11);         \
  TIMSK1 |= (1<<OCIE1A);                  \
  interrupts()
#elif TIMER_INTERRUPT_MS <= 1048
  #pragma message("Prescaler = 256")
  #define INIT_TIMER_INTERRUPT             \
  noInterrupts();                          \
  TCCR1A = 0; TCCR1B = 0; TCNT1 = 0;       \
  OCR1A = 16000L*TIMER_INTERRUPT_MS/256-1; \
  TCCR1B |= (1<<WGM12);                    \
  TCCR1B |= (1<<CS12);                     \
  TIMSK1 |= (1<<OCIE1A);                   \
  interrupts()
#elif TIMER_INTERRUPT_MS < 4194 
  #pragma message("Prescaler = 1024")
  #define INIT_TIMER_INTERRUPT              \
  noInterrupts();                           \
  TCCR1A = 0; TCCR1B = 0; TCNT1 = 0;        \
  OCR1A = 16000L*TIMER_INTERRUPT_MS/1024-1; \
  TCCR1B |= (1<<WGM12);                     \
  TCCR1B |= (1<<CS12) | (1<<CS10);          \
  TIMSK1 |= (1<<OCIE1A);                    \
  interrupts()
#else
  #error Time interrupt interval can be 4193 ms max
#endif

#define SET_TIMER_ISR(X) \
ISR(TIMER1_COMPA_vect) X

#endif

// =============================================================================
//  noInterrupts();
//  TCCR1A = 0;  // set entire TCCR1A register to 0
//  TCCR1B = 0;  // same for TCCR1B
//  TCNT1  = 0;  // initialize counter value to 0
//
//  // set compare match register for TIMER_INTERVAL increments (clock_frequency * (period_in_ms / 1000) / prescale)
//  OCR1A = 16000000 * (TIMER_INTERVAL / 1000) / TIMER_PRESCALE - 1;
//
//  TCCR1B |= (1 << WGM12);               // turn on CTC mode
//  TCCR1B |= (1 << CS12) | (1 << CS10);  // set CS10 and CS12 bits for TIMER_PRESCALE = 1024
//  TIMSK1 |= (1 << OCIE1A);              // enable timer compare interrupt
//  interrupts();
// =============================================================================