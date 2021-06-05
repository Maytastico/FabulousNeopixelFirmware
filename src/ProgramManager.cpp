#include "ProgramManager.h"


Program ProgramManager::getCurrentProgram()
{
    return currentProgram;
}

void ProgramManager::setStore(EpromHandler *storage)
{
    this->storage = storage;
}


void ProgramManager::setProgram(Program newProgram)
{
    currentProgram = newProgram;
    //saves the program status exept it is the program off
    if(newProgram != OFF)
        storage->storeProgrammStatus((int)newProgram);
}