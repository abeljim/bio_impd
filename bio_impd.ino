/*
ad5933-test
    Reads impedance values from the AD5933 over I2C and prints them serially.
*/

#include <Wire.h>
#include "AD5933.h"

// Start frequency limited by arduino 8 bit memory
#define START_FREQ  (100)
#define FREQ_INCR   (1000)
#define NUM_INCR    (40)
#define REF_RESIST  (10000)

double gain[NUM_INCR+1];
int phase[NUM_INCR+1];

void setup(void)
{
  Wire.begin();
  Serial.begin(9600);

  // Perform initial configuration. Fail if any one of these fail.
  if (!(AD5933::reset() &&
        AD5933::setInternalClock(true) &&
        AD5933::setStartFrequency(START_FREQ) &&
        AD5933::setIncrementFrequency(FREQ_INCR) &&
        AD5933::setNumberIncrements(NUM_INCR) &&
        AD5933::setPGAGain(PGA_GAIN_X1)))
        {
            Serial.println("FAILED in initialization!");
            while (true) ;
        }

  // Perform calibration sweep
  if (AD5933::calibrate(gain, phase, REF_RESIST, NUM_INCR+1))
    Serial.println("Calibrated!");
  else
    Serial.println("Calibration failed...");
}

void loop(void)
{
    // Create arrays to hold the data
    int real[NUM_INCR+1], imag[NUM_INCR+1];

    // Perform the frequency sweep
    if (AD5933::frequencySweep(real, imag, NUM_INCR+1)) {
      // Print the frequency data
      int cfreq = START_FREQ/1000;
      for (int i = 0; i < NUM_INCR+1; i++, cfreq += FREQ_INCR/1000) {
        // Print raw frequency data
        Serial.print(cfreq);
        Serial.print(": R=");
        Serial.print(real[i]);
        Serial.print("/I=");
        Serial.print(imag[i]);

        // Compute impedance this is the use full section
        double magnitude = sqrt(pow(real[i], 2) + pow(imag[i], 2));
        double impedance = 1/(magnitude*gain[i]);
        Serial.print("  |Z|=");
        Serial.println(impedance);
      }
      Serial.println("Frequency sweep complete!");
    } else {
      Serial.println("Frequency sweep failed...");
    }

  // Delay 5 seconds
  delay(5000);
}
