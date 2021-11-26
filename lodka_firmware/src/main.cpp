#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>


#define AP 1

#define KEY "1111"

#define MOTOR_L_F 5
#define MOTOR_L_B 18
#define MOTOR_R_F 19
#define MOTOR_R_B 21

#define MOTOR_L_CHANNEL_F 0
#define MOTOR_L_CHANNEL_B 1
#define MOTOR_R_CHANNEL_F 2 
#define MOTOR_R_CHANNEL_B 3 

const char* ssid = "BSR - Uczniowie";
const char* pswd = "bednarsk@";

const char* ap_ssid = "esp-wifi";
const char* ap_pswd = "esp-wifi";


WiFiServer server(80);

StaticJsonDocument<2048> json_document;


void wifi_init(bool ap);
void server_loop(void * params);


void setup() {
  // Serial.begin(9600);

  ledcSetup(MOTOR_L_CHANNEL_F, 400, 16);
  ledcSetup(MOTOR_L_CHANNEL_B, 400, 16);
  ledcSetup(MOTOR_R_CHANNEL_F, 400, 16);
  ledcSetup(MOTOR_R_CHANNEL_B, 400, 16);

  ledcAttachPin(MOTOR_L_F, MOTOR_L_CHANNEL_F);
  ledcAttachPin(MOTOR_L_B, MOTOR_L_CHANNEL_B);
  ledcAttachPin(MOTOR_R_F, MOTOR_R_CHANNEL_F);
  ledcAttachPin(MOTOR_R_B, MOTOR_R_CHANNEL_B);

  wifi_init(AP);

  server.begin(); 

  xTaskCreate(server_loop, "Server loop", 4096, NULL, 0, NULL);
}

void loop() {
  if(json_document["key"] == KEY) {
    if(json_document["task"] == "set_motors") {
      if(json_document["args"]["left"] > 0.0)
        ledcWrite(MOTOR_L_F, abs((float)json_document["args"]["left"])*65535);
      else if(json_document["args"]["left"] < 0.0)
        ledcWrite(MOTOR_L_B, abs((float)json_document["args"]["left"])*65535);
      else 
        ledcWrite(MOTOR_L_F, 0);
        ledcWrite(MOTOR_L_B, 0);
      
      if(json_document["args"]["right"] > 0.0)
        ledcWrite(MOTOR_R_F, abs((float)json_document["args"]["right"])*65535);
      else if(json_document["args"]["right"] < 0.0)
        ledcWrite(MOTOR_R_B, abs((float)json_document["args"]["right"])*65535);
      else 
        ledcWrite(MOTOR_R_F, 0);
        ledcWrite(MOTOR_R_B, 0);
    }
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
          char cmd[2048];
          client.read((uint8_t *)cmd, 1024);
          // Serial.println(cmd);
          deserializeJson(json_document, cmd);
          vTaskDelay(1);
        }
        vTaskDelay(1);
      }
      client.stop();
    }
    vTaskDelay(1);
  }
}

void wifi_init(bool ap) {
  
  // Serial.print("IP Address is: ");

  if(ap) {
    WiFi.softAP(ap_ssid, ap_pswd);
    IPAddress IP = WiFi.softAPIP();
    // Serial.println(IP);
  } else {
    WiFi.begin(ssid, pswd);

    while(WiFi.status() != WL_CONNECTED) {
      delay(1000);
      // Serial.println("Connecting to WiFi...");
    }
    // Serial.println(WiFi.localIP());
  }  
}