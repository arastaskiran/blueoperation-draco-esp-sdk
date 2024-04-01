/**
 * @file draco_network.cpp
 * @author Aras Taşkıran (aras.taskiran@argeloji.com)
 * @brief DRACO NETWORK LAYER
 * @version 0.1
 * @date 2024-03-05
 *
 * @copyright Copyright (c) 2023 Argeloji Mühendislik
 *
 */

#include <draco_network.h>
#include "draco_server.h"

bool DracoNetwork::use_wifi{false};

void DracoNetwork::setWifi(const char *ssid, const char *psk)
{
    DracoServer::setSSID(ssid);
    DracoServer::setPSK(psk);
}
void DracoNetwork::setIPV4(const char *ip, const char *netmask, const char *gateway)
{
    DracoServer::setIP(ip);
    DracoServer::setNetmask(netmask);
    DracoServer::setGateway(gateway);
}
void DracoNetwork::setDNS(const char *primary, const char *secondary)
{
    DracoServer::setDNS1(primary);
    DracoServer::setDNS2(secondary);
}
void DracoNetwork::startWebServer(unsigned short port, const char *auth_token)
{
    DracoServer::setToken(auth_token);
    DracoServer::startWifiServer(port);
    use_wifi = true;
}