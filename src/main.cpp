#include <Arduino.h>
#include <IRremote.h>
#include "IRReceiver.h"
#include "Color_Definitions.h"
#include "LedController.h"
#include "EpromHandler.h"
#include "ProgramManager.h"
#include "TransitionHandler.h"
#include "Rainbow.h"
#include "RandomColorFade.h"
#include "RandomColor.h"
#include "StarLight.h"
#include "Pride.h"
//Specifiy your remote here
#include "Button_Definition_24.h"

//Pin Definitions
const uint8_t PowerOn_Pin = 7; //temp
const byte LED_Pin = 6;
const uint8_t IR_Pin = 5;
const uint16_t numPixels = 30;

//Declarations

//--Transition Handler--
TransitionHandler transitionHandler;
//--Program manager--
ProgramManager manager;
//-----EEPROM-Handler----
EpromHandler memory;
//-----IR-Receiver-----
//IR Control Objects
IRrecv irrecv(IR_Pin);
//Handles Received Data;
IRReceiver irReceiver(&irrecv);
//---------ARGB--------
//Handles Neopixel
LedController pixels(numPixels, LED_Pin, RGBW, NEO_GRBW + NEO_KHZ800, &memory, &transitionHandler);

//-------------Animation Programs-----------------

//Executes a rainbow program
Rainbow rainbow;

//Executes a random color program
RandomColorFade randomColorFade;

//Executes a program that sets
//every pixel to a random color
RandomColor randomColor;

Pride prideAnimation;

StarLight starLight;

Timer debug;

Timer manuelColorRefresh;

void setup()
{

  //Initilizes the TransitionHandler
  transitionHandler.begin(&pixels);

  //Serial commuinication
  Serial.begin(9600);

  // Set the power on pin as output and switch on
  pinMode(PowerOn_Pin, OUTPUT);    //temp
  digitalWrite(PowerOn_Pin, true); //temp

  //Initializes EEPROM Memory
  memory.begin();

  // Initialize IR Receiver
  irReceiver.begin();

  // Initialize LedController Libary and Led stripe
  pixels.begin();
  pixels.changeBrightness(memory.getSavedBrightness());
  pixels.setupController(memory.getSavedColor(), memory.getSavedBrightness());
  if (memory.getSavedProgram() == SET_MANUEL_COLOR)
  {
    pixels.changeColorWithTransition(memory.getSavedColor(), DEFAULT_TRANSITION);
  }

  //Initilizes the programm manager and casts the number to an Programm enum
  manager.setProgram(static_cast<Program>(memory.getSavedProgram()));
  manager.setStore(&memory);

  //------Animation Setup------
  rainbow.begin(&pixels);

  randomColorFade.begin(&pixels);

  randomColor.begin(&pixels, &transitionHandler);

  starLight.begin(&pixels);

  prideAnimation.begin(&pixels);

  debug.startTimer(1000);
}

/**
 * @brief trys to pull data from the infrared receiver
 * 
 */
void processIRData(void);

void loop()
{
  // if (debug.isTimerReady())
  // {
  //   Serial.println(memory.getSavedProgram());
  //   Serial.println(manager.getCurrentProgram());
  //   Serial.println(String(memory.getSavedBrightness()));
  //   Serial.println(String(memory.getSavedColor()));
  //   Serial.print(pixels.getBrightness());

  //   debug.startTimer(1000);
  // }



  // receive and decode IR data
  if (irReceiver.isDataReady())
  {
    processIRData();
  } // End  if (myIr.isDataReady())

  //Performs a periodical save of the brightness value every 3 seconds
  pixels.loop();

  //Executes certain state machines that handles transitioning
  //from one to another color
  transitionHandler.loop();

  //Defines what loop will be executed
  switch (manager.getCurrentProgram())
  {
  case OFF:
    break;
  case SET_MANUEL_COLOR:
    //This is for when the leds get unpluged so they regain the sate after disconnecting
    if(transitionHandler.getCurrentTransitionState() == STDBY){
      if(manuelColorRefresh.isTimerReady()){
        pixels.changeColor(memory.getSavedColor());
        manuelColorRefresh.startTimer(1000);
      }
    }
    break;
  case RANDOM:
    randomColorFade.loop();
    break;
  case RANDOM_COLOR_FRAME:
    if (transitionHandler.getCurrentTransitionState() == STDBY || transitionHandler.getCurrentTransitionState() == STATE_3)
    {
      randomColor.loop();
    }
    break;
  case STAR_LIGHT:
    if (transitionHandler.getCurrentTransitionState() == STDBY || transitionHandler.getCurrentTransitionState() == STATE_3)
    {
      starLight.loop();
    }
    break;
  case RAINBOW:
    if (transitionHandler.getCurrentTransitionState() == STDBY || transitionHandler.getCurrentTransitionState() == STATE_3)
    {
      rainbow.loop();
    }
    break;
  case PRIDE:
    if (transitionHandler.getCurrentTransitionState() == STDBY || transitionHandler.getCurrentTransitionState() == STATE_3)
    {
      prideAnimation.loop();
    }
  break;
  }
}

