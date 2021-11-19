#include <Arduino.h>
#include <WiFi.h>

// const char* ssid = "BSR - Uczniowie";
// const char* pswd = "bednarsk@";

const char* ssid = "esp-wifi";
const char* pswd = "esp-wifi";

WiFiServer server(80);

struct
{
  bool foreward, backward, left, right;
}steering;

void setup() {
  Serial.begin(9600);

  // WiFi.softAP(ssid, pswd);
  // IPAddress IP = WiFi.softAPIP();

  WiFi.begin(ssid, pswd);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());

  server.begin();
  
}

void loop() {
  WiFiClient client = server.available();
  if(client)
  {
    while(client.connected())
    {
      while(client.available() > 0)
      {
        String cmd = client.readStringUntil('e');
        // Serial.println(cmd);
        const char* cCmd = cmd.c_str();

        if(cCmd[0] == 'S') steering.backward = true;
        if(cCmd[0] == 's') steering.backward = false;

        if(cCmd[0] == 'W') steering.foreward = true;
        if(cCmd[0] == 'w') steering.foreward = false;

        if(cCmd[0] == 'A') steering.left = true;
        if(cCmd[0] == 'a') steering.left = false;

        if(cCmd[0] == 'D') steering.right = true;
        if(cCmd[0] == 'd') steering.right = false;  
      }
      if(steering.backward)
        Serial.print("F");      
      else
        Serial.print("f");
      if(steering.backward)
        Serial.print("B");
      else
        Serial.print("b");
      if(steering.left)
        Serial.print("L");
      else
        Serial.print("l");
      if(steering.right)
        Serial.print("R");
      else
        Serial.print("r");
      Serial.print("\n");
    }
    client.stop();
  }
}