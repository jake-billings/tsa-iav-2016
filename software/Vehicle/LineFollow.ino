/**
 * Abstraction of line of following code optimized for closed-loop control
 * within a larger system.
 */
#define LINE_FOLLOW_DEBUG true

//The PID proportional weight to apply to the error
#define KP 0.05

//The PID derivative weight to apply to the error
#define KD 0.7

//The PID setpoint of the system
//This is 3000 because the QTR reads 0-6000 with 3000 at the center
#define SETPOINT 3000

//The default set spead for each motor 0-100
#define MOTOR_A_SPEED 220
#define MOTOR_B_SPEED MOTOR_A_SPEED

/**
 * Runs the setup methods for all of LineFollowing's dependencies
 */
void lineFollowSetup() {
  #if LINE_FOLLOW_DEBUG
  Serial.println("Setting up Line Following...");
  #endif

  //Setup dependenceis
  qtrCalibrate();
  halSetup();
  
  #if LINE_FOLLOW_DEBUG
  Serial.println("Line Following Setup Complete.");
  #endif
}

//Variable outside of the step scope to store the last error
int lastPos = 3000;

/**
 * Runs a single step of the control loop for line following. This should
 * be called at very regular intervals to keep a consistant derivative value.
 */
void lineFollowStep() {
  //Read position on line from QTR sensor
  int pos = qtrGetPosition();

  //Run PID on the new position
  int output = pid(SETPOINT, pos, lastPos, KP, KD);
  lastPos = pos;

  
  #if LINE_FOLLOW_DEBUG
  Serial.print("Position: ");
  Serial.print(pos);
  Serial.print("\tOutput: ");
  Serial.print(output);
  Serial.println();
  #endif

  //Calculate motor speeds
  int outputA = MOTOR_A_SPEED - output;
  int outputB = MOTOR_B_SPEED + output;

  //If the motor speed exceeds the bounds, use max or min values
  if (outputA < halGetMin())
    outputA = halGetMin();
  if (outputB < halGetMin())
    outputB = halGetMin();
  if (outputA > halGetMax())
    outputA = halGetMax();
  if (outputB > halGetMax())
    outputB = halGetMax();

  //Output new value to motors
  halDrive(MOTOR_A,outputA);
  halDrive(MOTOR_B,outputB);
}

