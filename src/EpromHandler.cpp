/**
 * @file EpromHandler.cpp
 * @author MacaroniDamage
 * @brief Saves and accesses the Data of the EEPROM
 * @version 0.2
 * @date 2020-12-16
 * 
 * 
 */

#include <EEPROM.h>
#include "EpromHandler.h"

void EpromHandler::begin(void)
{
  ARGB_Data storedData;

  // load data from EEPROM
  EEPROM.get(0, storedData);

  Serial.println("Stored Data");
  Serial.println(String(storedData.brightness));
  Serial.println(String(storedData.color));
  Serial.println(String(storedData.programStatus));
  Serial.println(String(storedData.prideBanner));
  // EEPROM deleted ?
  if ((0 == storedData.brightness) || (0 == storedData.color) || (0 == storedData.programStatus) || (0 == storedData.prideBanner))
  {
    // EEPROM deleted, write defaults
    storedData.brightness = DEF_BRIGHTNESS;
    storedData.color = DEF_COLOR;
    storedData.programStatus = DEF_DEFAULTPROGRAM;
    storedData.prideBanner = DEF_PRIDEBANNER;
    EEPROM.put(0, storedData);
  }
  // copy data from EEPROM
  this->actData.brightness = storedData.brightness;
  this->actData.color = storedData.color;
  this->actData.programStatus = storedData.programStatus;
  this->actData.prideBanner = storedData.prideBanner;
}

// get loaded light data
void EpromHandler::getLightData(uint8_t *brightness, uint32_t *color, uint8_t *programmStatus, uint8_t *prideBanner) const
{
  *brightness = this->actData.brightness;
  *color = this->actData.color;
  *programmStatus = this->actData.programStatus;
  *prideBanner = this->actData.prideBanner;
}

// get loaded light data
uint32_t EpromHandler::getSavedColor()
{
  return this->actData.color;
}

// get loaded light data
uint8_t EpromHandler::getSavedBrightness()
{
  return this->actData.brightness;
}

uint8_t EpromHandler::getSavedProgram()
{
  return this->actData.programStatus;
}

uint8_t EpromHandler::getPrideBanner()
{
  return this->actData.prideBanner;
}

// store brightness to EEPROM
void EpromHandler::storeBrightness(uint8_t pBrightness, String programName)
{
  if(pBrightness > 10){
    this->actData.brightness = pBrightness;
    EEPROM.put(0, this->actData);
  }else{
    Serial.println("-----------------Attention---------------------");
    Serial.println("Program tried to save a brightness value below");
    Serial.println("Brightness value: "+ String(pBrightness));
    Serial.println("-----------------Debug-Data---------------------");
  }
}

// store color to EEPROM
void EpromHandler::storeColor(uint32_t pColor)
{
  this->actData.color = pColor;
  EEPROM.put(0, this->actData);
}

// store color to EEPROM
void EpromHandler::storeProgrammStatus(uint8_t pProgrammstatus)
{
  this->actData.programStatus = pProgrammstatus;
  EEPROM.put(0, this->actData);
}

// store color to EEPROM
void EpromHandler::storePrideBanner(uint8_t pPrideBanner)
{
  this->actData.prideBanner = pPrideBanner;
  EEPROM.put(0, this->actData);
}