#include "arduhoop.h"

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(led_number_pixels, led_data_pin, NEO_GRB + NEO_KHZ800);
MPU6050 accelgyro;

int loop_cnt;
int16_t ax, ay, az, gx, gy, gz;
int audio;

void loop() {

    Serial.print("Time "); Serial.print(millis()); Serial.print("ms\t");

    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);

    gx = abs(gx);
    gy = abs(gy);
    gz = abs(gz);

    Serial.print("Acc:\t");
    Serial.print(gx); Serial.print("\t");
    Serial.print(gy); Serial.print("\t");
    Serial.print(gz); Serial.print("\t");

    audio = readMic();
    Serial.print("Audio\t"); Serial.print(audio); Serial.print("\t");

    Serial.print("SW "); Serial.print(isButtonPressed() ? "[X]" : "[ ]"); Serial.print("\t");
    Serial.print("SD_SW "); Serial.print(isSDcardPresent() ? "[X]" : "[ ]"); Serial.print("\t");
    Serial.print("Charging "); Serial.print(isBatteryCharging() ? "[X]" : "[ ]"); Serial.print("\t");
    Serial.print("Voltage "); Serial.print(batteryVoltage()); Serial.print("V\t");

    Serial.println(" ");
    loop_cnt++;



  for (int i = 0; i < led_number_pixels; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, Wheel(loop_cnt), Wheel(80 + loop_cnt), Wheel(160 + loop_cnt)); // Moderately bright green color.
  }
  loop_cnt++;
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(20);

}


