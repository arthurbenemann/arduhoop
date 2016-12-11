#ifndef HARDWARE_H
#define HARDWARE_H

#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include "Adafruit_NeoPixel.h"
#include "SPI.h"
#include "SD.h"

// LED
const int led_data_pin = 10;
const int led_number_pixels = 180;
const int led_pwr =  11;

// SDCard
const int chipSelect = 8;

// Battery
const int bat_stat = A2;
const int bat_sense = A3;

// Switches
const int sw = A0;
const int sd_sw = 6;

// Audio
const int audio_pwr =  A4;
const int mic_pin = A5;

#endif /* HARDWARE_H */
