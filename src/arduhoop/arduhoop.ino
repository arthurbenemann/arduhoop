#include "arduhoop.h"

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(led_number_pixels, led_data_pin, NEO_GRB + NEO_KHZ800);
MPU6050 accelgyro;

int cnt;

void loop() {
  //debug();

  if(isButtonPressed()){
    delay(500);
    while(isButtonPressed());
    digitalWrite(led_pwr, !digitalRead(led_pwr));
  }

  cnt++;
  for (int i = 0; i < led_number_pixels; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, Wheel(cnt), Wheel(80 + cnt), Wheel(160 + cnt)); // Moderately bright green color.
  }
  cnt++;
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(20);
}


