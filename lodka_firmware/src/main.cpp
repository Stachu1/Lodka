#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>


#define AP 1

#define KEY "1111"

#define MOTOR_L 12
#define MOTOR_R 13

#define MOTOR_L_CHANNEL 0
#define MOTOR_R_CHANNEL 1

const char* ssid = "BSR - Uczniowie";
const char* pswd = "bednarsk@";

const char* ap_ssid = "esp-wifi";
const char* ap_pswd = "esp-wifi";


WiFiServer server(80);

StaticJsonDocument<2048> json_document;


void wifi_init(bool ap);
void server_loop(void * params);


void setup() {
  Serial.begin(9600);

  ledcSetup(MOTOR_L_CHANNEL, 400, 16);
  ledcSetup(MOTOR_R_CHANNEL, 400, 16);

  ledcAttachPin(MOTOR_L, MOTOR_L_CHANNEL);
  ledcAttachPin(MOTOR_R, MOTOR_R_CHANNEL);

  wifi_init(AP);

  server.begin(); 

  xTaskCreate(server_loop, "Server loop", 4096, NULL, 0, NULL);
}

void loop() {
  if(json_document["key"] == KEY) {
    
  }
}

void server_loop(void * params) {
  for(;;) {
    WiFiClient client = server.available();
    if(client)
    {
      client.println(KEY);
      while(client.connected())
      {
        while(client.available() > 0)
        {
          char cmd[1024];
          client.read((uint8_t *)cmd, 1024);
          Serial.println(cmd);
          deserializeJson(json_document, cmd);
        }
      }
      client.stop();
    }
    vTaskDelay(1);
  }
}

void wifi_init(bool ap) {
  
  Serial.print("IP Address is: ");

  if(ap) {
    WiFi.softAP(ap_ssid, ap_pswd);
    IPAddress IP = WiFi.softAPIP();
    Serial.println(IP);
  } else {
    WiFi.begin(ssid, pswd);

    while(WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi...");
    }
    Serial.println(WiFi.localIP());
  }  
}