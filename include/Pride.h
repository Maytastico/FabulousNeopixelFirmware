#ifndef PRIDE_H_
#define PRIDE_H_

#include <Arduino.h>
#include <LedController.h>
#include <Timer.h>
#include "ProgramManager.h"
#include "Color_Definitions.h"

class LedController;


class Pride
{
private:

    uint32_t pride [6] = {_pController->Color(228, 3, 3), _pController->Color(255, 140, 0), _pController->Color(255, 237, 0), _pController->Color(0, 128, 38), _pController->Color(0, 77, 255), _pController->Color(117, 7, 135)};
    uint32_t transPride [5] = {_pController->Color(85, 105, 252), _pController->Color(247, 68, 184), _pController->Color(255, 255, 255, 255),  _pController->Color(247, 68, 84), _pController->Color(85, 105, 252)};
    uint32_t lesbianPride [7] = {_pController->Color(213, 45, 0), _pController->Color(239, 118, 10), _pController->Color(255, 154, 50),  _pController->Color(255, 255, 255, 255), _pController->Color(209, 98, 164) , _pController->Color(181, 86, 144) , _pController->Color(163, 2, 98)};
    uint32_t panPride [3] = {_pController->Color(255, 33, 140), _pController->Color(255, 216, 0), _pController->Color(33, 177, 255)};
    uint32_t biPride [3] = {_pController->Color(214, 2, 112), PURPLE, _pController->Color(0, 56, 168)};
    uint32_t nonBinaryPride [3] = {YELLOW, WHITE, PURPLE};

    /**
     * @brief Saves all pride banners that can be displayed
     * 
     */
    enum PrideBanners{
        PRIDE,
        LESBIAN,
        BI,
        PAN,
        TRANS,
        NONBINARY
    };

    LedController *_pController = nullptr;

    Timer cycle;


public:
    Pride(){}

    void begin(LedController *_controller){
        this->_pController = _controller;
    };

    void displayFlag();

    void loop();
};



#endif //PRIDE_H_