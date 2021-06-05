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

  void printDebug(String name){
    Serial.println("0,0,0,0,0,0,0,Timer " + name + " Debug Info,0,0,0,0,0,0,0");
    Serial.println("Timer Start: " + String(timerStart));
    Serial.println("Timer Target: " + String(timerTarget));
    Serial.println("Is accieved: " + String(isTimerReady()));
    Serial.println("0,0,0,0,0,0,0,Timer Debug Info,0,0,0,0,0,0,0");
  }
};

#endif // TIMER_H_
