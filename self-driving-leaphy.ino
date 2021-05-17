#include <Arduino.h>
#include "Leaphyoriginal1.h" // voor LED's

float dangerDistance = 30;
float reverseDistance = 10;

float escapeOffset = 5;

float firstTurnTime = 5;

void nearWall(float currentDistance) {
  setLed(155, 165, 0);
  tone(4, 440, 50);

  if (getDistance() < reverseDistance) {
    tooCloseToWall();
  }

  for (int i = 0; i <= firstTurnTime; i++) { // turn clockwise for firstTurnTime iterations
    setMotor(9, 50);
    setMotor(10, -100);
  }
  
  if (getDistance() <= currentDistance) { // if the distance has shrunk since the for loop, turn the other (presumably more efficient way)
    while (getDistance() < dangerDistance + escapeOffset) {
      setMotor(9, -100);
      setMotor(10, 50);

      if (getDistance() < reverseDistance) {
        tooCloseToWall();
      }
    }
  } else {
    while (getDistance() < dangerDistance + escapeOffset) {
      setMotor(9, 50);
      setMotor(10, -100);

      if (getDistance() < reverseDistance) {
        tooCloseToWall();
      }
    }
  }
}

void tooCloseToWall() {
  while (getDistance() < reverseDistance + escapeOffset) {
    setLed(255, 0, 0);
    setMotor(9, -75);
    setMotor(10, -75);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
}

void loop() {
  // normal driving
  setLed(0, 255, 0);
  moveMotors(1, 80);

  if (getDistance() < dangerDistance) {
    nearWall(getDistance());
  }
}
