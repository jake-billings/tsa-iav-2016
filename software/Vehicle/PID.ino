/**
 * Abstraction of PID math
 * 
 * Currently, only proportional and derivative math is implemented
 * No steady-state errors have been present yet, so the integral
 * componenet has not been implemented.
 * 
 * setpoint - The ideal condition of the system
 * sig - The input into the control loop (for instance, the QTR sensor reading)
 * lastSig - The input into the control loop in the last step (used to calculate derivative)
 * KP - weight of the proportional component of the error
 * KD - weight of the derivative component of the error
 */
int pid(int setpoint, int sig, int lastSig, float kp, float kd) {
  //Calculate error and last error from input signal and setpoint
  int error = sig - setpoint;
  int lastError = lastSig - setpoint;
  
  //Perform the pid calculation by applying KP and KD weights
  //to the error and the derivative of the error.
  int output = kp * error + kd * (error - lastError);

  return output;
}

