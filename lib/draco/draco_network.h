/**
 * @file draco_network.h
 * @author Aras Taşkıran (aras.taskiran@argeloji.com)
 * @brief DRACO NETWORK LAYER
 * @version 0.1
 * @date 2024-03-05
 *
 * @copyright Copyright (c) 2023 Argeloji Mühendislik
 *
 */
#ifndef DRACO_NETWORK_H
#define DRACO_NETWORK_H
class DracoNetwork
{
public:
    static void setWifi(const char *ssid, const char *psk);
    static void setIPV4(const char *ip, const char *netmask, const char *gateway);
    static void setDNS(const char *primary, const char *secondary);
    static void startWebServer(unsigned short port, const char *auth_token);

protected:
    static bool use_wifi;
};
#endif