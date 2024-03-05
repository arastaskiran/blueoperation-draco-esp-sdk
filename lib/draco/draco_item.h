/**
 * @file draco_item.h
 * @author Aras Taşkıran (aras.taskiran@argeloji.com)
 * @brief
 * @version 0.1
 * @date 2024-03-04
 *
 * @copyright Copyright (c) 2024 Argeloji Mühendislik
 *
 */
#ifndef DRACO_ITEM
#define DRACO_ITEM
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266HTTPClient.h>

class DracoItem
{
public:
    DracoItem(int io, int mode = 0x2, int addr = 0, unsigned int type = 0, bool inverted = false);
    void check();

private:
    int io;
    int mode;
    int addr;
    int value;
    bool is_inverted;
    unsigned int type;
    void setup();
    void send();
    void setSecurity(BearSSL::WiFiClientSecure &client);
    void buildHeader(HTTPClient &http);
    String buildBody();
    String getEP();
    int getValue();
    String getHardware();
    String getType();
    HTTPClient getClient();
    int getDIValue();
    int getPullUPDIValue();
    int invertDigitalValue(int v);
};
#endif