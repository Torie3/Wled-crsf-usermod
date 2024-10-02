#pragma once

#include "wled.h"
#include "CRSFforArduino.hpp"

/*CRSFforArduino *crsf = nullptr;
int rcChannelCount = crsfProtocol::RC_CHANNEL_COUNT;
const char *rcChannelNames[] = {
    "A", "E", "T", "R", "Aux1", "Aux2", "Aux3", "Aux4",
    "Aux5", "Aux6", "Aux7", "Aux8", "Aux9", "Aux10", "Aux11", "Aux12"};

int channel11Value = 0; // Variable to store the value of channel 10

void onReceiveRcChannels(serialReceiverLayer::rcChannels_t *rcChannels);

class crsfUsermod : public Usermod
{
public:
  void userSetup()
  {
    pinMode(13, OUTPUT);
    crsf = new CRSFforArduino();
    if (!crsf->begin())
    {
      crsf->end();
      delete crsf;
      crsf = nullptr;
      rcChannelCount = rcChannelCount > crsfProtocol::RC_CHANNEL_COUNT ? crsfProtocol::RC_CHANNEL_COUNT : rcChannelCount;
      
      // Use the static callback function
      crsf->setRcChannelsCallback(crsfUsermod::onReceiveRcChannels);
    }
    
  }

  void userLoop()
  {
    crsf->update();
    DEBUG_PRINTLN("Working");
    digitalWrite(13, HIGH);
    
  }

  // Make this function static so it can be used as a callback
  static void onReceiveRcChannels(serialReceiverLayer::rcChannels_t *rcChannels)
  {
    if (rcChannels->failsafe == false)
    {
       //Print RC channels every 100 ms. 
      unsigned long thisTime = millis();
      static unsigned long lastTime = millis();

      //Compensate for millis() overflow. 
      if (thisTime < lastTime)
      {
        lastTime = thisTime;
      }

      if (thisTime - lastTime >= 10)
      {
        lastTime = thisTime; // Update last time for the next interval

        // Store the value of channel 10 in the global variable
        channel11Value = crsf->rcToUs(crsf->getChannel(11));
      }
    }
  }
};
*/