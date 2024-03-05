/**
 * @file esp-wifi-server.h
 * @author Aras Taşkıran (aras.taskiran@argeloji.com)
 * @brief ESP HTTP Server
 * @version 0.1
 * @date 2024-03-05
 *
 * @copyright Copyright (c) 2023 Argeloji Mühendislik
 *
 */

#include <WiFiServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

class ESPGenericWifiServer
{

public:
    /**
     * @brief Debug mode stter
     *
     * @param debug debug status
     * @return Void
     */
    static void setDebug(bool debug);
    /**
     * @brief Set Server IP Address
     *
     * @param ip ip string
     * @return Void
     */
    static void setIP(const char *ip);
    /**
     * @brief Set Server Netmask Address
     *
     * @param netmask ip string
     * @return Void
     */
    static void setNetmask(const char *netmask);
    /**
     * @brief Set Server Gateway Address
     *
     * @param gateway ip string
     * @return Void
     */
    static void setGateway(const char *gateway);
    /**
     * @brief Set Primary DNS Address
     *
     * @param dns ip string
     * @return Void
     */
    static void setDNS1(const char *dns);
    /**
     * @brief Set Secondery DNS Address
     *
     * @param dns ip string
     * @return Void
     */
    static void setDNS2(const char *dns);
    /**
     * @brief Set Api Token
     *
     * @param token secret keyword
     * @return Void
     */
    static void setToken(const char *token);
    /**
     * @brief Set Wifi SSID
     *
     * @param ssid SSID Name
     * @return Void
     */
    static void setSSID(const char *ssid);
    /**
     * @brief Set Wifi PSK
     *
     * @param ssid PSK Password
     * @return Void
     */
    static void setPSK(const char *psk);
    /**
     * @brief Connect to Wifi
     *
     * @return Void
     */
    static void connect(uint16_t port);
    /**
     * @brief Call continuously within the main loop
     *
     * @return Void
     */
    static void check();
    /**
     * @brief Add Http Route
     * @param uri Url
     * @param method HTTPMethod
     * @param fn action
     *
     * @return Void
     */
    static void addRoute(const Uri &uri, HTTPMethod method, std::function<void(void)> fn);

protected:
    static ESP8266WebServer *server;
    static bool checkToken();
    static void exception(const String &s);
    static const String getArg(const String &s);

private:
    static uint16_t _port;
    static bool _debug;
    static char *_ssid;
    static IPAddress _ip;
    static IPAddress _netmask;
    static IPAddress _gateway;
    static IPAddress _dns1;
    static IPAddress _dns2;
    static char *_token;
    static char *_psk;
    static IPAddress toIP(const char *ip);
};