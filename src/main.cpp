#include <Arduino.h>
#include <draco.h>

void setup()
{
  /*
  EXAMPLE SETUP
  */
  Draco::debugMode(false);
  Draco::addIO(14, INPUT_PULLUP, 101, Draco::IoType::DIGITAL_INPUT);
  Draco::addIO(12, INPUT_PULLUP, 102, Draco::IoType::DIGITAL_INPUT);
  Draco::addIO(13, INPUT_PULLUP, 103, Draco::IoType::DIGITAL_INPUT);
  Draco::addIO(0, INPUT_PULLUP, 104, Draco::IoType::DIGITAL_INPUT);
  Draco::addIO(4, INPUT_PULLUP, 105, Draco::IoType::DIGITAL_INPUT);
  Draco::addIO(5, INPUT_PULLUP, 106, Draco::IoType::DIGITAL_INPUT);
  Draco::addIO(1, INPUT_PULLUP, 107, Draco::IoType::DIGITAL_INPUT);

  Draco::setBlueDeviceID(55); // DRACO DEVICE ID
  Draco::setBlueAuthToken("Bearer [SECRET DRACO AUTH TOKEN]");
  Draco::setBlueDeviceToken("[SECRET DRACO DEVICE TOKEN]");
  Draco::setOrigin("https://portal.blueoperation.io");
  Draco::useSSL(true);
  Draco::setWifi("WIFI SSID", "WIFI PSK");
  Draco::setIPV4("192.168.1.169", "255.255.255.0", "192.168.1.1");
  Draco::setDNS("8.8.8.8", "8.8.4.4");
  // START ESP SERVER PORT 80 WITH TOKEN
  Draco::startWebServer(80, "[SECRET ESP DEVICE TOKEN or SECRET DRACO DEVICE TOKEN]");
}

void loop()
{
  Draco::update();
}
