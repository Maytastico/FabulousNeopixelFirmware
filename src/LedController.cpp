/**
 * @file LedController.cpp
 * @author MacaroniDamage
 * @brief Contains basic features of controling the 
 *        RGB Stripe
 * @version 0.1
 * @date 2020-12-16
 * 
 * 
 */

#include "LedController.h"

void LedController::setupController(uint32_t color, uint8_t brightness)
{
  this->currentColor = color;
  this->currentBrightness = brightness;
  this->brightnessToSave = brightness;
}

void LedController::turnOn()
{
  _pTransition->playTransition(this->oldBrightness, FADE_IN);
  
}

void LedController::turnOff()
{
  this->oldBrightness = this->currentBrightness;
  _pTransition->playTransition(FADE_OUT);
}

void LedController::changeColor(uint32_t color)
{
  currentColor = color;
  // sets a color on all leds
  this->fill(currentColor, 0, this->numLEDs);
  this->show();
}

void LedController::changeColorWithTransition(uint32_t color, Transition transition)
{
  updateColorWhenBrightnessChanges = true;
  //ensures that the transition mode is standart and not animation
  _pTransition->setTransitionMode(STANDARD);
  _pTransition->playTransition(transition,color);
}

//Changes and configures a Timer that triggers a save command every 3 seconds
void LedController::changeBrightness(uint8_t brightness)
{
  currentBrightness = brightness;
  // set brighness and show at LED strip

  //Just refreshes the targetColor if the third state achieved
  if (updateColorWhenBrightnessChanges == true && _pTransition->getCurrentTransitionState() == STATE_3)
  {
    this->changeColor(this->currentColor);
  }

  this->setBrightness(brightness);
  this->show();
}

//Increses or decreases the brighness relative to its last value
void LedController::setBrightnessRelative(int16_t step)
{
  int16_t actBrightness = (int16_t)currentBrightness + step;
  int8_t calculatedBrightness = currentBrightness;

  if (actBrightness < MIN_BRIGHTNESS)
  {
    calculatedBrightness = MIN_BRIGHTNESS;
  }
  else if (actBrightness > MAX_BRIGHTNESS)
  {
    calculatedBrightness = MAX_BRIGHTNESS;
  }
  else
  {
    calculatedBrightness = (uint8_t)actBrightness;
  }
  changeBrightness(calculatedBrightness);

  //Important for saveing the current brightness value
  brighnessSaveTimer.startTimer(SAVE_BRIGHTNESS_DELAY);
  brightnessToSave = calculatedBrightness;
}

//------utilities------
uint32_t LedController::generateRandomColor()
{
  uint32_t randomColorValue;
  uint8_t steps = 0;

  do
  {
    uint8_t r = random(20, 255);
    uint8_t g = random(20, 255);
    uint8_t b = random(20, 255);

    //Generates color with normal RGB values
    //if the mode is set to RGB.
    //When the mode is RGBW the program generates
    //a white value.
    switch (this->ledMode)
    {
    case RGB:
      randomColorValue = this->gamma32(this->Color(r, g, b));
      break;
    case RGBW:
      uint8_t w = random(0, 32);
      randomColorValue = this->gamma32(this->Color(r, g, b, w));
      break;
    }

    steps++;
  } while (this->lastColorValue == randomColorValue && randomColorValue > 0 && steps <= 5);

  this->lastColorValue = randomColorValue;
  return randomColorValue;
}

uint8_t LedController::generateRadomPosition()
{
  uint8_t pos = random(0, this->numPixels());
  pos = random(0, this->numPixels());
  return pos;
}

void LedController::displayArray(uint32_t *frame, uint8_t frameElements, int beginningPosition, boolean override){
  uint8_t frameIndex = 0;
  for (uint8_t i = 0; i < this->numPixels(); i++)
  { 
    if(i >= beginningPosition && i < beginningPosition+frameElements){
      this->setPixelColor(i, frame[frameIndex]);
      frameIndex++;
    }else{
      if(override == true)
        this->setPixelColor(i,this->Color(0,0,0));
    }
  }
  this->show();
}

void LedController::displayArrayStrech(uint32_t *frame, uint8_t frameElements){
  uint8_t frameIndex = 0;
  uint8_t fragmentIndex = 0;
  uint8_t fragmentLenght = this->numPixels()/frameElements;
  for (uint8_t i = 0; i < this->numPixels(); i++)
  { 
    if(fragmentIndex>=fragmentLenght){
      frameIndex++;
      fragmentIndex = 0;
    }
    this->setPixelColor(i, frame[frameIndex]);
    fragmentIndex++;
  }
  this->show();
}

//returns the current color value
uint32_t LedController::getCurrentColor()
{
  return this->currentColor;
}

//return the current Brighnessvalue
uint8_t LedController::getCurrentBrightness()
{
  return this->currentBrightness;
}

LedMode LedController::getLedMode()
{
  return this->ledMode;
}

void LedController::setUpdateColorWhenBrightnessChanges(bool updateFlag)
{
  updateColorWhenBrightnessChanges = updateFlag;
}

//Save routine of the LedController
void LedController::loop()
{
  if (brighnessSaveTimer.isTimerReady())
  {
    _pMemory->storeBrightness(this->brightnessToSave, "LedControl");
  }
}