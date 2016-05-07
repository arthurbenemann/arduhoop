#include "arduhoop.h"

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(led_number_pixels, led_data_pin, NEO_GRB + NEO_KHZ800);
MPU6050 accelgyro;

void loop() {
  audioBeat();
  //debug();
}


