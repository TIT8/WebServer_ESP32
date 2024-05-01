#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

//Hardware
const int relay = 16;
const int pulse = 4;
volatile int state = LOW;
volatile int del = 500;     // it's really better with volatile?!

//Server
//const char* ssid = "Vodafone-35070320";
//const char* password = "pass";

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>Trevi</title>
    <meta name='viewport' content='width=device-width, initial-scale=1'>
</head>
<body>
    <h1>Electromagnet</h1>
    <div>
        <p>Inserire la frequenza</p>
        <form action="/freq" method="post">
            <input type="range" name="freq" min="10" max="1000" step="10" value="500">
            <input type="submit" name="sub">
        </form>
    </div>
</body>
</html>
)rawliteral";

AsyncWebServer server(80);

//Interrupt
void change_state()
{
  switch(state)
  {
    case LOW:
      state = HIGH;
      break;
    case HIGH:
      state = LOW;
      break;
  }
}

void setup() 
{
  pinMode(relay, OUTPUT);

  attachInterrupt(pulse, change_state, HIGH);
  Serial.begin(9600);

  /*
  if(!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  */

  WiFi.softAP("esp32");
  WiFi.softAPConfig(local_ip, gateway, subnet);

  /*
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());
  */

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send(200, "text/html", index_html);
  });
  server.on("/freq", HTTP_POST, [](AsyncWebServerRequest *request)
  {
    String req;
    if(request->hasArg("freq"))
    {
      req = request->arg("freq");
    }
    int val = atoi(req.c_str());
    if(val != 0)
    {
      del = val;
    }
    request->redirect("/");
  });
  /*
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css");
  });
  */
  server.begin();
}

void loop()
{
  if(state == HIGH)
  {
    digitalWrite(relay, HIGH);
    delay(del);
    digitalWrite(relay, LOW);
    delay(del);
  }
}
