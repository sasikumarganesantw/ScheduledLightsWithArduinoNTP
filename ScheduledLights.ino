#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char* ssid = "yourWiFiName";
const char* password =  "yourWiFiPassword";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Variables to save date and time
int startTimeHour = 10;
int startTimeMins = 0;

int endTimeHour = 12;
int endTimeMins = 30;

void setup() {
  // Define the IO pin which thorugh you emit the signal
  pinMode(4, OUTPUT);
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

// Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  double offsetIST = 3600 * 5.5;
  timeClient.setTimeOffset(offsetIST);
}
void loop() {
  
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }

  // Extract time
  Serial.print("Time: ");
  Serial.println(timeClient.getFormattedTime());

  // Powers the light on start time  
  if((timeClient.getHours() >= startTimeHour && timeClient.getMinutes() >= startTimeMins) && (timeClient.getHours() <= endTimeHour && timeClient.getMinutes() < endTimeMins)){
      digitalWrite(4, HIGH);
  } else {
      digitalWrite(4, LOW);
  }
  delay(1000);
}