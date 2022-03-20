/**
 * @file IRReceiver.cpp
 * @author MacaroniDamage
 * @brief Summarizes the features
 *        of the IRremote libary
 * @version 0.1
 * @date 2020-12-16
 * 
 * 
 */

#include <IRReceiver.h>

//Declaretes the IRremote Object
IRReceiver::IRReceiver(IRrecv *irRecv)
{
    _pIrRecv = irRecv;
}

//Initializes the IRremote Object
void IRReceiver::begin()
{
    _pIrRecv->enableIRIn();
}

// encodes the ir data if available and 
// return whether data is available or not
bool IRReceiver::isDataReady()
{
    bool isReady = _pIrRecv->decode(&_results);

    if (isReady)
    {
      encodedData = _results.value;
      _pIrRecv->resume();
      return true;
    }
    return false;
}

//Returns encoded data
uint32_t IRReceiver::getEncodedData()
{
    return encodedData;
}