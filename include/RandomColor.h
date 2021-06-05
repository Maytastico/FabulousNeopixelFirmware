#ifndef _RANDOMCOLOR_
#define _RANDOMCOLOR_

#include <Arduino.h>
#include "Timer.h"
#include "LedController.h"
#include "TransitionHandler.h"

class LedController;

class RandomColor
{
private:
    /**
     * @brief Init sets the first frame of the animation
     *        Loop will determine ever cycle what pixel and what color it will have
     * 
     */
    enum RandomColoStates
    {
        SHOW_FIRST,
        LOOP
    };

    /**
     * @brief Saves the random colors so they can be updated 
     *        every cycle
     * 
     */
    uint32_t colors[50];

    /**
     * @brief Will be used insinde the state machine what it
     *        will do
     * 
     */
    RandomColoStates states = SHOW_FIRST;

    /**
     * @brief The timer that handles the updates
     *        of the animation
     * 
     */
    Timer cycle;

    /**
     * @brief A LedController Library that is necessary
     *        to control the stripes
     * 
     */
    LedController *_pcontroller;

    /**
     * @brief A LedController Library that is necessary
     *        to control the stripes
     * 
     */
    TransitionHandler *_pTransition;

    /**
     * @brief The state machine 
     * 
     */
    void colorStates();

    /**
     * @brief Sets a random amount of pixel to a 
     *        randomized color on a random position
     * 
     */
    void changeRandomPixels();

public:
    /**
     * @brief Construct a new Random Color object
     * 
     */
    RandomColor(){};

    /**
     * @brief Fills the colors array with random
     *        color values
     * 
     */
    void fillRandomFrame();
    /**
     * @brief Sets the controller pointer so 
     *        the instance can access the neopixel
     *        library
     * 
     * @param _controller 
     */
    void begin(LedController *_controller, TransitionHandler *_transition)
    {
        this->_pcontroller = _controller;
        this->_pTransition = _transition;
        this->fillRandomFrame();
    }

    /**
     * @brief The animation routine that
     *        executes the 
     * 
     */
    void loop();

    /**
     * @brief Sets the state back to INIT
     * 
     */
    void resetStateMachine();

    /**
     * @brief Displays the contents of the color array
     * 
     */
    void displayRandomFrame();
};

#endif //_RANDOMCOLOR_