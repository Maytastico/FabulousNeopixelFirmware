#ifndef LEDCONTROLLER_H_
#define LEDCONTROLLER_H_

//Includes
#include <Adafruit_NeoPixel.h>
#include "EpromHandler.h"
#include "Timer.h"
#include "TransitionHandler.h"
#include <avr/pgmspace.h>

/**
 * @brief Defines in which mode the Leds will be driven.
 *        So programs know what data to send
 * 
 */
enum LedMode
{
    RGB,
    RGBW,
};

/** 
 * Is used to define how high the brightness value will be increased after pressing the corrosponding button
 * 
 */
const uint8_t BRIGHTNESS_OFFSET = 30;
/* 
 * Defines how many steps the brightness will be in- or decreased during an fade effect.
 */
const uint8_t BRIGHTNESS_STEP = 5;
/**
 * Defines the maximum brightness
 */
const uint8_t MAX_BRIGHTNESS = 255;
/**
 * Defines the minimum brightness
 */
const uint8_t MIN_BRIGHTNESS = 0;

/**
 * @brief Defines how it takes until the already 
 *        changed brighness will be saved
 * 
 */
const uint16_t SAVE_BRIGHTNESS_DELAY = 1000;

class LedController : public Adafruit_NeoPixel
{
private:

    /**
     * @brief Defines how color data will be send to the strips
     * 
     */
    LedMode ledMode;

    /**
     * @brief Decides when the color gets refreshed when the brightness
     *        of the stripe will be changed. Can be useful when an animation
     *        program transitions to its animation and does not want that the
     *        color gets refreshed
     * 
     */
    bool updateColorWhenBrightnessChanges = true;

    /**
     * @brief Used to trigger transitions for certain methods
     * 
     */
    TransitionHandler *_pTransition;

    /**
     * @brief Used to save the color and brightness values
     * 
     */
    EpromHandler *_pMemory;

    /**
     * @brief Contains the already set color
     * 
     */
    uint32_t currentColor;

    /**
     * @brief Is used for the random Color method to
     *        ensure that the next random color value is not the same
     * 
     */
    uint32_t lastColorValue;

    /**
     * @brief temporarily saves the ast position values
     *        so the next value won't be the last one
     * 
     */
    uint8_t lastPositionValue;

    /**
     * @brief Contains the already set brightness
     * 
     */
    uint8_t currentBrightness;

    /**
     * @brief Is for temporarily save the old Brightness values
     *        when the user presses the OFF button
     * 
     */
    uint8_t oldBrightness;

    /**
     * @brief Contains the brightness value that will be saved
     *        It will be used by the setBrightnessRelative method.
     * 
     */
    uint8_t brightnessToSave;

    /**
     * @brief A timer that handles only saving the brightness values
     * 
     */
    Timer brighnessSaveTimer;

public:
    /**
     * @brief Construct a new Led Controller object
     * 
     * @param numPixels 
     * @param ledPin 
     * @param type 
     */
    LedController(uint16_t numPixels, uint8_t ledPin, LedMode ledMode, neoPixelType type, EpromHandler *memory, TransitionHandler *transition) : Adafruit_NeoPixel(numPixels, ledPin, type)
    {
        _pMemory = memory;
        _pTransition = transition;

        this->ledMode = ledMode; 
    };

    /**
     * @brief Calls the TransitionHandler instance so that it
     *        turns its target Brightness to the minimum value
     * 
     */
    void turnOff();

    /**
     * @brief Configures the TransitionHandle instace so that it turns
     *        its targetBrigtness to the oldValue
     * 
     */
    void turnOn();

    /**
     * @brief Setup the last color and
     *         brightness state of the object
     * 
     * @param color 
     * @param brightness 
     */
    void setupController(uint32_t color, uint8_t brightness);

    /**
     * @brief Calls the transition instance that will initiate the transition
     * 
     * @param targetColor 
     * @param transition 
     */
    void changeColorWithTransition(uint32_t targetColor, Transition transition);


    /**
     * @brief Sets a Color 
     * 
     * @param color 
     */
    void changeColor(uint32_t color);

    /**
     * @brief Sets a Brightness
     * 
     * @param brightness 
     */
    void changeBrightness(uint8_t brightness);

    /**
     * @brief Sets the Brightness Relative 
     *        to the current Brightness
     * 
     * @param step 
     */
    void setBrightnessRelative(int16_t step);

    //Utilities
    /**
     * @brief Generates a random color value
     * 
     * @return uint32_t 
     */
    uint32_t generateRandomColor();

    /**
     * @brief Returns a value between 0 and amount of pixels
     * 
     */
    uint8_t generateRadomPosition();

    /**
     * @brief Shows an array on the stripe
     * 
     * @param frame constant array in program memory
     * @param frameElements 
     * @param position 
     */
    void displayArray(const uint32_t *frame, uint8_t frameElements, int position, boolean override);

    /**
     * @brief Displayes a array and streches the segments trough the whole stripe lenght.
     *        It is important to set the right number of leds so the segments will be displayed right.
     * 
     * @param frame 
     * @param frameElements 
     */
    void displayArrayStrech(const uint32_t *frame, uint8_t frameElements);

    //Setter
    /**
     * @brief Sets the status of the instance that decides whether 
     *        the color value will be refreshed after the brightness gets 
     *        changed.
     * 
     * @param updateColor 
     */
    void setUpdateColorWhenBrightnessChanges(bool updateColor);

    //Getter
    /**
     * @brief Get the Current Color object
     * 
     * @return uint32_t 
     */
    uint32_t getCurrentColor();

    /**
     * @brief Get the Current Brightness
     * 
     * @return uint8_t 
     */
    uint8_t getCurrentBrightness();

    /**
     * @brief Get the Current Brightness
     * 
     * @return uint8_t 
     */
    LedMode getLedMode();

    //Save routine
    /**
     * @brief Mainly saves the brightness data every 3 seconds
     * 
     */
    void loop();
};

#endif // LEDCONTROLLER_H_