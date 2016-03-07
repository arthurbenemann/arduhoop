/*
  SD card file dump

 This example shows how to read a file from the SD card using the
 SD library and send it over the serial port.

 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

 created  22 December 2010
 by Limor Fried
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

#include <SPI.h>
#include <SD.h>
#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN    6    // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 6

#define SD_CS 4

uint8_t sdBuf[512];

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialize all pixels to 'off'
  strip.begin();
  strip.show(); 

  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(SD_CS)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop() {

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("test.bmp");

  // if the file is available, write to it:
  if (dataFile) {

    while(true){

    if(dataFile.read(sdBuf, 34)             &&    // Load header
      (*(uint16_t *)&sdBuf[ 0] == 0x4D42) &&    // BMP signature
      (*(uint16_t *)&sdBuf[26] == 1)      &&    // Planes: must be 1
      (*(uint16_t *)&sdBuf[28] == 24)     &&    // Bits per pixel: must be 24
      (*(uint32_t *)&sdBuf[30] == 0)) {         // Compression: must be 0 (none)
      
      int   bmpWidth,            // BMP width in pixels
            bmpHeight;           // BMP height in pixels
      uint32_t  bmpImageoffset;  // Start of image data in BMP file
        
      // Supported BMP format -- proceed!
      bmpImageoffset = *(uint32_t *)&sdBuf[10]; // Start of image data
      bmpWidth       = *(uint32_t *)&sdBuf[18]; // Image dimensions
      bmpHeight      = *(uint32_t *)&sdBuf[22];
      // That's some nonportable, endian-dependent code right there.
  
      Serial.print(bmpWidth);
      Serial.write('x');
      Serial.print(bmpHeight);
      Serial.println(F(" pixels"));
      
      dataFile.seek(bmpImageoffset);
  
        int line =0;
      while (dataFile.available()) {
        Serial.print("Line ");
        Serial.print(line++);
        Serial.print("  position ");
        Serial.println(dataFile.position());
        
        dataFile.readBytes(sdBuf, 2 + PIXEL_COUNT*3);
        int i =0;
        for(int pixel = 0; pixel<6; pixel++){
          strip.setPixelColor(pixel, sdBuf[i], sdBuf[i+1], sdBuf[i+2]);
          Serial.print(sdBuf[i],HEX);          
          Serial.print(sdBuf[i],HEX);
          Serial.print(sdBuf[i],HEX);
          Serial.print(' ');
          i += 3;
        }
        Serial.println();
        strip.show();
        delay(200);
      }
     } else{
      Serial.println("incompatible file");
     }
     dataFile.seek(0);
    }
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening file.txt");
  }
}

