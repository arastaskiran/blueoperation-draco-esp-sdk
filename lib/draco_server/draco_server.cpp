/**
 * @file draco_server.cpp
 * @author Aras Taşkıran (aras.taskiran@argeloji.com)
 * @brief ESP DRACO HTTP SERVER
 * @version 0.1
 * @date 2024-03-05
 *
 * @copyright Copyright (c) 2023 Argeloji Mühendislik
 *
 */

#include <draco_server.h>

unsigned int DracoServer::_current_http_event{DracoServer::HTTPCommands::NOP};
unsigned long DracoServer::_currentStep{0};

void DracoServer::checkServer()
{
    _current_http_event = HTTPCommands::NOP;
    ESPGenericWifiServer::check();
}

void DracoServer::startWifiServer(uint16_t port)
{
    connect(port);
    loadRoutes();
}
void DracoServer::loadRoutes()
{
    addRoute("/turn_on", HTTPMethod::HTTP_POST, openCurtain);
    addRoute("/turn_off", HTTPMethod::HTTP_POST, closeCurtain);
}

void DracoServer::openCurtain()
{
    if (!checkToken())
    {
        return;
    }
    _currentStep = 0;
    _current_http_event = HTTPCommands::CURTAIN_OPEN;
    if (isNumeric(getArg("step_limit")))
    {
        _currentStep = (unsigned long) getArg("step_limit").toInt();
    }
    server->send(200, "application/json", "{\"success\":true, \"message\":\"command processed\"}");
}
void DracoServer::closeCurtain()
{
    if (!checkToken())
    {
        return;
    }
    _currentStep = 0;
    _current_http_event = HTTPCommands::CURTAIN_CLOSE;
    if (isNumeric(getArg("step_limit")))
    {
        _currentStep = (unsigned long) getArg("step_limit").toInt();
    }
    server->send(200, "application/json", "{\"success\":true, \"message\":\"command processed\"}");
}

bool DracoServer::onHttpEvent(unsigned int event)
{
    return _current_http_event == event;
}

unsigned int DracoServer::getCurrentEvent()
{
    return _current_http_event;
}

bool DracoServer::isNumeric(const String &str)
{
    unsigned int stringLength = str.length();

    if (stringLength == 0)
    {
        return false;
    }

    bool seenDecimal = false;

    for (unsigned int i = 0; i < stringLength; ++i)
    {
        if (isDigit(str.charAt(i)))
        {
            continue;
        }

        if (str.charAt(i) == '.')
        {
            if (seenDecimal)
            {
                return false;
            }
            seenDecimal = true;
            continue;
        }
        return false;
    }
    return true;
}

unsigned long DracoServer::getCurrentStep()
{
    return _currentStep;
}