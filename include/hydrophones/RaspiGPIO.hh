// Based on TinyGPIO Here: http://abyz.me.uk/rpi/pigpio/examples.html

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>

namespace MuddSub::Acoustics
{

#define RPI_GPILEV0 13
#define RPI_GPILEV1 14

// GPIO modes
#define GPIO_INPUT  0
#define GPIO_OUTPUT 1

class GPIO
{

public:

  GPIO() = delete;
  GPIO(bool& success);

  void setMode(unsigned int pin, unsigned int mode);
  unsigned int getMode(unsigned int pin);

  // pull up/down resistors
  void setPUD(unsigned int pin, unsigned int PUD);

  unsigned int gpioReadPin(unsigned int pin);

  void gpioWritePin(unsigned int gpio, unsigned int level);

  uint32_t gpioReadBank1();
  uint32_t gpioReadBank2();


private:

  volatile uint32_t* gpioReg_;


};
}
