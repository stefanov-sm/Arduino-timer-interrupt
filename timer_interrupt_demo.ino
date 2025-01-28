#define PROXIMITY_A_SENSOR 2
#define PROXIMITY_B_SENSOR 3
#define REGISTRATION_GATE  8

// =============================================================================
#define NREADINGS          5
class sensor
{
  private:
  bool running_value;
  bool readings_list[NREADINGS];
  byte readings_list_position;
  byte sensor_pin;

  public:
  sensor(byte sensor_pin_number)
  {
    this->sensor_pin = sensor_pin_number;
    this->running_value = false;
    this->readings_list_position = 0;
    for (byte i = 0; i < NREADINGS; i++)
      (this->readings_list)[this->readings_list_position] = false;
  }

  void update(void) // to be invoked by a timer ISR
  {
    // Sensor status (item present is LOW)
    byte readings, i;

    (this->readings_list)[this->readings_list_position++] = (digitalRead(this->sensor_pin) == LOW);
    if (this->readings_list_position >= NREADINGS) this->readings_list_position = 0;

    for (readings = i = 0; i < NREADINGS; i++)
      if ((this->readings_list)[i]) readings++;
    
    switch (readings)
    {
      case 0:
        this->running_value = false; break;
      case NREADINGS:
        this->running_value = true; break;
      default: return; // flickering, inconclusive
    }  
  }

  void reset(void)
  {
    this->running_value = 0;
  }
 
  bool value(void)
  {
    return this->running_value;
  }
};

// =============================================================================
sensor sensor_A = sensor(PROXIMITY_A_SENSOR);
sensor sensor_B = sensor(PROXIMITY_B_SENSOR);

#define TIMER_INTERRUPT_MS 10
#include "timer_interrupt.h"

SET_TIMER_ISR({
  sensor_A.update(); 
  sensor_B.update(); 
});

// =============================================================================
void setup()
{
  pinMode(PROXIMITY_A_SENSOR, INPUT);
  pinMode(PROXIMITY_B_SENSOR, INPUT);
  pinMode(REGISTRATION_GATE, OUTPUT);

  INIT_TIMER_INTERRUPT;
}

void loop()
{
  digitalWrite(REGISTRATION_GATE, sensor_A.value() && sensor_B.value() ? HIGH: LOW);
}
