#include "StarLight.h"

//Generates random positions and writes them into the starpositions array
void StarLight::generateStarFrame()
{
    for (unsigned int i = 0; i < AMOUNT_OF_STARS; i++)
    {

        //sets a random color to every pixel
        uint8_t pos = _pController->generateRadomPosition();
        this->starPositions[i] = pos;
    }
}

//draws the stars on the stripe
void StarLight::displayStarFrame(boolean randomIntensityActivated)
{
    _pController->fill(0);
    for (unsigned int i = 0; i < AMOUNT_OF_STARS; i++)
    {
        uint8_t intensity;
        if(randomIntensityActivated == true){
            intensity = random(200, 255);
        }
        else
        {
            intensity = 200;
        }


        switch (_pController->getLedMode())
        {
        case RGB:
            _pController->setPixelColor(starPositions[i], _pController->Color(intensity, intensity, intensity));
             break;
        case RGBW:
            _pController->setPixelColor(starPositions[i], _pController->Color(0, 0, 0, intensity));
            break; 
        }
    }
    _pController->show();
}

//executes the states
void StarLight::starLightStage()
{
    switch (stage)
    {
    case GENERATE_STARS:
        this->generateStarFrame();
        generateNewStars.startTimer(REGENERATE_STARS);
        stage = DISPLAY_STAR;
        break;
    case DISPLAY_STAR:
        this->displayStarFrame(true);
        cycle.startTimer(500);

        if(nextFallingStar.isTimerReady()){
            stage = CAST_FALLING_STAR;
            directionFrame = chooseFrameDirection();
            choosenType = chooseFallingStar(); 
        }
        else if(generateNewStars.isTimerReady()){ 
            stage = GENERATE_STARS; 
        }
        
        break;
    case CAST_FALLING_STAR:
        this->displayStarFrame(false);
        _pController->displayArray(choosenType, 7, framePosition, false);

        if(directionFrame == LEFT_TO_RIGHT){
            framePosition--;
            if(framePosition < -10){
            nextFallingStar.startTimer(CAST_NEXT_FALLING_STAR);
            cycle.startTimer(500);
            stage = DISPLAY_STAR;
        }
        }else if(RIGHT_TO_LEFT){
            framePosition++;
            
            if(framePosition > (int)_pController->numPixels()){
                nextFallingStar.startTimer(CAST_NEXT_FALLING_STAR);
                cycle.startTimer(500);
                stage = DISPLAY_STAR;
            }
        }
        cycle.startTimer(60);
        
        break;
    }
}

//Choses one of four falling star types
const uint32_t* StarLight::chooseFallingStar(){
    uint8_t randomStar = random(0,4);
    switch (randomStar)
    {
    case 0:
        if(directionFrame == LEFT_TO_RIGHT){
            return &blueFallingStar[0];
        }else{
            return &blueFallingStarM[0];
        }
        break;
    case 1:
        if(directionFrame == LEFT_TO_RIGHT){
            return &orangeFallingStar[0];
        }else{
            return &orangeFallingStarM[0];
        }
        break;
    case 2:
        return &rainbowFallingStar[0];
        break;
    case 3:
        return &whiteFallingStar[0];
        
        break;
    }
    return nullptr;
}

//Choses in which direction a star will be casted
MoveDirection StarLight::chooseFrameDirection(){
    uint8_t tmp = random(1,10);
    if(tmp % 2 >= 1){
        framePosition = 0;
        return RIGHT_TO_LEFT;
    }else
    {
        framePosition = _pController->numPixels();
        return LEFT_TO_RIGHT;
    }
}

//Will be executed by the processIRData() method in main.cpp
//so the states will be reset after a the animation was started
void StarLight::resetStateMachine()
{
    stage = GENERATE_STARS;
}

void StarLight::loop()
{
    if (cycle.isTimerReady())
    {
        starLightStage();
    } 

}