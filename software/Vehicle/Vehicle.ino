#define DEBUG true
#define LINE_FOLLOW_STEP_INTERVAL 10 //Run line following loop every 10 milliseconds

void setup()
{
#if DEBUG
  Serial.begin(9600);
#endif

  lineFollowSetup();

  pinMode(7,INPUT);
  while (!digitalRead(7)) {
    //Wait
  }
}

//The last time in milliseconds from boot that the line following loop ran
long lastLineFollowStep = -1;
bool lineFollowEnabled = true;
void loop() {
  long mils = millis();

  if (lineFollowEnabled) {
    //Run the loop once every 10 milliseconds
    if ((mils - lastLineFollowStep) >= LINE_FOLLOW_STEP_INTERVAL) {

      //Run the loop
      lineFollowStep();

      //Store the time that the loop ran
      lastLineFollowStep = mils;
    }
  } else {
    halDrive(0, 0);
    halDrive(1, 0);
  }

#if DEBUG
  if (Serial.available()) {
    Serial.read();
    lineFollowEnabled = !lineFollowEnabled;
  }
#endif
}
