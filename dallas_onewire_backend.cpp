#include "dallas_onewire_backend.h"

#define ONE_WIRE_BUS 0
#define SENSOR_COUNT 1

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

inline uint64_t to_uint64_t(DeviceAddress address) {
  return *((uint64_t*) address);
}

uint8_t toLabelId(uint64_t addressId) {
  /* On labels:
     S00 = 282310A83320019D
     S01 = 2823907A33200150
     S02 = 285533823320016A
     S03 = 28A37C79332001C9
     S04 = 28BC42BA3220018A
     S05 = 28CCEDE03220018D
     S06 = 28D27928332001E3
     S07 = 28E54F8A3320013D
     S08 = 28F1DE0233200105
     S09 = 28F366A2332001B3

     Bytes reversed:
     S00 = 0x9D012033A8102328
     S01 = 0x500120337A902328
     S02 = 0x6A01203382335528
     S03 = 0xC9012033797CA328
     S04 = 0x8A012032BA42BC28
     S05 = 0x8D012032E0EDCC28
     S06 = 0xE30120332879D228
     S07 = 0x3D0120338A4FE528
     S08 = 0x0501203302DEF128
     S09 = 0xB3012033A266F328
  */
  switch (addressId) {
    case 0x9D012033A8102328:
      return 0;
    case 0x500120337A902328:
      return 1;
    case 0x6A01203382335528:
      return 2;
    case 0xC9012033797CA328:
      return 3;
    case 0x8A012032BA42BC28:
      return 4;
    case 0x8D012032E0EDCC28:
      return 5;
    case 0xE30120332879D228:
      return 6;
    case 0x3D0120338A4FE528:
      return 7;
    case 0x0501203302DEF128:
      return 8;
    case 0xB3012033A266F328:
      return 9;
  }
}

void dallas_onewire_backend::setupBackend() { }

int dallas_onewire_backend::getSensorCount() {
  return SENSOR_COUNT;
}

int dallas_onewire_backend::getDomoticzIndex(int index) {
  return index + 36;
}

void dallas_onewire_backend::prepareRead() {
  sensors.requestTemperatures(); // Send the command to get temperatures
}

int dallas_onewire_backend::readSensorInt(int index) {
  return 0;
}

float dallas_onewire_backend::readSensorFloat(int index) {
  // Search the wire for address
  DeviceAddress address;
  if (sensors.getAddress(address, index)) {
    return sensors.getTempC(address);
  } else {
    Serial.write("Couldn't get sensor address of index ");
    Serial.println(index);
  }
}
