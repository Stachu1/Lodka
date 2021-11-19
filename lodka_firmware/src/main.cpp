#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>

// const char* ssid = "BSR - Uczniowie";
// const char* pswd = "bednarsk@";

const char* ssid = "esp-wifi";
const char* pswd = "esp-wifi";

WiFiServer server(80);

StaticJsonDocument<2048> json_document;


void server_loop(void * params);


void setup() {
  Serial.begin(9600);

  WiFi.softAP(ssid, pswd);
  IPAddress IP = WiFi.softAPIP();

  // WiFi.begin(ssid, pswd);

  // while(WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.println("Connecting to WiFi...");
  // }

  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());

  server.begin(); 

  xTaskCreate(server_loop, "Server loop", 4096, NULL, 0, NULL);
}

void loop() {
  
}

void server_loop(void * params) {
  for(;;) {
    WiFiClient client = server.available();
    if(client)
    {
      client.println("1111");
      while(client.connected())
      {
        while(client.available() > 0)
        {
          String cmd = client.readString();
          Serial.println(cmd);
        }
      }
      client.stop();
    }
    vTaskDelay(1);
  }
}