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
#include <draco_io_service.h>

unsigned int DracoServer::_current_http_event{DracoServer::HTTPCommands::NOP};
unsigned long DracoServer::_currentStep{0};

void DracoServer::checkServer()
{
    _current_http_event = HTTPCommands::NOP;
    if (!ESPGenericWifiServer::checkWifi())
    {
        return;
    }
    ESPGenericWifiServer::check();
}

void DracoServer::startWifiServer(uint16_t port)
{
    connect(port);
    loadRoutes();
}
void DracoServer::loadRoutes()
{
    addRoute("/set_value", HTTPMethod::HTTP_POST, setDacoValue);
}

void DracoServer::setDacoValue()
{
    if (!checkToken())
    {
        return;
    }

    if (!isNumeric(getArg("value")) || !isNumeric(getArg("point")))
    {
        server->send(422, "application/json", "{\"success\":false, \"message\":\"value and point must be integer\"}");
        return;
    }
    int point = (int)getArg("point").toInt();
    int value = (int)getArg("value").toInt();
    bool found = false;

    struct IONode *ptr;
    ptr = DracoIoService::getIoList()->head;
    while (ptr != NULL)
    {
        if (ptr->data->isAddrEQ(point))
        {
            ptr->data->setVal(value);
            found = true;
            break;
        }

        ptr = ptr->next;
    }

    if (!found)
    {
        server->send(404, "application/json", "{\"success\":false, \"message\":\"io object not found\"}");
        return;
    }
    server->send(200, "application/json", "{\"success\":true, \"message\":\"io_value_changed\"}");
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