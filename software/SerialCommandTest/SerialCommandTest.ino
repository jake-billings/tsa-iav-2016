#define COMMAND_SIZE 4

const bool PIN_PERMISSIONS[] = {
  false, false, true, true, true, true, true, true, true, true, true, true, true, true
};
const bool PIN_ANALOG[] = {
  false, false, false, true, false, true, true, false, false, true, true, true, false, false
};

void setup() {
  Serial.begin(9600);

  byte command[COMMAND_SIZE] = {0x01, 0x02, 0x34, 0x00};

  processCommand(command);
}

void loop() {
}

void processCommand(byte command[COMMAND_SIZE]) {
  if (command[0] == 0) { //PING
    Serial.println("Ping not implemented yet.");

  } else if (command[0] == 1) { //PIN CONTROL

    //Check if the pin is valid and allowed
    if (command[1] > 0 && command[1] < sizeof(PIN_PERMISSIONS) && PIN_PERMISSIONS[command[1]]) {

      //Set the pin to an output
      pinMode(command[1], OUTPUT);

      //Check if the pin is analog
      if (PIN_ANALOG[command[1]]) {
        //If the pin is analog, write the value to it.
        analogWrite(command[1], command[2]);
        
      } else {
        //If the pin is digital, go HIGH if the desired value is above 0.
        if (command[2] > 0) {
          digitalWrite(command[1],HIGH);
        } else {
          digitalWrite(command[1],LOW);
        }
        
      }
    } else {
      //The pin is invalid.
      Serial.print("Invalid pin: ");
      Serial.println(command[1]);
    }
  }
}

