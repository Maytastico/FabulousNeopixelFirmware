/**
 * @file EpromHandler.cpp
 * @author MacaroniDamage
 * @brief Saves and accesses the Data of the EEPROM
 * @version 0.1
 * @date 2020-12-16
 * 
 * 
 */

#include <Arduino.h>
#include "Timer.h"

#ifndef _EEPROM_HANDLER_H_
#define _EEPROM_HANDLER_H_

const uint8_t DEF_BRIGHTNESS = 127;
const uint32_t DEF_COLOR = 255; // Blue
const uint8_t DEF_DEFAULTPROGRAM = 1;

class EpromHandler
{
private:
  struct ARGB_Data
  {
    uint8_t brightness;
    uint32_t color;
    uint8_t programStatus;
  };

  /**
   * @brief Contains the saved light and program status data
   * 
   */
  ARGB_Data actData;


public:
  EpromHandler(){};

  /**
   * @brief Initializes the EEPROM memory area and saves default values
   *        into it if is does not containe any. Also saves the data into this object
   * 
   */
  void begin();

  /**
   * @brief Returns the EEPROM data that is saved inside of this object
   * 
   * @param brightness 
   * @param color 
   * @param programmStatus 
   */
  void getLightData(uint8_t *brightness, uint32_t *color, uint8_t *programmStatus) const;

  /**
   * @brief Return the brightness that is saved inside of this object
   * 
   * @return uint8_t 
   */
  uint8_t getSavedBrightness();

  /**
   * @brief Return the color that is saved inside of this object
   * 
   * @return uint32_t 
   */
  uint32_t getSavedColor();

  /**
 * @brief Return the programm Status that is saved inside of this object
 * 
 * @return uint8_t 
 */
  uint8_t getSavedProgram();

  /**
   * @brief Takes the brightness that was handed over and saves it into the
   *        ARGB_Data structure and save the structure into the EEPROM
   * 
   * @param pBrightness 
   */
  void storeBrightness(uint8_t pBrightness, String programName);

  /**
   * @brief Takes the Color that was handed over and saves it into the
   *        ARGB_Data structure and save the structure into the EEPROM
   * 
   * @param pColor 
   */
  void storeColor(uint32_t pColor);

  /**
   * @brief Takes the program status that was handed over and saves it into the
   *        ARGB_Data structure and save the structure into the EEPROM
   * 
   * @param pProgrammstatus 
   */
  void storeProgrammStatus(uint8_t pProgrammstatus);

};

#endif // _EEPROM_HANDLER_H_
