## Arduino timer interrupt
Frugal **`Timer1`** interrupt support for Arduino R3 NANO and R3 UNO
> [!IMPORTANT]  
> Maximum interval between interrupts is **4193 ms**

The example is a sensor control that keeps the previous reading (true or false) while hesitating/flickering

### Usage
```C++
#include "timer_interrupt.h"

#define SLOW_GATE          11
#define TIMER_INTERRUPT_MS 10
#define A_LONG_TIME (60L*1000/TIMER_INTERRUPT_MS)

// =============================================================================
SET_TIMER_ISR({
  // Do the fast job(s) here, onece per 10 ms in this example

  // Now the slow job(s)
  // This example toggles SLOW_GATE once per minute
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
