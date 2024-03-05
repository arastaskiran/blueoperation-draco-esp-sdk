/**
 * @file draco_server.h
 * @author Aras Taşkıran (aras.taskiran@argeloji.com)
 * @brief ESP DRACO HTTP SERVER
 * @version 0.1
 * @date 2024-03-05
 *
 * @copyright Copyright (c) 2023 Argeloji Mühendislik
 *
 */

#include <esp-wifi-server.h>

class DracoServer : public ESPGenericWifiServer
{

public:
    /**
     * @brief HTTP CONTROL COMMANDS
     *
     */
    enum HTTPCommands
    {
        NOP = 0,
        CURTAIN_OPEN = 1,
        CURTAIN_CLOSE = 2,

    };

    /**
     * @brief Call continuously within the main loop
     *
     * @return Void
     */
    static void checkServer();
    /**
     * @brief Checks the event sent via API call
     *
     * @param event Event to check
     * @return Returns true if the specified event is active
     */
    static bool onHttpEvent(unsigned int event);
    /**
     * @brief Connect to Wifi
     *
     * @return Void
     */
    static void startWifiServer(uint16_t port);
    /**
     * @brief Get Current HTTP Event
     *
     * @return current_event
     */
    static unsigned int getCurrentEvent();

    static unsigned long getCurrentStep();

private:
    static unsigned int _current_http_event;
    static bool checkCommand(String &request);
    static void openCurtain();
    static void closeCurtain();
    static void loadRoutes();
    static bool isNumeric(const String &str);
    static unsigned long _currentStep;
};