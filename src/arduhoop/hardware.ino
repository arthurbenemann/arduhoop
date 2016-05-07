#include "arduhoop.h"

const float BATTERY_SCALING = 2.56 * 2.0 / 1023;
const float alpha = 0.01;
float sample_filter = -1;

const int MIC_BIAS = 667;

int readMic() {
  return analogRead(mic_pin) - MIC_BIAS;
}

float batteryVoltage() {
  // read the input on analog pin 0:
  int sample = analogRead(bat_sense);
  if (sample_filter != -1) {
    sample_filter = alpha * sample + (1 - alpha) * sample_filter;
  } else {
    sample_filter = sample;
  }
  return sample_filter * BATTERY_SCALING;
}

bool isBatteryCharging() {
  return digitalRead(bat_stat) == LOW;
}

bool isButtonPressed() {
  return digitalRead(sw) == LOW;
}

bool isSDcardPresent() {
  return digitalRead(sd_sw) == LOW;
}

