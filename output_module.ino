const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int buzzerPin = 6;

void initializeDisplayModule() {
  lcd.begin(16, 2);
  pinMode(buzzerPin, OUTPUT);
}

void showMessage(String msg) {
  if (DEBUG) {
    Serial.println(msg);
  }
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg);
}

void setBuzzer(boolean mode) {
  digitalWrite(buzzerPin, mode);
}