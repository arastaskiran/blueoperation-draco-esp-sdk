/**
 * @file draco_item.cpp
 * @author Aras Taşkıran (aras.taskiran@argeloji.com)
 * @brief
 * @version 0.1
 * @date 2024-03-04
 *
 * @copyright Copyright (c) 2024 Argeloji Mühendislik
 *
 */
#include "draco_item.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include "device_type.h"
#include "draco.h"

DracoItem::DracoItem(int io, int mode, int addr, unsigned int type, bool inverted, bool feed_back)
{
    this->io = io;
    this->mode = mode;
    this->addr = addr;
    this->type = type;
    this->value = -1;
    this->is_inverted = inverted;
    this->need_feedback_output = feed_back;
    this->setup();
}

void DracoItem::setup()
{
    switch (type)
    {
    case DeviceType::IoType::DIGITAL_INPUT:
        pinMode(this->io, this->mode);
        break;
    case DeviceType::IoType::DIGITAL_OUTPUT:
        pinMode(this->io, OUTPUT);
        digitalWrite(this->io, (this->is_inverted) ? HIGH : LOW);
        break;
    case DeviceType::IoType::ANALOG_OUTPUT:
        pinMode(this->io, OUTPUT);
        break;

    default:

        break;
    }
}

void DracoItem::check()
{
    if (digitalRead(this->io) == this->value)
    {
        return;
    }
    this->value = digitalRead(this->io);

    send();
}

bool DracoItem::isAddrEQ(int addr)
{
    return this->addr == addr;
}

void DracoItem::send()
{
    if ((WiFi.status() != WL_CONNECTED) || !this->need_feedback_output)
    {

        return;
    }

    HTTPClient https = getClient();
    https.setUserAgent("BLUEOPERATION-IOT-DEVICE");

    buildHeader(https);
    int httpCode = https.POST(buildBody());

    if (httpCode <= 0)
    {

        https.end();
        return;
    }

    // if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
    // {

    //         String payload = https.getString();
    //         Serial.println(payload);

    // }

    https.end();
}

void DracoItem::setSecurity(BearSSL::WiFiClientSecure &client)
{

    if (Draco::is_secure)
    {
        client.setFingerprint(Draco::fingerprint);
        return;
    }

    client.setInsecure();
}

void DracoItem::buildHeader(HTTPClient &http)
{
    http.addHeader("Content-Type", "application/json");
    http.addHeader("User-Agent", "BLUEOPERATION-IOT-DEVICE");
    http.addHeader("hardware", "draco");
    if (Draco::hasProxy())
    {
        // TODO:PROXY KULLANIMI HENÜZ YAZILMADI
        return;
    }

    http.addHeader("Authorization", Draco::getAuthToken());
}

void DracoItem::setVal(int val)
{
    if (type == DeviceType::IoType::DIGITAL_INPUT || type == DeviceType::IoType::ANALOG_INPUT)
    {
        return;
    }
    if (type == DeviceType::IoType::DIGITAL_OUTPUT)
    {
        setDigitalOut(val);
        return;
    }
    setAnalogOut(val);
}

void DracoItem::setDigitalOut(int val)
{
    value = val;
    if (is_inverted)
    {

        digitalWrite(this->io, (val == 1) ? LOW : HIGH);
        this->send();
        return;
    }
    digitalWrite(this->io, (val == 1) ? HIGH : LOW);
    this->send();
    return;
}
void DracoItem::setAnalogOut(int val)
{
    value = val;
    analogWrite(this->io, val);
    this->send();
}

String DracoItem::getEP()
{
    if (Draco::hasProxy())
    {
        // TODO:PROXY KULLANIMI HENÜZ YAZILMADI
        return "";
    }
    return Draco::getPortalOrigin() + String("/api/v1/dracodevice/setvalue");
}

String DracoItem::buildBody()
{
    JsonDocument doc;
    doc["ref"] = "ESPDRACO";
    doc["device_token"] = Draco::getDeviceToken();
    doc["device_id"] = Draco::getDeviceID();
    doc["data"]["addr"] = 0;
    doc["data"]["name"] = "POINT";
    doc["data"]["points"] = addr;

    doc["data"]["value"] = getValue();
    doc["data"]["hardware"] = getHardware();
    doc["data"]["type"] = getType();
    doc["data"]["is_inverted"] = is_inverted;
    doc["data"]["flag"] = 0;
    String output;
    serializeJson(doc, output);
    return output;
}

HTTPClient DracoItem::getClient()
{

    HTTPClient https;
    if (Draco::isSSL())
    {

        std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
        setSecurity(*client);
        if (!https.begin(*client, getEP()))
        {
            if (Draco::isDebugMode())
            {
                Serial.printf("[HTTP] Unable to connect\n");
            }
        }
        return https;
    }
    std::unique_ptr<WiFiClient> client(new WiFiClient);
    if (!https.begin(*client, getEP()))
    {
        if (Draco::isDebugMode())
        {
            Serial.printf("[HTTP] Unable to connect\n");
        }
    }

    return https;
}

int DracoItem::getValue()
{
    if (type == DeviceType::IoType::DIGITAL_INPUT)
    {
        return getDIValue();
    }
    if (type == DeviceType::IoType::ANALOG_INPUT)
    {
        return analogRead(this->io);
    }

    return value;
}

int DracoItem::getDIValue()
{
    if (mode == 0x02)
    {
        return getPullUPDIValue();
    }
    return (is_inverted) ? invertDigitalValue(value) : value;
}

int DracoItem::getPullUPDIValue()
{
    int v = value == 1 ? 0 : 1;
    return (is_inverted) ? invertDigitalValue(v) : v;
}

int DracoItem::invertDigitalValue(int v)
{
    return v == 1 ? 0 : 1;
}

String DracoItem::getHardware()
{
    String v = "";
    switch (type)
    {
    case DeviceType::IoType::DIGITAL_INPUT:
        v = "Mod8DI";
        break;
    case DeviceType::IoType::DIGITAL_OUTPUT:
        v = "Mod8KO";
        break;
    case DeviceType::IoType::ANALOG_INPUT:
        v = "Mod8AI";
        break;
    case DeviceType::IoType::ANALOG_OUTPUT:
        v = "Mod2AO";
        break;

    default:
        v = "";
        break;
    }
    return v;
}
String DracoItem::getType()
{
    String v = "";
    switch (type)
    {
    case DeviceType::IoType::DIGITAL_INPUT:
        v = "digitalinputs";
        break;
    case DeviceType::IoType::DIGITAL_OUTPUT:
        v = "digitaloutputs";
        break;
    case DeviceType::IoType::ANALOG_INPUT:
        v = "analoginputs";
        break;
    case DeviceType::IoType::ANALOG_OUTPUT:
        v = "analogoutputs";
        break;

    default:
        v = "";
        break;
    }
    return v;
}
