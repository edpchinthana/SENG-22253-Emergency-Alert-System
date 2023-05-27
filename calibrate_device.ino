
void calibrate() {
  if (!checkStillAttached()) {
    showMessage("Check safety link!");
    waitTillButtonPressed();
    return;
  }
  showMessage("Calibration Mode");
  delay(3000);
  
  showMessage("Keep straight");
  waitTillButtonPressed();
  defaultPosition = readGyroValues();

  showMessage("Lean left");
  waitTillButtonPressed();
  leftPosition = readGyroValues();

  showMessage("Lean right");
  waitTillButtonPressed();
  rightPosition = readGyroValues();



  isCalibrated = true;
  showMessage("Calibration was successful");
}