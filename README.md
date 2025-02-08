## Arduino timer interrupt
Frugal **`Timer1`** interrupt support for Arduino R3 NANO and R3 UNO
> [!IMPORTANT]  
> Maximum interval between interrupts is **4193 ms**
### Info (PrincOps)
_____  
- Set **TIMER1_COMPA_vect** interrupt vector to the correponding ISR (_Interrupt Service Routine_)  
_____  
<image src=https://github.com/user-attachments/assets/531d7271-4a0e-44a3-8a1c-a4127b014768 width = 700/>
  
- Set **WGM12** bit of register **TCCR1B** for **CTC** (_Clear Timer on Compare match_) mode  
`TCCR1B |= (1 << WGM12);`  
_____  
<image src=https://github.com/user-attachments/assets/de0afe79-e7f8-433c-9c8c-170302f76575 width = 500/>  
  
- Set **CS10** and **CS12** bits of register **TCCR1B** for **prescaler = 1024**  
`TCCR1B |= (1 << CS12) | (1 << CS10);`
   
Use `(1<<CS11)` for **prescaler = 8**, `(1<<CS10)|(1<<CS11)` **for prescaler = 64**, `(1<<CS12)` for **prescaler = 256** as shown above  
_____  
 - Set **OCIE1A** bit of register **TIMSK1** to enable **Timer1** TCI (_Timer Compare Interrupt_)  
 `TIMSK1 |= (1 << OCIE1A);`
_____  

### Usage
The `timer_interrupt_demo.ino` example is a sensor control that uses interrupts and keeps the previous (`true` or `false`) reading while hesitating/flickering and only changes it when stable.  

Timer interrupt occurs every 10 ms in the example below
> [!TIP]  
> Note the use of `static` variables for the slow job
```C++
#include "timer_interrupt.h"

#define TIMER_INTERRUPT_MS 10
#define SLOW_GATE          11
#define A_LONG_TIME (60L*1000/TIMER_INTERRUPT_MS)
// One minute here, may be many days long

// =============================================================================
// The timer interrupt service routine (ISR)
SET_TIMER_ISR({
  // Do the fast job(s) here, once every 10 ms

  // A slow job
  // Toggle SLOW_GATE pin once per minute
  static unsigned long slow_counter = 0;
  if (++slow_counter >= A_LONG_TIME)
  {
    slow_counter = 0;
    static bool slow_status = false;
    slow_status = !slow_status;
    digitalWrite(SLOW_GATE, slow_status ? HIGH: LOW);
  }
});

// =============================================================================
void setup()
{
  pinMode(SLOW_GATE, OUTPUT);
  // The rest of the setup

  INIT_TIMER_INTERRUPT(TIMER_INTERRUPT_MS);
}

// =============================================================================
void loop()
{
  // The rest of the logic     
}
