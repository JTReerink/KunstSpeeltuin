#define THINGER_SERIAL_DEBUG

// Requires WifiManager from Library Manager or https://github.com/tzapu/WiFiManager
#include <ThingerWebConfig.h>

ThingerWebConfig thing;

void setup() {
  // open serial for debugging
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["led"] << digitalPin(LED_BUILTIN);

  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> outputValue(millis());
}

void loop() {
  thing.handle();
}
