#include <SPI.h>
#include "RF24.h"

#define COMMAND_SIZE 4

// Clockwise and counter-clockwise definitions.
// Depending on how you wired your motors, you may need to swap.
#define FORWARD  HIGH
#define BACKWARD LOW

// Motor definitions to make life easier:
#define MOTOR_A 0
#define MOTOR_B 1

RF24 radio(7, 8);
byte TRANSMITTER_ADDRESS[] = "EAKJB_RECEIVER";
byte RECEIVER_ADDRESS[] = "EAKJB_TRANSMITTER";

void setup() {
  //Initialize serial...
  Serial.begin(9600);
  Serial.print("Intializing transmitter...");

  //Initialize radio...
  radio.begin();

  //Set power level to low becaue communication is short-range
  radio.setPALevel(RF24_PA_LOW);

  //Open reading and writing pipes (addresses)
  //Switch the addresses on the transmitter
  radio.openWritingPipe(RECEIVER_ADDRESS);
  radio.openReadingPipe(1, TRANSMITTER_ADDRESS);

  //Start listening
  radio.startListening();

  //Notify debugger that initialization has finished.
  Serial.println("Done.");
}

void loop() {
  int reading = analogRead(A0);
  int reading2 = analogRead(A1);
  
//  Serial.println(reading);
//  Serial.print("Transmitting command...");
  
  byte val;
  byte dir;
  if (reading>=512) {
    val=map(reading,512,1023,0,257);
    dir=FORWARD;
  } else {
    val=map(reading,511,0,0,257);
    dir=BACKWARD;
  }
  byte val2;
  byte dir2;
  if (reading2>=512) {
    val2=map(reading2,512,1023,0,257);
    dir2=FORWARD;
  } else {
    val2=map(reading2,511,0,0,257);
    dir2=BACKWARD;
  }
  Serial.print(val);
  Serial.print('\t');
  Serial.println(val2);
  
  byte commandA[COMMAND_SIZE] = {0x02, MOTOR_A, val, dir};
  byte commandB[COMMAND_SIZE] = {0x02, MOTOR_B, val, dir};

  radio.stopListening();

  radio.write(&commandA, sizeof(byte)*COMMAND_SIZE);
  delay(80);
  radio.write(&commandB, sizeof(byte)*COMMAND_SIZE);

  radio.startListening();

//  Serial.println("Done.");

  delay(80);
}


