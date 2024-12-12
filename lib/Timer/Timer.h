#include <sys/time.h>

#ifndef __Timer_h
#define __Timer_h

class Timer {

  double t_cpu;
  struct timeval Tvalue;
  struct timezone dummy;
  bool timerStarted;

  public:

  Timer();

  void start();
  double read();
  void stop();
  double get();
};

#endif


