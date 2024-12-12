#include "Timer.h"

Timer::Timer() {
  t_cpu = 0;
}
void Timer::start() {
  gettimeofday(&Tvalue,&dummy);
  timerStarted = true;
}
void Timer::stop() {
  if(timerStarted == false) t_cpu = 0;
  else {
    struct timeval Tvalue2;
    struct timezone dummy2;
    gettimeofday(&Tvalue2,&dummy2);
    double startTime = ((double) Tvalue.tv_sec +1.e-6*((double) Tvalue.tv_usec));
    double endTime = ((double) Tvalue2.tv_sec +1.e-6*((double) Tvalue2.tv_usec));
    t_cpu = endTime-startTime;
    timerStarted = false;
  }  
}
double Timer::read() {
  if(timerStarted == false) t_cpu = 0;
  else {
    struct timeval Tvalue2;
    struct timezone dummy2;
    gettimeofday(&Tvalue2,&dummy2);
    double startTime = ((double) Tvalue.tv_sec +1.e-6*((double) Tvalue.tv_usec));
    double endTime = ((double) Tvalue2.tv_sec +1.e-6*((double) Tvalue2.tv_usec));
    t_cpu = endTime-startTime;
  }
  return t_cpu;
}
double Timer::get() {
  return t_cpu;
}




