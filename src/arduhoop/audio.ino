#include <Filters.h>

int audio;
float peak;
unsigned int time_stamp;

FilterOnePole lowpassFilter( LOWPASS, 160.0 );

void audioBeat() {
  //audio = abs(bassFilter(readMic()))*16;
  audio = abs(  lowpassFilter.input(readMic())) * 64;

  if (audio > peak) {
    peak = audio;
  } else {
    peak = 0.995 * peak;
  }

  if (millis() - time_stamp > 40) {
    time_stamp = millis();
    Serial.println(peak);
    setColor(peak);
  }
}
