String emergencyServiceNo = "+94711111111";
String riderName = "John Doe";
String riderBloodGroup = "A+";
String emergencyContact = "James Bond - 071 232 2322";



String generateMessageBody(String location, String time) {
  return "Rider in danger!\nRider name: "+riderName+",\nBlood Group: "+riderBloodGroup+",\nEmergency Contact: "+emergencyContact+",\nLocation: "+location+",\nTime: "+time;
}

void sendEmergencyAlerts() {
  String location = readGPSCoordinates();
  String time = readDateTime();

  String message = generateMessageBody(location, time);

  sendSMS(emergencyServiceNo, message);
}