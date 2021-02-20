This is an Arduino program that takes in sensor data from an arbitrary source and published it to an MQTT topic. Currently, this is designed to go to Domoticz, but it can easily be adapted for another receiver.

Currently, sensor backends for Dallas/OneWire and DHT are supported.

See `config.h.example` for configuration options. Also make sure to read through the chosen backend and ensure that specific constants are correct.
