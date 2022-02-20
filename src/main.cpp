#include <Arduino.h>
#include <HX711.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 18;
const int LOADCELL_SCK_PIN = 19;

HX711 scale;

void setup() {
  Serial.begin(500000);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(409600);
  scale.tare();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (scale.wait_ready_timeout(20)) {
    float reading = scale.get_units(1);
    Serial.print(millis());
    Serial.print("\t");
    Serial.println(reading);
  }
}