#ifndef __SENSOR_BACKEND_H__
#define __SENSOR_BACKEND_H__ 1

class sensor_backend {
  public:
    sensor_backend() {}
    virtual void setupBackend() = 0;
    virtual int getSensorCount() = 0;
    virtual int getDomoticzIndex(int index) = 0;
    virtual void prepareRead() = 0;
    virtual int readSensorInt(int index) = 0;
    virtual float readSensorFloat(int index) = 0;
};

#endif
