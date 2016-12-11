
void setup() {
  Serial.begin(9600);
  //while (!Serial);
  Serial.println("Arduhoop");

  Serial.println("Initializing battery sensors...   ");
  analogReference(INTERNAL);
  pinMode(bat_stat, INPUT);

  Serial.println("Initializing mic...   ");
  pinMode(audio_pwr, OUTPUT);
  digitalWrite(audio_pwr, HIGH);

  Serial.println("Initializing LED string...");
  pinMode(led_pwr, OUTPUT);
  ledsOn();
  pixels.begin(); // This initializes the NeoPixel library.


  Serial.print("Initializing I2C devices... ");
  Wire.begin();
  accelgyro.initialize();
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  Serial.print("Initializing SD card...   ");
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
  } else {
    Serial.println("card initialized.");
  }

  Serial.println("Intialization done.");
}
