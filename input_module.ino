boolean pushButtonState = 0;
const int buttonInput = 4;

void initializeInputModule() {
  pinMode(buttonInput, INPUT);
}
int readButton() {
  int buttonState = digitalRead(buttonInput);
  return buttonState;
}

void waitTillButtonPressed() {
  int buttonState = 0;
  while (buttonState == LOW) {
    buttonState = readButton();
  }
  Serial.println("Button Pressed!");
  delay(1000);
}

boolean checkButtonPressed() {
  int buttonState = readButton();
  boolean pressed = pushButtonState == buttonState;
  pushButtonState = buttonState;
  return buttonState;
}