#include <Arduino.h>
#include <HX711.h>
#include "C610Bus.h"

C610Bus<CAN2> bus; // Initialization. Templated to either use CAN1 or CAN2.
long ts_last_command = 0; // Timestamp of last command in microseconds

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 18;
const int LOADCELL_SCK_PIN = 19;

HX711 scale;
const int kPrecision = 4;

const float kPositionGain = 4000;
const float kVelocityGain = 200;

void setup() {
  Serial.begin(500000);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(409600);
  scale.tare();
}

void loop() {
  bus.PollCAN();

  long now = micros();
  if (now - ts_last_command >= 2000) {
    float m0_pos = bus.Get(0).Position();
    float m0_vel = bus.Get(0).Velocity();

    float m0_target = 2 * sin(millis() / 1000.0 * 10.0);
    float m0_command = kPositionGain * (m0_target - m0_pos) + kVelocityGain * (0.0 - m0_vel);
    bus.CommandTorques(m0_command, 0, 0, 0, C610Subbus::kOneToFourBlinks);
    ts_last_command = now;
    // Serial.println(now);
  }

  // Print data if we have a torque measurement available
  if (scale.is_ready()) {
    float reading = scale.get_units(1);
    // Serial.print(millis());
    // Serial.print("\t");
    Serial.print(reading, kPrecision);

    Serial.print("\t");
    Serial.print(bus.Get(0).Position(), kPrecision);
    Serial.print("\t");
    Serial.print(bus.Get(0).Velocity() / 15.0, kPrecision);

    Serial.print("\t");
    Serial.print(bus.Get(1).Position(), kPrecision);
    Serial.print("\t");
    Serial.print(bus.Get(1).Velocity() / 15.0, kPrecision);
    Serial.println();
  }

}