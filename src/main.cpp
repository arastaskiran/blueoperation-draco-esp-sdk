#include <Arduino.h>
#include <draco.h>
#include <device_type.h>

void setup()
{

  Draco::debugMode(false);
  Draco::addIO(16, OUTPUT, 4, DeviceType::IoType::DIGITAL_OUTPUT, true, false);
  Draco::addIO(5, OUTPUT, 5, DeviceType::IoType::DIGITAL_OUTPUT, true, false);

  // Draco::addIO(14, INPUT_PULLUP, 101, DeviceType::IoType::DIGITAL_INPUT);
  // Draco::addIO(12, INPUT_PULLUP, 102, DeviceType::IoType::DIGITAL_INPUT);
  // Draco::addIO(13, INPUT_PULLUP, 103, DeviceType::IoType::DIGITAL_INPUT);
  // Draco::addIO(0, INPUT_PULLUP, 104, DeviceType::IoType::DIGITAL_INPUT);
  // Draco::addIO(4, INPUT_PULLUP, 105, DeviceType::IoType::DIGITAL_INPUT);
  // Draco::addIO(5, INPUT_PULLUP, 106, DeviceType::IoType::DIGITAL_INPUT);
  // Draco::addIO(1, INPUT_PULLUP, 107, DeviceType::IoType::DIGITAL_INPUT);
  // Draco::addIO(16, INPUT_PULLDOWN_16, 108, DeviceType::IoType::DIGITAL_INPUT);
  Draco::setBlueDeviceID(33);
  Draco::setBlueAuthToken("SECRET BEARER TOKEN");
  Draco::setBlueDeviceToken("SECRET DEVICE TOKEN");
  Draco::setOrigin("https://portal.blueoperation.io");
  Draco::useSSL(true);
  Draco::setWifi("WIFI_SSID", "WIFI_PSK");
  Draco::setIPV4("192.168.1.170", "255.255.255.0", "192.168.1.1");
  Draco::setDNS("8.8.8.8", "8.8.4.4");
  Draco::startWebServer(80, "SECRET DEVICE TOKEN");
}

void loop()
{
  Draco::update();
}
