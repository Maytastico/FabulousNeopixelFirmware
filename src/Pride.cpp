#include "Pride.h"

void Pride::loop(){
    if(cycle.isTimerReady()){
        _pController->displayArray(nonBinaryPride, 3, 0, true);
        cycle.startTimer(ANIMATION_UPDATE_RATE);
    }
}