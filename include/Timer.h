/**
 * @file Timer.h
 * @author MacaroniDamage
 * @brief A useful class that makes timer hanling easier
 * @version 0.1
 * @date 2020-12-20
 * 
 * 
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <Arduino.h>


class Timer
{
private:
  unsigned long timerStart = 0;
  unsigned long timerTarget = 0;

public:
  void startTimer(long msec)
  {
    timerStart = millis();
    timerTarget = msec;
  }

  bool isTimerReady()
  {
    return (millis() - timerStart) > timerTarget;
  }
};

#endif // TIMER_H_
