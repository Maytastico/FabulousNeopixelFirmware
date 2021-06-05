#ifndef IRRECEIVER_H_
#define IRRECEIVER_H_

#include <Arduino.h>
#include <IRremote.h>

class IRReceiver
{
private:
  /**
   * @brief Containe the not encoded data 
   *        that will be encoded in isDataReady
   * 
   */
  decode_results _results;

  /**
   * @brief Contains the encoded data form the infrared remote
   * 
   */
  uint32_t encodedData;

  /**
   * @brief Pointer object of the IRremote Libary
   * 
   */
  IRrecv *_pIrRecv;

public:
  IRReceiver(IRrecv *irRecv);

  /**
   * @brief Initializes the IRremote Libary
   * 
   */
  void begin();

  /**
   * @brief Calls the IRremote Libary and checks
   *        whether new data arrived
   * 
   * @return true -> new data arrived
   * @return false -> no data was received
   */
  bool isDataReady();

  /**
   * @brief Returns the received data from infrared remote
   * 
   * @return uint32_t -> encoded data
   */
  uint32_t getEncodedData();
};

#endif // IRRECEIVER_H_