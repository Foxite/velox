#ifndef __DHT_BACKEN_H__
#define __DHT_BACKEN_H__ 1

#include <DHT.h>
#include "sensor_backend.h"

class dht_backend: public sensor_backend {
  public:
    dht_backend() { }
    void setupBackend();
    int getSensorCount();
    int getDomoticzIndex(int index);
    void prepareRead();
    int readSensorInt(int index);
    float readSensorFloat(int index);
};

#endif
