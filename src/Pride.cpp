#include "Pride.h"

void Pride::changeFlag(){
    uint8_t banner =  static_cast<uint8_t>(currentBanner);
    banner++;
    if(banner > static_cast<uint8_t>(lastBanner)){
        banner = 1;
    }
    currentBanner = static_cast<PrideBanners>(banner);
    _pStorage->storePrideBanner(banner);
    bannerChanged = true;
}

void Pride::processChange(){
    switch (currentBanner)
    {
    case PRIDE:
        _pController->displayArrayStrech(pride, 6);
        break;
    case LESBIAN:
        _pController->displayArrayStrech(lesbianPride, 7);
        break;
    case BI:
        _pController->displayArrayStrech(biPride, 3);
        break;
    case PAN:
        _pController->displayArrayStrech(panPride, 3);
        break;
    case TRANS:
        _pController->displayArrayStrech(transPride, 5);
        break;
    case NONBINARY:
        _pController->displayArrayStrech(nonBinaryPride, 3);
        break;
    default:
        break;
    }
    
    bannerChanged = false;
}

void Pride::loop(){
    if(cycle.isTimerReady()){
        processChange();
        cycle.startTimer(cycleRate);
    }

    if(bannerChanged){
        processChange();
    }
}