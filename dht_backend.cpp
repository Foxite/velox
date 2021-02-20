#include "dht_backend.h"

#define DHTPIN 2 // Digital pin connected to the DHT sensor
#define DHTTYPE DHT21 // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

void dht_backend::setupBackend() {
  dht.begin();
}

int dht_backend::getSensorCount() {
  return 2;
}

int dht_backend::getDomoticzIndex(int index) {
  return index + 36;
}

void dht_backend::prepareRead() { }

int dht_backend::readSensorInt(int index) {
  if (index == 0) {
    return 0;
  }  else if (index == 1) {
    float ret = dht.readHumidity();
    if (isnan(ret)) {
      return -1;
    } else {
      return (int) ret;
    }
  }
}

float dht_backend::readSensorFloat(int index) {
  if (index == 1) {
    return 0;
  } else if (index == 0) {
    float ret = dht.readTemperature();
    if (isnan(ret)) {
      return -273.15;
    } else {
      return ret;
    }
  }
}
