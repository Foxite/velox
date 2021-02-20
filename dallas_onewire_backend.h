#ifndef __DALLAS_ONEWIRE_BACKEND_H__
#define __DALLAS_ONEWIRE_BACKEND_H__ 1

#include <OneWire.h>
#include <DallasTemperature.h>
#include "sensor_backend.h"

class dallas_onewire_backend: public sensor_backend {
  public:
    dallas_onewire_backend() { }
    void setupBackend();
    int getSensorCount();
    int getDomoticzIndex(int index);
    void prepareRead();
    int readSensorInt(int index);
    float readSensorFloat(int index);
};

#endif
