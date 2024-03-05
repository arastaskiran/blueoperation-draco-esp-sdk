/**
 * @file draco.h
 * @author Aras Taşkıran (aras.taskiran@argeloji.com)
 * @brief
 * @version 0.1
 * @date 2024-03-04
 *
 * @copyright Copyright (c) 2024 Argeloji Mühendislik
 *
 */

#include "draco_item_list.h"
#include <draco_network.h>

class Draco : public DracoNetwork
{
public:
    enum IoType
    {
        NONE = 0,
        DIGITAL_INPUT = 1,
        DIGITAL_OUTPUT = 2,
        ANALOG_INPUT = 3,
        ANALOG_OUTPUT = 4,

    };

    static void setOrigin(const char *origin);
    static void setBlueAuthToken(const char *token);
    static void setBlueDeviceToken(const char *token);
    static void setBlueDeviceID(int device_id);
    /**
     * @brief Add Http Route
     * @param io int
     * @param mode int
     * @param addr int
     * @param type IoType
     * @param inverted bool
     *
     * @return Void
     */
    static void addIO(int io, int mode = 0x2, int addr = 0, unsigned int type = 0, bool inverted=false);
    static void update();
    /**
     * @brief Set Debug Mode
     *
     * @param status Debug status
     * @param baud uart baud rate (defalt 115200)
     * @return Void
     */
    static void debugMode(bool status, unsigned int baud = 115200);
    static bool is_secure;
    static uint8_t fingerprint[20];
    static void setFingerPrint(const uint8_t fp[20]);

    static void setProxy(const char *origin, uint16_t port);
    static const char *getAuthToken() { return _bop_auth_token; }
    static const char *getPortalOrigin() { return _bop_origin; }
    static const char *getProxyOrigin() { return proxy_origin; }
    static const char *getDeviceToken() { return _bop_device_token; }
    static const char *getProxyToken() { return _proxy_token; }
    static uint16_t getProxyPort() { return proxy_port; }
    static int getDeviceID() { return _device_id; }
    static bool hasProxy() { return use_proxy; }
    static bool isDebugMode() { return _debug_mode; }
    static bool isSSL() { return use_ssl; }
    static void useSSL(bool status);

protected:
    static const char *_bop_auth_token;
    static const char *_bop_device_token;
    static const char *_proxy_token;
    static const char *_bop_origin;
    static const char *proxy_origin;
    static bool use_proxy;
    static bool use_ssl;
    static uint16_t proxy_port;
    static int _device_id;
    static DracoItemList *io_list;
    /**
     * @brief Controls hardware activity events
     *
     * @param c Log Message
     * @return Void
     */
    static void log(const char c[]);

private:
    /**
     * @brief Check new http commands
     *
     * @return bool (true: interupt, false:continue)
     */
    static bool checkHTTP();
    static bool _debug_mode;
    static void checkIO();
};