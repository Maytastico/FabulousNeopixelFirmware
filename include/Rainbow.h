#ifndef RAINBOW_H_
#define RAINBOW_H_

#include <Arduino.h>
#include "LedController.h"
#include "Timer.h"
#include "ProgramManager.h"

class LedController;

class Rainbow
{
private:
    /**
     * @brief Is used to datermine on wich step the program is
     * 
     */
    uint32_t firstHue = 0;

    /**
     * @brief The controller is used to access the stipe and define
     *        a color to a pixel
     * 
     */
    LedController *p_argb = nullptr;

    /**
     * @brief Controles when a new rainbow will be set
     * 
     */
    Timer refreshStripe;

    /**
     * @brief Goes through the 65536 times the number of leds
     *        and sets the every step to a different Led
     * 
     */
    void setRainbow();

    /**
     * @brief Steps every cycle 65536 forward
     * 
     */
    void evaluateHue();

public:
    /**
     * @brief Constructs a new Rainbow object
     * 
     */
    Rainbow() {}

    /**
     * @brief It needs the controller to modify the color of the led stripe
     * 
     * @param _controller 
     */
    void begin(LedController *_controller)
    {
        this->p_argb = _controller;
    };

    /**
     * @brief Executes the update routine for the animation
     * 
     */
    void loop();
};

#endif //RAINBOW_H_