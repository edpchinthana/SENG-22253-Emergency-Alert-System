
#include <Wire.h>
#include <LiquidCrystal.h>
#include "Gyro_Position.h"
#include "GPS_Position.h"

const boolean DEBUG = true;
boolean isCalibrated = false;


GyroPosition defaultPosition;
GyroPosition leftPosition;
GyroPosition rightPosition;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  initializeShockModule();
  initializeGyroModule();
  initializeDisplayModule();
  initializeInputModule();
  initializeA7Module();
}


void loop() {
  if (!isCalibrated) {
    calibrate();
  } else {
    boolean isCollided = detectCollision();
    

    if (isCollided) {
      showMessage("Emergency mode!");
      setBuzzer(HIGH);
      delay(4000);
      boolean isTerminated = waitForTermination(10000);

      if (isTerminated) {
        showMessage("Terminated!");
        setBuzzer(LOW);
      } else {
        showMessage("Sending alerts!");
        sendEmergencyAlerts();
        delay(2000);
        showMessage("Alerts sent!");
      }

      waitTillButtonPressed();
      setBuzzer(LOW);
    }
  }
}
