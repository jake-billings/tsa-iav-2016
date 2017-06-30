/**
 * Abstraction for the QTR library optimized for the purposes of closed-loop
 * PID linefollowing.
 */
#include <QTRSensors.h>

//Enables or disables debuging serial prints
#define QTR_DEBUG true

//Parameters for the QTR library
#define NUM_SENSORS   8     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   2     // emitter is controlled by digital pin 2
#define CALIBRATION_ITERATIONS 100// the number of times to call calibrate()

//Initialize the QTR library with the pin layout
QTRSensorsRC qtrrc((unsigned char[]) {
  A0, A1, A2, A3, A4, A5, 4, 5
},NUM_SENSORS, TIMEOUT, EMITTER_PIN);

//A place in memory for the sensor values
unsigned int sensorValues[NUM_SENSORS];

/**
 * Calibrates the QTR sensor array using the QTRSensors library's calibrate
 * method.
 */
void qtrCalibrate() {
#if QTR_DEBUG
  Serial.println("Calibrating QTR...");
#endif

  //Perform the actual calibration
  //Calibration takes about 10 seconds at 400 interations
  //About 25ms per call
  for (int i = 0; i < CALIBRATION_ITERATIONS; i++) {
    qtrrc.calibrate();
  }

#if QTR_DEBUG
  //Print minimum values
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();

  //Print maximum values
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.print(' ');
  }

  //Print completion message.
  Serial.println("\nCalibration Complete.");
#endif
}

/**
 * Returns the position of the sensor on the line ranging from 0-6000
 * with 3000 directly centered on the line using the QTR Library's position
 * method.
 */
int qtrGetPosition() {
  return qtrrc.readLine(sensorValues);
}

