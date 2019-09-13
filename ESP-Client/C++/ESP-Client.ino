//#include <WiFi.h> // для ESP32
#include <ESP8266WiFi.h>
#include <PubSubClient.h> // библиотека от Nick O'Leary.

const char *ssid =  "Redmi";
const char *password =  "redmi111";

const char *mqtt_server = "192.168.43.244";
const int mqtt_port = 1883;
const char *mqtt_user = "pi";
const char *mqtt_pass = "123";

WiFiClient wifiClient;   
PubSubClient client(wifiClient, mqtt_server, mqtt_port);

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to ");
    Serial.print(ssid);
    
    while (WiFi.status() != WL_CONNECTED) { 
      delay(500);
      Serial.print(".");
    }
    Serial.println("WiFi connected");
}

void loop() {
    
    if (WiFi.status() == WL_CONNECTED) {
        if (!client.connected()) {
            Serial.print("Connecting to MQTT broker");

            bool isConnect = client.connect(MQTT::Connect("ESP_ID").set_auth(mqtt_user, mqtt_pass));
            
            if (isConnect) {
              Serial.println(" MQTT connected");
            }
            else {
              Serial.println("Could not connect to MQTT broker");
           }
        }
        else {
              client.loop(); // поддержание соединения с брокером
              getData();
              sendData();
        }
    }
}

// получение данных после подписки
void callback(const MQTT::Publish& pub) {

    Serial.print(pub.topic());
    Serial.print(" : ");
    Serial.println(pub.payload_string());
    
}

void getData() {

  client.set_callback(callback);
  client.subscribe("Android/#");

}

void sendData() {

   String data = "Data from ESP";
   Serial.print("Send : ");
   Serial.println(data);
   client.publish("ESP", data);  
   delay(1000);
   
}