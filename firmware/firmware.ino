#include <WiFi.h>

const char* ssid = "BSR - Elektroniczna";
const char* pswd = "realnywarsztat";

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
        Serial.println(cmd);
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
    }
    client.stop();
  }
}