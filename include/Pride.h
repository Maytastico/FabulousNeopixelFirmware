#ifndef PRIDE_H_
#define PRIDE_H_

#include <Arduino.h>
#include <LedController.h>
#include <Timer.h>
#include "ProgramManager.h"
#include "Color_Definitions.h"
#include "ProgramManager.h"
#include <avr/pgmspace.h>

class LedController;

//Data defined to be written into flash
//Has to be defined global because of PROGMEM
const uint32_t pride [6] PROGMEM = {14942979, 16747520, 16772352, 32806, 19967, 7669639};
const uint32_t transPride [5] PROGMEM= {5597692, 16204984, 16777215,  16204884, 5597692};
const uint32_t lesbianPride [7] PROGMEM= {13970688, 15693322, 16751154,  16777215, 13722276, 11884176, 10682978};
const uint32_t panPride [3] PROGMEM= {16720268, 16766976, 2208255};
const uint32_t biPride [3] PROGMEM= {HOTPINK, PURPLE, 14504};
const uint32_t nonBinaryPride [3] PROGMEM = {YELLOW, WHITE, PURPLE};

/**
*  @brief Saves all pride banners that can be displayed
* 
*/
enum PrideBanners{
    NO_BANNER,
    PRIDE_BANNER,
    LESBIAN_BANNER,
    BI_BANNER,
    PAN_BANNER,
    TRANS_BANNER,
    NONBINARY_BANNER
};
    
/**
* @brief Saves the last Pridebanner in the PrideBanner enumeration
* 
*/
const PrideBanners LAST_BANNER_IN_ENUM = NONBINARY_BANNER;

class Pride
{
private:

    /**
     * @brief Saves a reference to the led control class to modify the colors of the adressable led
     * 
     */
    LedController *_pController = nullptr;

    /**
     * @brief Saves a refence to the eprom class to store what banner was shown before the light was turned of
     * 
     */
    EpromHandler *_pStorage = nullptr;

    /**
     * @brief Saves the state of the Pridebanner that is shown at the moment
     * 
     */
    PrideBanners currentBanner = PRIDE_BANNER;

    /**
     * @brief Indicates whether the command to change the banner was given
     * 
     */
    boolean bannerChanged = true;

    /**
     * @brief Stores when the image will be changed the next time
     * 
     */
    Timer cycle;


public:
    Pride(){}

    /**
     * @brief Initializes the Object with all the needed references
     * 
     * @param _controller 
     * @param _storage 
     */
    void begin(LedController *_controller, EpromHandler *_storage){
        this->_pController = _controller;
        this->_pStorage = _storage;
        if(_pStorage->getPrideBanner() != 0)
            this->currentBanner = static_cast<PrideBanners>(_storage->getPrideBanner());
    };

    /**
     * @brief Counts through the accessiable Pridebanners for chaning the displayed Pridebannes
     * 
     */
    void changeFlag();

    /**
     * @brief 
     * 
     */
    void processChange();

    void loop();
};



#endif //PRIDE_H_