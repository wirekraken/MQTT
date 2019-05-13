#include <WiFi.h> // библиотека для ESP32
// #include <ESP8266WiFi.h>
#include <PubSubClient.h>

String data = "Some data from ESP";

const char *ssid =  "Redmi";
const char *password =  "redmi111";

const char *mqtt_server = "postman.cloudmqtt.com";
const int mqtt_port = 18697;
const char *mqtt_user = "vfwrxgsq";
const char *mqtt_pass = "HLC0HqJJ1TFI";

void callback(const MQTT::Publish& pub){
    Serial.print(pub.topic());
    Serial.print(" : ");
    Serial.println(pub.payload_string());
    
    String payload = pub.payload_string();
    
}

WiFiClient wifiClient;   
PubSubClient client(wifiClient, mqtt_server, mqtt_port);

void setup(){
    Serial.begin(115200);
}

void loop(){

    if(WiFi.status() != WL_CONNECTED){
        Serial.print("Connecting to ");
        Serial.print(ssid);
        Serial.println("...");
        WiFi.begin(ssid, password);
        
        if(WiFi.waitForConnectResult() != WL_CONNECTED){
            return;
        }

        Serial.println("WiFi connected");
    }
    
    if(WiFi.status() == WL_CONNECTED){
        if(!client.connected()){
            Serial.println("Connecting to MQTT server");
            if(client.connect(MQTT::Connect("ESP_1").set_auth(mqtt_user, mqtt_pass))){
                Serial.println("Connected to MQTT server");
                client.set_callback(callback);
                client.subscribe("data/fromAndroid"); // подписывааемся на  топик

            }
            else{
                Serial.println("Could not connect to MQTT server");   
            }
        }
        
        if(client.connected()){
            client.loop();
            SendData();
        }
    }
}

void SendData(){
    client.publish("data/fromESP", data); // отправляем
    delay(3000);
}
