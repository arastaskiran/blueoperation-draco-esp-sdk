#ifndef DEVICE_TYPE_H
#define DEVICE_TYPE_H
class DeviceType
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
};
#endif