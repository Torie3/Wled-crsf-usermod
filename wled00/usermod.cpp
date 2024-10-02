#include "wled.h"
#include "CRSFforArduino.hpp"
/*
 * This v1 usermod file allows you to add own functionality to WLED more easily
 * See: https://github.com/Aircoookie/WLED/wiki/Add-own-functionality
 * EEPROM bytes 2750+ are reserved for your custom use case. (if you extend #define EEPSIZE in const.h)
 * If you just need 8 bytes, use 2551-2559 (you do not need to increase EEPSIZE)
 *
 * Consider the v2 usermod API if you need a more advanced feature set!
 */

//Use userVar0 and userVar1 (API calls &U0=,&U1=, uint16_t)
CRSFforArduino *crsf = nullptr;
int rcChannelCount = crsfProtocol::RC_CHANNEL_COUNT;
const char *rcChannelNames[] = {
    "A", "E", "T", "R", "Aux1", "Aux2", "Aux3", "Aux4",
    "Aux5", "Aux6", "Aux7", "Aux8", "Aux9", "Aux10", "Aux11", "Aux12"};

int channel11Value = 0; // Variable to store the value of channel 10

void onReceiveRcChannels(serialReceiverLayer::rcChannels_t *rcChannels);

//gets called once at boot. Do all initialization that doesn't depend on network here
void userSetup()
{
    crsf = new CRSFforArduino();
    if (!crsf->begin())
    {
      crsf->end();
      delete crsf;
      crsf = nullptr;
      rcChannelCount = rcChannelCount > crsfProtocol::RC_CHANNEL_COUNT ? crsfProtocol::RC_CHANNEL_COUNT : rcChannelCount;
      
      // Use the static callback function
      crsf->setRcChannelsCallback(onReceiveRcChannels);
    }
}

//gets called every time WiFi is (re-)connected. Initialize own network interfaces here
void userConnected()
{

}

//loop. You can use "if (WLED_CONNECTED)" to check for successful connection
void userLoop()
{
    crsf->update();
}

void onReceiveRcChannels(serialReceiverLayer::rcChannels_t *rcChannels)
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
