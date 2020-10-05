#ifndef _LIFEH_
#define _LIFEH_
#include <avr/io.h>

class Life
{
private:
  uint8_t life;
  uint8_t adress;

public:
  Life() {}
  Life(uint8_t _adress);
  uint8_t getLife();
  void setLife(uint8_t _life);
  void Death();
  void setLed(uint8_t _byte);
  void Init();
};
#endif
