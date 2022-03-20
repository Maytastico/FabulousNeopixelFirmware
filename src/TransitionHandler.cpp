/**
 * @file TransitionHandler.cpp
 * @author MacaroniDamage
 * @brief Executes state machine that handel transitions to different
 *        stages
 * @version 0.1
 * @date 2020-12-18
 * 
 * 
 */
#include "TransitionHandler.h"

/** Configures the instace so that
 * it triggers the wished state machine
**/
void TransitionHandler::playTransition(Transition transition, uint32_t targetColor)
{
  this->targetColor = targetColor;
  this->currentColor = _pController->getCurrentColor();
  this->currentBrightness = _pController->getCurrentBrightness();

  this->transition = transition;
  this->transitionState = STATE_1;
}

//sets the target brightness and gets the current values from the controller
void TransitionHandler::playTransition(uint8_t targetBrightness, Transition transition)
{
  this->targetBrightness = targetBrightness;
  this->currentColor = _pController->getCurrentColor();
  this->currentBrightness = _pController->getCurrentBrightness();

  this->transition = transition;
  this->transitionState = STATE_1;
}

//Just sets the transition values and gets the current values from the controller
void TransitionHandler::playTransition(Transition transition)
{
  this->currentColor = _pController->getCurrentColor();
  this->currentBrightness = _pController->getCurrentBrightness();

  this->transition = transition;
  this->transitionState = STATE_1;
  //Serial.println("Stage: " + String(transitionState));
}

void TransitionHandler::setTransitionMode(TransitionMode transitionMode)
{
  this->transitionMode = transitionMode;
}

TransitionState TransitionHandler::getCurrentTransitionState()
{
  return this->transitionState;
}

//Sets the targetBrightness to the minimun value sets the new color
//and set the targetBrigtness to the wished value
void TransitionHandler::Fade()
{
  switch (transitionState)
  {
  case STDBY:
    transitionState = STDBY;
    break;
  case STATE_1: //Fade_Out

    //temporaily saves the brightness to set it later.
    this->oldBrightness = this->currentBrightness;

    //turns the brightness of the stripe to minimal brightness
    this->targetBrightness = MIN_BRIGHTNESS;

    //changes the state
    transitionState = STATE_2;
    break;
  case STATE_2: //SET COLOR
    if (currentBrightness <= targetBrightness)
    {
        //Tells the Controller what color is now the current one
        //and dates the stripe up
        transitionState = STATE_3;
        //Dates the currentColor and currentBrightness up
        this->currentColor = this->targetColor;
        this->targetBrightness = this->oldBrightness;
        //Executes the changeColor function if transitionMode is in
        //a standart state so it won't be executed durig an animation
        if (transitionMode == STANDARD)
          _pController->changeColor(currentColor);
    }
    else
    {
      transitionState = STATE_2;
    }
    break;
  case STATE_3: //Fade IN
    if (currentBrightness < targetBrightness)
    {
      transitionState = STATE_3;
    }
    else
    {
      currentColor = targetColor;
      transitionState = STDBY;
      transitionisPlayed = false;
    }
    break;
  default:
    transitionState = STDBY;
  }
}

// change to a target brightness
void TransitionHandler::gotoBrightness()
{
  int16_t actBrightness = (int16_t)currentBrightness;
  if (brightnessUpdateTimer.isTimerReady())
  {
    if (targetBrightness > currentBrightness)
    {
      actBrightness += BRIGHTNESS_STEP;
      if (actBrightness > targetBrightness)
        currentBrightness = targetBrightness;
      else
        currentBrightness = actBrightness;
    }
    else if (targetBrightness < currentBrightness)
    {
      actBrightness -= BRIGHTNESS_STEP;
      if (actBrightness < targetBrightness)
        currentBrightness = targetBrightness;
      else
        currentBrightness = (uint8_t)actBrightness;
    }
    //Refreshes the stripe
    _pController->changeBrightness(currentBrightness);
    //Refreshed the update timer
    brightnessUpdateTimer.startTimer(BRIGHTNESS_UPDATE);
  }
}

//Sets the targetBrightnes to the minimum brightness and waits until it is achieved
//set the transition state then to Standby
void TransitionHandler::FadeOut()
{
  switch (transitionState)
  {
  case STATE_1:
    this->targetBrightness = MIN_BRIGHTNESS;
    this->transitionState = STATE_2;
    break;
  case STATE_2:
    if (currentBrightness <= targetBrightness)
    {
      this->transitionState = STDBY;
    }
    break;
  }
}

//Waits until the targetBrightness is equal or higher then the currentBrighness
//and the set the TargetHandler to Standby
void TransitionHandler::FadeIn()
{
  switch (transitionState)
  {
  case STATE_1:
    //Will be modified so the changeBrightness method
    //refreshes the solid color
    this->transitionState = STATE_3;
    break;
  case STATE_3:
    if (currentBrightness >= targetBrightness)
    {
      this->transitionState = STDBY;
    }
    break;
  }
}

uint8_t TransitionHandler::getCurrentBrightness(){
  return currentBrightness;
}

uint8_t TransitionHandler::getTargetBrightness(){
  return targetBrightness;
}
void TransitionHandler::loop()
{
  if (transitionState != STDBY)
  {
    switch (transition)
    {
    case FADE_TO:
      this->Fade();
      this->gotoBrightness();
      break;
    case FADE_OUT:
      this->FadeOut();
      this->gotoBrightness();
      break;
    case FADE_IN:
      this->FadeIn();
      this->gotoBrightness();
      break;
    default:
      _pController->changeColor(targetColor);
      this->transitionState = STDBY;
      break;
    }
  }
}
