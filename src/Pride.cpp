#include "Pride.h"

void Pride::changeFlag(){
    uint8_t banner =  static_cast<uint8_t>(currentBanner);
    banner++;
    if(banner > static_cast<uint8_t>(LAST_BANNER_IN_ENUM)){
        banner = 1;
    }
    currentBanner = static_cast<PrideBanners>(banner);
    _pStorage->storePrideBanner(banner);
    bannerChanged = true;
}

void Pride::processChange(){
    switch (currentBanner)
    {
    case PRIDE_BANNER:
        _pController->displayArrayStrech(&pride[0], 6);
        break;
    case LESBIAN_BANNER:
        _pController->displayArrayStrech(&lesbianPride[0], 7);
        break;
    case BI_BANNER:
        _pController->displayArrayStrech(&biPride[0], 3);
        break;
    case PAN_BANNER:
        _pController->displayArrayStrech(&panPride[0], 3);
        break;
    case TRANS_BANNER:
        _pController->displayArrayStrech(&transPride[0], 5);
        break;
    case NONBINARY_BANNER:
        _pController->displayArrayStrech(&nonBinaryPride[0], 3);
        break;
    default:
        break;
    }
    
    bannerChanged = false;
}

void Pride::loop(){
    if(cycle.isTimerReady()){
        processChange();
        cycle.startTimer(ANIMATION_UPDATE_RATE);
    }

}