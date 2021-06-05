#ifndef RANDOMCOLORFADE_H_
#define RANDOMCOLORFADE_H_

#include <Arduino.h>
#include "LedController.h"
#include "Timer.h"

class LedController;

class RandomColorFade
{
private:
    /**
     * @brief Decides when a new color will be faded in
     * 
     */
    Timer ChangeColor;

    /**
     * @brief Is needed to control the stripe
     * 
     */
    LedController *p_argb;
public:
    /**
     * @brief Construct a new Random Color Fade object
     * 
     */
    RandomColorFade(){}
    
    /**
     * @brief Initializes the instance
     * 
     * @param _argb 
     */
    void begin(LedController *_argb){
        p_argb = _argb;
    }

    

    /**
     * @brief Checks if the timer is ready and then sets a new color
     * 
     */
    void loop(void);
};

#endif //RANDOMCOLORFADE_H_