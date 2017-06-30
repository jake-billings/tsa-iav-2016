#include <SPI.h>
#include "RF24.h"

#define RECIEVER_DEBUG true
#define COMMAND_SIZE 4

RF24 radio(6, 7);
byte TRANSMITTER_ADDRESS[] = "EAKJB_RECEIVER";
byte RECEIVER_ADDRESS[] = "EAKJB_TRANSMITTER";


const bool PIN_OUTPUTS[] = {
  false, false, false, false, false, false, false, false, false, false, false, false, false, false
};
const bool PIN_ANALOGS[] = {
  false, false, false, true, false, true, true, false, false, true, true, true, false, false
};

void recieverSetup() {
#if RECIEVER_DEBUG
  Serial.println("Setting up Reciever...");
#endif

  halSetup();

  for (byte i = 0; i < sizeof(PIN_OUTPUTS); i++) {
    if (PIN_OUTPUTS[i]) {
#if RECIEVER_DEBUG
      Serial.print(i);
      Serial.print(", ");
#endif
      pinMode(i, OUTPUT);
    }
  }

  //Initialize radio...
  radio.begin();

  //Set power level to low because communication is short-range
  radio.setPALevel(RF24_PA_LOW);

  //Open reading and writing pipes (addresses)
  //Switch the addresses on the transmitter
  radio.openWritingPipe(TRANSMITTER_ADDRESS);
  radio.openReadingPipe(1, RECEIVER_ADDRESS);

  //Start listening
  radio.startListening();

#if RECIEVER_DEBUG
  Serial.println("Reciever Setup Complete.");
#endif
}

void readAndProcessCommand() {
  //Wait for the transmitter to send something
  if (radio.available()) {

#if RECIEVER_DEBUG
    Serial.print("Receiving command...");
#endif

    //Initialize an array to hold the command
    byte command[COMMAND_SIZE];

    //Set to false if there is an error reading transmission
    bool okay = true;

    radio.read(command, sizeof(byte)*COMMAND_SIZE);

    //If the transmission has more than 4 bytes, handle this as an
    //error and throw out the additional bytes.
    while (radio.available()) {
#if RECIEVER_DEBUG
      Serial.println("Error reading command. Too many bytes.");
#endif
      okay = false;
      byte junk;
      radio.read(&junk, sizeof(byte));
    }

    //Give a debug message and print the received command
#if RECIEVER_DEBUG
    Serial.print("Done. Received: ");
    for (byte i = 0; i < COMMAND_SIZE; i++) {
      Serial.print(command[i], DEC);
      Serial.print(", ");
    }
    Serial.println();
#endif

    //Process the command
    processCommand(command);
  }
}

void processCommand(byte command[]) {
  if (command[0] == 0) { //PING
#if RECIEVER_DEBUG
    Serial.println("Ping not implemented yet.");
#endif

  } else if (command[0] == 1) { //PIN CONTROL

    //Check if the pin is valid and allowed
    if (command[1] > 0 && command[1] < sizeof(PIN_OUTPUTS) && PIN_OUTPUTS[command[1]]) {
#if RECIEVER_DEBUG
      Serial.print("Setting Pin ");
      Serial.print(command[1]);
      Serial.print(" to ");
#endif

      //Check if the pin is analog
      if (PIN_ANALOGS[command[1]]) {
#if RECIEVER_DEBUG
        Serial.print(command[2]);
#endif

        //If the pin is analog, write the value to it.
        analogWrite(command[1], command[2]);

      } else {
        //If the pin is digital, go HIGH if the desired value is above 0.
        if (command[2] > 0) {
#if RECIEVER_DEBUG
          Serial.print("HIGH");
#endif

          digitalWrite(command[1], HIGH);
        } else {
#if RECIEVER_DEBUG
          Serial.print("LOW");
#endif

          digitalWrite(command[1], LOW);
        }

      }

#if RECIEVER_DEBUG
      Serial.println(".");
#endif
    } else {
      //The pin is invalid.
#if RECIEVER_DEBUG
      Serial.print("Invalid pin: ");
      Serial.println(command[1]);
#endif
    }
  } else if (command[0] == 2) {
    int spd = command[2];
    if (command[3] > 0) {
      spd *= -1;
    }
    halDrive(command[1], spd);
  }
}

