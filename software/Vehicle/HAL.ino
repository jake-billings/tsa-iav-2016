/**
 * The Hardware Abstraction Layer (HAL) interfaces a single method call
 * to control a motor with whatever motor controller layer is being used.
 * Early in development, the Ardumoto shield was used. Later, a cutom
 * H-Bridge was used. The HAL removes the need to modify PID or LineFollowing
 * code further than KP and KD weights.
 */

#define ARDUMOTO true //True if the motor controller is an ardumoto
#define HAL_ENABLED true //True if motors should run
#define HAL_DEBUG true //True if debug messages should be shown

//Motor integer values
#define MOTOR_A 0
#define MOTOR_B 1

//-------ARDUMOTO----------
#if ARDUMOTO

// Clockwise and counter-clockwise definitions.
// Depending on how you wired your motors, you may need to swap.
#define CW  0
#define CCW 1

// Pin Assignments
const byte PWMA = 3;  // PWM control (speed) for motor A
const byte PWMB = 10; // PWM control (speed) for motor B
const byte DIRA = 9; // Direction control for motor A
const byte DIRB = 8; // Direction control for motor B

/**
 * Setup lower level HAL components
 */
void halSetup() {
  #if HAL_DEBUG
  Serial.println("Setting up HAL...");
  #endif
  setupArdumoto();
  #if HAL_DEBUG
  Serial.println("HAL setup complete.");
  #endif
}

/**
 * Drives a given motor at a given speed
 */
void halDrive(int motor, int spd) {
  #if HAL_ENABLED
  driveArdumoto(motor, (spd < 0 ? CCW : CW), (byte) abs(spd));
  #endif
}

/**
 * Returns the maximum value for a motor
 */
int halGetMax() {
  return 255;
}

/**
 * Returns the minimum value for a motor
 */
int halGetMin() {
  return -255;
}

/**
 * Return a value where the motor does not spin
 */
int halGetZero() {
  return 0;
}

// driveArdumoto drives 'motor' in 'dir' direction at 'spd' speed
void driveArdumoto(byte motor, byte dir, byte spd)
{

  if (motor == MOTOR_A) {
    digitalWrite(DIRA, dir > 0 ? HIGH : LOW);
    analogWrite(PWMA, spd);
  }
  else if (motor == MOTOR_B) {
    digitalWrite(DIRB, dir > 0 ? HIGH : LOW);
    analogWrite(PWMB, spd);
  }
}

// setupArdumoto initialize all pins
void setupArdumoto() {
  #if HAL_DEBUG
  Serial.println("Setting up Ardumoto...");
  #endif
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
  
  #if HAL_DEBUG
  Serial.println("Ardumoto Setup Complete.");
  #endif
}
#endif
