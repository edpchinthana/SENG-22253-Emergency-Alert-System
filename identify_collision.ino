boolean checkSafeAngle(GyroPosition currentPosition) {
  boolean xAxisCheck = currentPosition.x >= leftPosition.x && currentPosition.x <= rightPosition.x;
  boolean yAxisCheck = currentPosition.y >= 120 && currentPosition.y <= 240;
  return xAxisCheck && yAxisCheck;
}

boolean checkStillAttached() {
  return readSafetyLinkStatus();
}

boolean detectCollision() {
  showMessage("Detection Mode");

  // wait till shock event happens
  waitForShock();

  showMessage("Shock detected!");
  delay(4000);
  GyroPosition current = readGyroValues();
  boolean safeAngle = checkSafeAngle(current);

  if (!checkStillAttached()) {
    showMessage("Danger!");
    return true;
  }

  if (safeAngle) {
    showMessage("Angle - ok");
    return false;
  } else {
    showMessage("Danger!");
    return true;
  }
}

boolean waitForTermination(int waitingTime) {
  long int time = millis();

  int buttonState = LOW;

  int remainingTime = waitingTime/1000;
  while ((time + waitingTime) > millis() && buttonState == LOW) {
    int timeLeft = round((waitingTime - (millis() - time))/1000);
    if (remainingTime != timeLeft) {
      remainingTime = timeLeft;
      showMessage("Sending in "+String(remainingTime));
    }
    
    buttonState = readButton();
  }

  return buttonState;
}