/**
 * @file TransitionHandler.h
 * @author MacaroniDamage
 * @brief Executes state machine that handel transitions to different
 *        stages
 * @version 0.1
 * @date 2020-12-18
 * 
 * 
 */
#include <Arduino.h>
#include "Timer.h"
#include "LedController.h"

class LedController;

#ifndef _TRANSITION_HANDLER_H_
#define _TRANSITION_HANDLER_H_

/**
 * @brief Defines wich animation is executed
 * 
 */
enum Transition
{
    COLOR_TO_COLOR,
    FADE_TO,
    FADE_OUT,
    FADE_IN
};

/**
 * @brief General definitions of transition state
 * 
 */
enum TransitionState
{
    STDBY,
    STATE_1,
    STATE_2,
    STATE_3
};

/**
 * @brief Defines what kind of Transition will be played
 *        Animation -> Disables the ChangeColor method in the fade animation
 *        Standard -> Handels everything as usual
 *        Disable_Animation -> Fades out without setting color and Fades in with setting the color
 * 
 */
enum TransitionMode
{
    STANDARD,
    ANIMATION,
    DISABLE_ANIMATION
};


/**
 * @brief Defines a delay after wich time the
 *        brightness will be refreshed
 * 
 */
const uint16_t BRIGHTNESS_UPDATE = 50;

/**
 * @brief Defines the default transition when the user
 *        changes a color over the remote 
 * 
 */
const Transition DEFAULT_TRANSITION = FADE_TO;

class TransitionHandler
{
private:
    //------Attributes------

    /**
     * @brief Defines the wished color value
     * 
     */
    uint32_t targetColor;
    /**
     * @brief Defines the current color that was 
     *        fetched from the LEDController instace
     * 
     */
    uint32_t currentColor;

    /**
     * @brief Defines the currentBrighness that was 
     *        fetched from the LEDController instace
     * 
     */
    uint8_t currentBrightness;
    /**
     * @brief Defines the wished brightness
     * 
     */
    uint8_t targetBrightness;

    /**
     * @brief Used to temprorily save the old brightness
     * 
     */
    uint8_t oldBrightness;

    /**
     * @brief Is the pointer that contains the LedController object
     * 
     */
    LedController *_pController;

    /**
     * @brief Defines wich transition will be executed
     * 
     */
    Transition transition;

    /**
     * @brief Defines wich state the transition has
     * 
     */
    TransitionState transitionState;

    /**
     * @brief Is used to datermine what commands will be
     *        enabled and disabled
     * 
     */
    TransitionMode transitionMode;

    /**
     * @brief Defines in wich rate the brightness 
     *        animation will be executed
     * 
     */
    Timer brightnessUpdateTimer;

    /**
     * @brief Return wheather a transition was played
     * 
     */
    bool transitionisPlayed;

    //----private methods-----
    /**
     * @brief Configures the instance so that is 
     *        Smoothly transitions to the wished brightness
     * 
     */
    void gotoBrightness();

    /**
     * @brief A state machine that configures the instance so that
     *        it toggles the brightness low sets the wished target color
     *        and toggles the brighness to the old brightness state
     * 
     */
    void Fade();

    /**
     * @brief A state machine that configures the instance so that it
     *        toggles the brightness to the minimum value
     * 
     */
    void FadeOut();

    /**
     * @brief A state machine that configures the instance so that it
     *        toggles the brightness to a wished value
     * 
     */
    void FadeIn();

public:
    /**
     * @brief Construct a new Transition Handler object
     * 
     */
    TransitionHandler(){};

    /**
     * @brief Initilizes the instance
     * 
     * @param controller 
     */
    void begin(LedController *controller)
    {
        _pController = controller;
    }

    /**
     * @brief Configures the instace so that the state machines
     *        plays a certain transition to a specified Color
     * 
     * @param targetColor The Color that will be transitioned to
     * @param transition Defines the kind of animation that will be playes
     */
    void playTransition(Transition transition, uint32_t targetColor);

    /**
     * @brief 
     * 
     * @param targetBrightness 
     * @param transition 
     */
    void playTransition(uint8_t targetBrightness, Transition transition);

    /**
     * @brief Configures the instace so that the state machine
     *        plays a certain transition without setting another color.
     *        Can be used to turn on or turn off the LEDs
     * 
     * @param transition Defines the kind of animation that will be playes
     */
    void playTransition(Transition transition);

    /**
     * @brief Defines what funtions are enabled or disabled
     * 
     * @param transitionMode 
     */
    void setTransitionMode(TransitionMode transitionMode);

    /**
     * @brief Returns the current transitionState value
     * 
     * @return TransitionState 
     */
    TransitionState getCurrentTransitionState();

    uint8_t getCurrentBrightness();

    uint8_t getTargetBrightness();

    /**
     * @brief The routine that will be executed during every loop cycle
     *        and executes the state machines
     * 
     */
    void loop();
};

#endif //_TRANSITION_HANDLER_H_