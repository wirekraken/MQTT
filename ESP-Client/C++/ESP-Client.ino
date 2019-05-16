#include <WiFi.h> // библиотека для ESP32
// #include <ESP8266WiFi.h>
#include <PubSubClient.h>

String data = "Some data from ESP";

const char *ssid =  "ssid";
const char *password =  "password";

const char *mqtt_server = "postman.cloudmqtt.com";
const int mqtt_port = 18697;
const char *mqtt_user = "vfwrxgsq";
const char *mqtt_pass = "tYTP8C1e_IeK";

WiFiClient wifiClient;   
PubSubClient client(wifiClient, mqtt_server, mqtt_port);

void setup(){
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to ");
    Serial.print(ssid);
    
    while (WiFi.status() != WL_CONNECTED){ 
      delay(500);
      Serial.print(".");
    }
    Serial.println("WiFi connected");
}

void loop(){
    
    if(WiFi.status() == WL_CONNECTED){
        if(!client.connected()){
            Serial.print("Connecting to MQTT broker");

            if(client.connect(MQTT::Connect("ESP_ID").set_auth(mqtt_user, mqtt_pass))){
              Serial.println(" MQTT connected");
            }
            else{
              Serial.println("Could not connect to MQTT broker");
           }
        }
        else{
            client.loop(); // поддержание соединения с брокером
            getData();
            sendData();
        }
    }
}

// получение данных после подписки
void callback(const MQTT::Publish& pub){
    Serial.print(pub.topic());
    Serial.print(" : ");
    Serial.println(pub.payload_string());
    
    String payload = pub.payload_string();
    
}
