const int shockInput = 5;
const int safetyLinkInput = 7;

void initializeShockModule() {
  pinMode(shockInput, INPUT);
  pinMode(safetyLinkInput, INPUT_PULLUP);
}

int readShockInput() {
  return digitalRead(shockInput);
}

void waitForShock() {
    boolean shockState = HIGH;
    while (shockState == HIGH) {
    shockState = digitalRead(shockInput);
  }
}

int readSafetyLinkStatus() {
  return !digitalRead(safetyLinkInput);
}