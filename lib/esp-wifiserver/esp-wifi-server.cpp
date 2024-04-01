/**
 * @file esp-wifi-server.cpp
 * @author Aras Taşkıran (aras.taskiran@argeloji.com)
 * @brief
 * @version 0.1
 * @date 2024-03-05
 *
 * @copyright Copyright (c) 2023 Argeloji Mühendislik
 *
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <esp-wifi-server.h>
#include <string.h>

bool ESPGenericWifiServer::_debug{false};
IPAddress ESPGenericWifiServer::_ip{IPAddress()};
IPAddress ESPGenericWifiServer::_netmask{IPAddress()};
IPAddress ESPGenericWifiServer::_gateway{IPAddress()};
IPAddress ESPGenericWifiServer::_dns1{IPAddress()};
IPAddress ESPGenericWifiServer::_dns2{IPAddress()};
char *ESPGenericWifiServer::_token{nullptr};
char *ESPGenericWifiServer::_ssid{nullptr};
char *ESPGenericWifiServer::_psk{nullptr};
uint16_t ESPGenericWifiServer::_port{80};

ESP8266WebServer *ESPGenericWifiServer::server{nullptr};

void ESPGenericWifiServer::setIP(const char *ip)
{
    _ip = toIP(ip);
}

void ESPGenericWifiServer::setNetmask(const char *netmask)
{
    _netmask = toIP(netmask);
}

void ESPGenericWifiServer::setGateway(const char *gateway)
{
    _gateway = toIP(gateway);
}

void ESPGenericWifiServer::setDNS1(const char *dns)
{
    _dns1 = toIP(dns);
}

void ESPGenericWifiServer::setDNS2(const char *dns)
{
    _dns2 = toIP(dns);
}

void ESPGenericWifiServer::setToken(const char *token)
{
    _token = (char *)token;
}

void ESPGenericWifiServer::setDebug(bool debug)
{
    _debug = debug;
}

void ESPGenericWifiServer::setSSID(const char *ssid)
{
    _ssid = (char *)ssid;
}

void ESPGenericWifiServer::setPSK(const char *psk)
{
    _psk = (char *)psk;
}

void ESPGenericWifiServer::connect(uint16_t port)
{
    server = new ESP8266WebServer(port);
    _port = port;
    if (_debug)
    {
        Serial.println();
        Serial.println();
        Serial.print("Connecting to ");
        Serial.println(_ssid);
    }
    // Configures static IP address
    if (!WiFi.config(_ip, _gateway, _netmask, _dns1, _dns2))
    {
        if (_debug)
        {
            Serial.println("STA Failed to configure");
        }
    }
    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid, _psk);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        if (_debug)
        {
            Serial.print(".");
        }
    }

    server->begin();
    if (_debug)
    {
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("Server started");
        Serial.print("Use this URL to connect: ");
        Serial.print("http://");
        Serial.print(WiFi.localIP());
        Serial.println("/");
    }
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
}

bool ESPGenericWifiServer::checkWifi()
{

    return (WiFi.status() == WL_CONNECTED);
}

void ESPGenericWifiServer::addRoute(const Uri &uri, HTTPMethod method, std::function<void(void)> fn)
{
    server->on(uri, method, fn);
}

void ESPGenericWifiServer::check()
{
    server->handleClient();
}

bool ESPGenericWifiServer::checkToken()
{

    if (server->arg("token") != _token)
    {
        server->send(401, "application/json", "{\"success\":false, \"message\":\"permission denied\"}");
        return false;
    }

    return true;
}

IPAddress ESPGenericWifiServer::toIP(const char *ip)
{
    IPAddress x;
    x.fromString(ip);
    return x;
}

const String ESPGenericWifiServer::getArg(const String &s)
{
    return server->arg(s);
}

void ESPGenericWifiServer::exception(const String &s)
{
    server->send(401, "application/json", "{\"success\":false, \"message\":\"" + s + "\"}");
}