void processIRData()
{
  uint32_t data = irReceiver.getEncodedData();

  switch (data)
  {
    //Control Stripe

  case BRIGHT_DOWN:
    // decrease brightness, after 5s store value to EEPROM
    pixels.setBrightnessRelative(-BRIGHTNESS_OFFSET);
    break;
  case BRIGHT_UP:
    // increase brightness, after 5s store value to EEPROM
    pixels.setBrightnessRelative(BRIGHTNESS_OFFSET);
    break;

  case ON_POWER:
    if(manager.getCurrentProgram()==OFF){
      Program savedProgram = static_cast<Program>(memory.getSavedProgram());
      pixels.turnOn();
      manager.setProgram(savedProgram);
      if (manager.getCurrentProgram() == RANDOM_COLOR_FRAME)
      {
        randomColor.resetStateMachine();
        transitionHandler.playTransition(FADE_IN);
      }
      //Disables the static color update, if it isn't the Manuel Color Mode
      if(savedProgram != SET_MANUEL_COLOR){
        pixels.setUpdateColorWhenBrightnessChanges(false);
      }
    }
    break;
  case OFF_POWER:
    pixels.turnOff();
    manager.setProgram(OFF);
    break;
  case CHANGE_TO_RAINBOW:
    if (manager.getCurrentProgram() == RAINBOW)
    {
      manager.setProgram(SET_MANUEL_COLOR);
      pixels.changeColorWithTransition(memory.getSavedColor(), DEFAULT_TRANSITION);
    }
    else
    {
      transitionHandler.playTransition(FADE_TO);
      transitionHandler.setTransitionMode(ANIMATION);
      manager.setProgram(RAINBOW);
      pixels.setUpdateColorWhenBrightnessChanges(false);
    }
    break;
  case CHANGE_TO_RANDOM:
    if (manager.getCurrentProgram() == RANDOM)
    {
      manager.setProgram(SET_MANUEL_COLOR);
      pixels.changeColorWithTransition(memory.getSavedColor(), DEFAULT_TRANSITION);
    }
    else
    {
      transitionHandler.setTransitionMode(ANIMATION);
      pixels.setUpdateColorWhenBrightnessChanges(false);
      manager.setProgram(RANDOM);
    }
    break;

  case CHANGE_TO_WALK:
    if (manager.getCurrentProgram() == RANDOM_COLOR_FRAME)
    {
      manager.setProgram(SET_MANUEL_COLOR);
      pixels.changeColorWithTransition(memory.getSavedColor(), DEFAULT_TRANSITION);
    }
    else
    {
      //Random Color Frame
      /* transitionHandler.setTransitionMode(ANIMATION);
      pixels.setUpdateColorWhenBrightnessChanges(false);
      transitionHandler.playTransition(FADE_TO);
      randomColor.resetStateMachine();
      manager.setProgram(RANDOM_COLOR_FRAME); */

      //Pride Animation
      transitionHandler.setTransitionMode(ANIMATION);
      pixels.setUpdateColorWhenBrightnessChanges(false);
      manager.setProgram(PRIDE);
    }
    break;

  case CHANGE_TO_FLASH:
    if (manager.getCurrentProgram() == STAR_LIGHT)
    {
      manager.setProgram(SET_MANUEL_COLOR);
      pixels.changeColorWithTransition(memory.getSavedColor(), DEFAULT_TRANSITION);
    }
    else
    {
      transitionHandler.setTransitionMode(ANIMATION);
      pixels.setUpdateColorWhenBrightnessChanges(false);
      transitionHandler.playTransition(FADE_TO);
      starLight.resetStateMachine();
      manager.setProgram(STAR_LIGHT);
    }
    break;

    //Stripe Color

  case RED_COLOR:
    memory.storeColor(RED);
    pixels.changeColorWithTransition(RED, DEFAULT_TRANSITION);
    manager.setProgram(SET_MANUEL_COLOR);
    break;
  case ORANGE_RED_COLOR:
    memory.storeColor(ORANGERED);
    pixels.changeColorWithTransition(ORANGERED, DEFAULT_TRANSITION);
    manager.setProgram(SET_MANUEL_COLOR);
    break;
  case ORANGE_COLOR:
    memory.storeColor(ORANGE);
    pixels.changeColorWithTransition(ORANGE, DEFAULT_TRANSITION);
    manager.setProgram(SET_MANUEL_COLOR);
    break;
  case ORAGNE_YELLOW_COLOR:
    memory.storeColor(GOLD);
    pixels.changeColorWithTransition(GOLD, DEFAULT_TRANSITION);
    manager.setProgram(SET_MANUEL_COLOR);
    break;
  case YELLOW_COLOR:
    memory.storeColor(YELLOW);
    pixels.changeColorWithTransition(YELLOW, DEFAULT_TRANSITION);
    manager.setProgram(SET_MANUEL_COLOR);
    break;

  case GREEN_COLOR:
    memory.storeColor(pixels.Color(0, 255, 0));
    pixels.changeColorWithTransition(pixels.Color(0, 255, 0), DEFAULT_TRANSITION);
    manager.setProgram(SET_MANUEL_COLOR);
    break;
  case LIME_COLOR:
    memory.storeColor(FORESTGREEN);
    pixels.changeColorWithTransition(FORESTGREEN, DEFAULT_TRANSITION);
    manager.setProgram(SET_MANUEL_COLOR);
    break;
  case DARK_LIME_COLOR:
    memory.storeColor(DARKGREEN);
    pixels.changeColorWithTransition(DARKGREEN, DEFAULT_TRANSITION);
    manager.setProgram(SET_MANUEL_COLOR);
    break;
  case DARK_GREEN_COLOR:
    memory.storeColor(DARKCYAN);
    pixels.changeColorWithTransition(DARKCYAN, DEFAULT_TRANSITION);
    manager.setProgram(SET_MANUEL_COLOR);
    break;
  case DARKER_GREEN_COLOR:
    memory.storeColor(SEAGREEN);
    pixels.changeColorWithTransition(SEAGREEN, DEFAULT_TRANSITION);
    manager.setProgram(SET_MANUEL_COLOR);
    break;

  case BLUE_COLOR:
    memory.storeColor(pixels.Color(0, 0, 255));
    pixels.changeColorWithTransition(pixels.Color(0, 0, 255), DEFAULT_TRANSITION);
    manager.setProgram(SET_MANUEL_COLOR);
    break;
  case LIGHT_BLUE_COLOR:
    memory.storeColor(ROYALBLUE);
    pixels.changeColorWithTransition(ROYALBLUE, DEFAULT_TRANSITION);
    manager.setProgram(SET_MANUEL_COLOR);
    break;
  case LIGHT_PURPLE_COLOR:
    memory.storeColor(INDIGO);
    pixels.changeColorWithTransition(INDIGO, DEFAULT_TRANSITION);
    manager.setProgram(SET_MANUEL_COLOR);
    break;
  case PURPLE_COLOR:
    memory.storeColor(PURPLE);
    pixels.changeColorWithTransition(PURPLE, DEFAULT_TRANSITION);
    manager.setProgram(SET_MANUEL_COLOR);
    break;
  case MAGENTA_COLOR:
    memory.storeColor(HOTPINK);
    pixels.changeColorWithTransition(HOTPINK, DEFAULT_TRANSITION);
    manager.setProgram(SET_MANUEL_COLOR);
    break;

  case WHITE_COLOR:
      switch (pixels.getLedMode())
      {
      case RGB:
        memory.storeColor(WHITE);
        pixels.changeColorWithTransition(WHITE, DEFAULT_TRANSITION);
        break;

      case RGBW:
        memory.storeColor(pixels.Color(0, 0, 0, 255));
        pixels.changeColorWithTransition(pixels.Color(0, 0, 0, 255), DEFAULT_TRANSITION);
        break;
      }
      manager.setProgram(SET_MANUEL_COLOR);
      break;


  default:
    Serial.print("IR-Data : ");
    Serial.print(data, HEX);
    Serial.println("");
    break;
  }
}