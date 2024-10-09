//Include the library files
#define BLYNK_PRINT Serial

//#define BLYNK_TEMPLATE_ID "TMPL3rd2DbXjg"
//#define BLYNK_TEMPLATE_NAME "Automatic plant watering system"
//#define BLYNK_AUTH_TOKEN "Your Auth Token"
#define BLYNK_TEMPLATE_ID           "TMPL3cH49-Jey"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "olLcoTLLYAKNkADq-GuekuKrteoqw1R0"


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "uNEwHdCCPnfEF4dx0QJ2AQPzg8BGpp7G";//Enter your Auth token
char ssid[] = "iot";//Enter your WIFI name"
char pass[] = "12345678";//Enter your WIFI password

BlynkTimer timer;
bool Relay = 0;

//Define component pins
#define sensor A0
#define waterPump D3

void setup() {
  Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, HIGH);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  //Call the function
  timer.setInterval(100L, soilMoistureSensor);
}

//Get the button value
BLYNK_WRITE(V1) {
  Relay = param.asInt();

  if (Relay == 1) {
    digitalWrite(waterPump, LOW);
  } else {
    digitalWrite(waterPump, HIGH);
  }
}

//Get the soil moisture values
void soilMoistureSensor() {
  int value = analogRead(sensor);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;

  Blynk.virtualWrite(V0, value);

}

void loop() {
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer
}