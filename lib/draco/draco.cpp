/**
 * @file draco.cpp
 * @author Aras Taşkıran (aras.taskiran@argeloji.com)
 * @brief
 * @version 0.1
 * @date 2024-03-04
 *
 * @copyright Copyright (c) 2024 Argeloji Mühendislik
 *
 */
#include "draco.h"
#include "draco_item_list.h"
#include "draco_item.h"
#include <string.h>
#include <Arduino.h>
#include <draco_server.h>

DracoItemList *Draco::io_list{new DracoItemList()};
const char *Draco::_bop_origin{nullptr};
const char *Draco::_bop_auth_token{nullptr};
const char *Draco::_bop_device_token{nullptr};
int Draco::_device_id{0};
bool Draco::_debug_mode{true};
bool Draco::is_secure{false};
uint8_t Draco::fingerprint[20]{0};
uint16_t Draco::proxy_port{0};
bool Draco::use_proxy{false};
bool Draco::use_ssl{false};

void Draco::debugMode(bool status, unsigned int baud)
{
    _debug_mode = status;
    if (status)
    {

        Serial.begin(baud);
        ESPGenericWifiServer::setDebug(true);
        log("Debug Mode Open");
    }
}

void Draco::setFingerPrint(const uint8_t fp[20])
{
    is_secure = true;
    memcpy_P(fingerprint, fp, 20);
}

void Draco::log(const char c[])
{
    if (!_debug_mode)
    {
        return;
    }
    Serial.println(c);
}

void Draco::setOrigin(const char *origin)
{
    _bop_origin = origin;
}

void Draco::setBlueAuthToken(const char *token)
{
    _bop_auth_token = token;
}

void Draco::setBlueDeviceToken(const char *token)
{
    _bop_device_token = token;
}

void Draco::setBlueDeviceID(int device_id)
{
    _device_id = device_id;
}

void Draco::addIO(int io, int mode, int addr, unsigned int type, bool inverted)
{
    io_list->insert(new DracoItem(io, mode, addr, type, inverted));
}

void Draco::setProxy(const char *origin, uint16_t port)
{
    proxy_origin = origin;
    proxy_port = port;
    use_proxy = true;
}

bool Draco::checkHTTP()
{
    if (!use_wifi)
    {
        return false;
    }
    DracoServer::checkServer();
    return !DracoServer::onHttpEvent(DracoServer::HTTPCommands::NOP);
}

void Draco::useSSL(bool status)
{
    use_ssl = status;
}

void Draco::update()
{
    if (Draco::checkHTTP())
    {

        return;
    }
    checkIO();
}

void Draco::checkIO()
{
    struct IONode *ptr;
    ptr = io_list->head;
    while (ptr != NULL)
    {
        ptr->data->check();
        ptr = ptr->next;
    }
}
