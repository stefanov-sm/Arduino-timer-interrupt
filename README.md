## Arduino timer interrupt
Frugal **`Timer1`** interrupt support for Arduino R3 NANO and R3 UNO
> [!IMPORTANT]  
> Maximum interval between interrupts is **4193 ms**  
> Note the use of `static` variables in the slow job example below

The `timer_interrupt_demo.ino` example is a sensor control that uses interrupts and keeps the previous (`true` or `false`) reading while hesitating/flickering and only changes it when stable.

### Usage
Timer interrupt occurs every 10 ms in the example below
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
