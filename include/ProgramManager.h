#ifndef ProgramManager_H_
#define ProgramManager_H_

#include <Arduino.h>
#include <EpromHandler.h>

/**
     * Contains possible light programs/animation that can be played
     */
enum Program
{
  NONE,
  OFF,
  SET_MANUEL_COLOR,
  RAINBOW,
  RANDOM,
  RANDOM_COLOR_FRAME,
  STAR_LIGHT
};

const uint8_t ANIMATION_UPDATE_RATE = 100;

class ProgramManager
{
private:
  

  Program currentProgram = OFF;

  EpromHandler *storage = nullptr;

public:
  /**
     * @brief Construct a new Program Manager object
     * 
     */
  ProgramManager() {}

  /**
 * @brief Sets the Store object
 * 
 * @param storage 
 */
  void setStore(EpromHandler *storage);

  /**
   * @brief Returns the program that was set by the user.
   *        It is used to determine what kind of loop will be executed .
   * 
   * @return Program 
   */
  Program getCurrentProgram();

  /**
   * @brief Sets the porgram that the main loop can fetch to determine
   *        what routine of an instace will be executed.
   * 
   * @param programType 
   */
  void setProgram(Program programType);

};

#endif // ProgramManager_H_