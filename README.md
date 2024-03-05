**BLUEOPERATION DRACO-ESP SDK**

Blueoperation Draco cihazlarına ESP üzerinden IO eklemenize yarar.

```plaintext

        +-----------------------+
        | O      | USB |      O |
        |        -------        |
  3.3V  | [ ]               [ ] | VIN
   GND  | [ ]               [ ] | GND
 GPIO1  | [ ]               [ ] | RST
 GPIO3  | [ ]               [ ] | EN 
GPIO15  | [ ]               [ ] | 3.3V
GPIO13  | [ ]               [ ] | GND
GPIO12  | [ ]               [ ] | SCLK
GPIO14  | [ ]  ___________  [ ] | MISO
   GND  | [ ] |           | [ ] | CS 
  3.3V  | [ ] |           | [ ] | MOSI 
 GPIO2  | [ ] |           | [ ] | GPIO9 
 GPIO0  | [ ] |           | [ ] | GPIO10
 GPIO4  | [ ] |           | [ ] | RESERVED
 GPIO5  | [ ] |           | [ ] | RESERVED
GPIO16  | [ ] |___________| [ ] | ADC0
        |                       |
        |  |  |  ____  ____  |  |
        |  |  |  |  |  |  |  |  |
        |  |__|__|  |__|  |__|  |
        | O                   O |
        +-----------------------+

INTERNAL PULLUP PINS:      INTERNAL PULLDOWN PINS:
GPIO14                     Don't use it if you don't have to
GPIO12                     GPIO16
GPIO13
GPIO0
GPIO4
GPIO5
GPI01

Don't use it if you don't have to
-------------------------------
GPIO2
GPIO9
GPI1O
GPIO3

```

**Örnek Kullanım**

```cpp
#include <draco.h>
void setup()
{

  Draco::debugMode(true, 11520);
  Draco::addIO(16, INPUT_PULLUP, 12, Draco::IoType::DIGITAL_INPUT);
  Draco::setBlueDeviceID(54);
  Draco::setBlueAuthToken("Bearer SECRET_BEARER TOKEN");
  Draco::setBlueDeviceToken("SECRET_DEVICE_TOKEN"); 
  Draco::setOrigin("https://portal.blueoperation.io");
  Draco::useSSL(true);
  Draco::setWifi("ARGELOJI_SSID", "SECRET_WIFI_PSK");
  Draco::setIPV4("192.168.1.169", "255.255.255.0", "192.168.1.1");
  Draco::setDNS("8.8.8.8", "8.8.4.4");
  Draco::startWebServer(80, "SECRET_ESP_TOKEN");
}

void loop()
{
  Draco::update();
}
```

**IO EKLEME**

---

Modüle IO noktası ekleme için `Draco::addIO` isimli methodu kullanmalısınız.

```cpp
    /**
     * @brief Add Draco IO
     * @param io int
     * @param mode int
     * @param addr int
     * @param type IoType
     * @param inverted bool
     *
     * @return Void
     */
    static void addIO(int io, int mode = 0x2, int addr = 0, unsigned int type = 0, bool inverted=false);
```

**Method Parametreleri**

<table>
<tbody>
    <tr><td>parametre</td><td>açıklama</td></tr>
    <tr><td>io</td><td>ESP üzerindeki GPIO numarasını yazınız</td></tr>    
    <tr><td>mode</td><td>IO modunu yazınız (INPUT_PULLUP, INPUT, OUTPUT)</td></tr>
    <tr><td>addr</td><td>Blueoperation draco i/o daki POINT isimli numara</td></tr>
    <tr><td>type</td><td>Blueoperation IO tipi (Aşağıda IoType dökümanına bakınız)</td></tr>
    <tr><td>inverted</td><td>Nokta terslenecek mi? (false: Terslenmeyecek, true: Treslenecek, default: false)</td></tr>
</tbody></table>


**IO Types**

---

ESP noktasının bluoperation üzerindeki karşılığı.

```cpp
    enum IoType
    {
        NONE = 0,
        DIGITAL_INPUT = 1,
        DIGITAL_OUTPUT = 2,
        ANALOG_INPUT = 3,
        ANALOG_OUTPUT = 4,

    };
```


**Debug Mode**

---

Seri Port Üzerinden hata ayıklaması yapmanızı sağlar varsayılan olarak kapalıdır. Canlı kullanımda kapalı olarak tutunuz çünkü çalışma performansını dramatik olarak etkiler.


```cpp

/**
* @brief Set Debug Mode
*
* @param status Debug status
* @param baud uart baud rate (defalt 115200)
* @return Void
*/
static void debugMode(bool status, unsigned int baud = 115200);
```


**SSL Modu**

---

Blueoperation Portalı SSL kullanıyorsa mutlaka aşağıdaki yapılandırmayı yapınız.

```cpp

Draco::useSSL(true);

```

SSL sertifikasının belirli bir FINGERPRINT değerinde olmasını denetlemek için aşağıdaki yapılandırmayı yapabilirsiniz.

```cpp
const uint8_t fingerprint[20] = {0x27, 0x30, 0xE7, 0x80, 0x9B, 0x9E, 0x16, 0x1F, 0xAE, 0x97, 0xD0, 0xDD, 0x55, 0x84, 0xAC, 0x61, 0xC4, 0xCE, 0xBE, 0xEA};

void setup()
{
    Draco::setFingerPrint(fingerprint);
}

```