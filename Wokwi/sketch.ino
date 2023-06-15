
// From https://randomnerdtutorials.com/esp32-mqtt-publish-subscribe-arduino-ide

#include <WiFi.h>
#include "DHTesp.h"
#include "PubSubClient.h"
#include <MQTT.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqttServer = "iot-alyani.cloud.shiftr.io";
int port = 1883;
String stMac;
char mac[50];
char clientId[50];
const int DHT_PIN = 15;
char result_temp[10]; 
char result_hum[10]; 

WiFiClient espClient;
PubSubClient client(espClient);
DHTesp dhtSensor;
MQTTClient clientt;
const int ledPin = 2;

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  wifiConnect();
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
  stMac = WiFi.macAddress();
  stMac.replace(":", "_");
  Serial.println(stMac);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
  client.setServer(mqttServer, port);
  client.setCallback(callback);
  pinMode(ledPin, OUTPUT);
}

void wifiConnect() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void mqttReconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    long r = random(1000);
    sprintf(clientId, "clientId-%ld", r);
    if (client.connect(clientId,"iot-alyani","iSjsOPFkpRT8jtfq")) {
      Serial.print(clientId);
      Serial.println(" connected");
      client.subscribe("alyanins/iot/#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* message, unsigned int length) {
  TempAndHumidity  data_temp = dhtSensor.getTempAndHumidity();
  dtostrf(data_temp.temperature, 6, 2, result_temp);
  dtostrf(data_temp.humidity, 6, 2, result_hum); 
  String stMessage;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    stMessage += (char)message[i];
  }
  Serial.println();

//Temp
    if(stMessage == "sensor activated"){
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
      client.publish("alyanins/iot/temperature", result_temp);
    }
    else if(stMessage == "sensor terminated"){
      Serial.println("sensor terminated");
      digitalWrite(ledPin, LOW);
    }

//hum
    if(stMessage == "sensor activated"){
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
      client.publish("alyanins/iot/humidity", result_hum);
    }
    else if(stMessage == "sensor terminated"){
      Serial.println("sensor terminated");
      digitalWrite(ledPin, LOW);
    }
}

void loop() {
  delay(10);
  if (!client.connected()) {
    mqttReconnect();
  }
  client.loop();
} 
