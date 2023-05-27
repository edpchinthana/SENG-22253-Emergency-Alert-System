#include <SoftwareSerial.h>
// #include <GSM.h>
#define PINNUMBER ""

int gsmRX = 2;
int gsmTX = 3;

SoftwareSerial gsmSerial(gsmRX, gsmTX);  //RX, TX

// GSM gsmAccess;

// GSM_SMS sms;
boolean notConnected = true;

void initializeA7Module() {
  gsmSerial.begin(115200);

  showMessage("Initializing");
  sendATCommand("AT\r\n", 2000);
  showMessage("done");
}

void baudrate() {
  int i = 0;
  for (i = 0; i < 10; i++) {
    String msg = String("");
    msg = sendATCommand("AT\r\n", 1000);
    showMessage(msg);
    if (msg.indexOf("ok") >= 0) {
      return;
    }
  }
}


String sendATCommand(String command, const int timeout) {
  String response = "";
  gsmSerial.print(command);  

  long int time = millis();


  while (gsmSerial.available() && (time + timeout) > millis()) {
    char c = gsmSerial.read(); 
    response += c;
  }


  showMessage(response);
  return response;
}

String sendCtrlZCommand(const int timeout) {
  String response = "";
  gsmSerial.print(0x1a);

  long int time = millis();

  while ((time + timeout) > millis()) {
    while (gsmSerial.available()) {
      char c = gsmSerial.read();
      response += c;
    }
  }

  return response;
}

String readDateTime() {
  String command = "AT+CCLK?";
  String response = sendATCommand(command, 2000);

  if (response.indexOf("+CCLK") > 0) {
    return response;
  } else {
    showMessage("Get time failed");
    return "";
  }
}

String readGPSCoordinates() {
  String command1 = "AT+GPS=1\r\n";   // turn on GPS
  String command2 = "AT+AGPS=1\r\n";  // reset the GPS in autonomy mode
  String command3 = "AT+GPSRD=1\r\n";     // get current GPS location

  showMessage("Turning on GPS");
  sendATCommand(command1, 2000);
  sendATCommand(command2, 2000);

  showMessage("Reading GPS coordinates");
  String response = sendATCommand(command3, 10000);

  if (response.indexOf("$GPGGA") > 0) {
    char buf[350];
    response.toCharArray(buf, 350);
    String link = convertToLink(buf);
      showMessage(link);
    return link;
  } else {
    showMessage("Get location failed!");
    delay(1000);
    return "";
  }
}

void sendSMS(String recepientNo, String msg) {
  gsmSerial.println("AT+CMGF=1");
  gsmSerial.println("AT+CMGS=\""+recepientNo+"\"");
  delay(1000);
  gsmSerial.print(msg);
  delay(100);
  gsmSerial.write(26);
  gsmSerial.write(0x22);
  gsmSerial.write(0x0D);
  gsmSerial.write(0x0A);
}

String convertToLink(char* test_str) {
  int i = 0;
  char *start_pch, *end_pch;
  char extracted_str[16];
  char temp_str[32];
  char map_str[100] = "https://www.google.com/maps/place/";

  float f_temp, latitude, longuitude;
  int i_temp;

  start_pch = test_str - 1;

  end_pch = strstr(test_str, ",");
  while (end_pch != NULL) {
    ++i;
    memset(extracted_str, 0, 16);
    strncpy(extracted_str, start_pch + 1, end_pch - start_pch - 1);
    if (i == 3) {
      f_temp = atof(extracted_str);
      i_temp = (int)f_temp;
      f_temp = (f_temp - i_temp) * 60;
      sprintf(temp_str, "%i°%i'%s\"", i_temp / 100, i_temp % 100, String(f_temp, 1).c_str());
      strcat(map_str, temp_str);
      latitude = (atof(&extracted_str[2]) / 60) + (i_temp / 100);
    } else if (i == 4) {
      strcat(map_str, extracted_str);
      if (extracted_str[0] == 'S') latitude *= -1;
    } else if (i == 5) {
      f_temp = atof(extracted_str);
      i_temp = (int)f_temp;
      f_temp = (f_temp - i_temp) * 60;
      sprintf(temp_str, "%c%i°%i'%s\"", (i_temp > 0) ? '+' : '-', i_temp / 100, i_temp % 100, String(f_temp, 1).c_str());
      strcat(map_str, temp_str);
      longuitude = (atof(&extracted_str[3]) / 60) + (i_temp / 100);
    } else if (i == 6) {
      strcat(map_str, extracted_str);
      if (extracted_str[0] == 'W') longuitude *= -1;
    }
    start_pch = end_pch;
    end_pch = strstr(end_pch + 1, ",");
  }

  //retrieve (checksum)
  memset(extracted_str, 0, 16);
  strncpy(extracted_str, start_pch + 1, strlen(start_pch));

  sprintf(temp_str, "/@%s,%s", String(latitude, 5).c_str(), String(longuitude, 5).c_str());
  strcat(map_str, temp_str);


  // Serial.println(map_str);
  return String(map_str);
}
