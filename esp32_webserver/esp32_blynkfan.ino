#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>


const char* ssid = "701";
const char* password = "11112222";


AsyncWebServer server(80);


#define UART_BUF_SIZE 128
char uartBuf[UART_BUF_SIZE];
int uartIndex = 0;


char lastTemp[32] = "";
char lastHum[32] = "";
char lastMotion[32] = "";
char lastLight[32] = "";
char lastFan[32] = "";

String htmlPage() {
  String page = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv='refresh' content='2'>
    <title>Fuzzy Logic Fan Control Monitor</title>
    <style>
      body {
        font-family: Arial, sans-serif;
        background: #f0f4f7;
        text-align: center;
        margin: 0;
        padding: 0;
      }
      h1 {
        background: #4CAF50;
        color: white;
        padding: 20px;
        margin: 0;
      }
      .container {
        display: flex;
        flex-wrap: wrap;
        justify-content: center;
        margin-top: 20px;
      }
      .card {
        background: white;
        box-shadow: 0 4px 8px rgba(0,0,0,0.1);
        border-radius: 12px;
        padding: 20px;
        margin: 10px;
        width: 220px;
        text-align: center;
      }
      .value {
        font-size: 22px;
        font-weight: bold;
        margin-top: 10px;
      }
      .temp   { color: #E91E63; }
      .hum    { color: #3F51B5; }
      .motion { color: #009688; }
      .light  { color: #673AB7; }
      .fan    { color: #FF9800; }
    </style>
  </head>
  <body>
    <h1>🌬️ Fuzzy Logic Fan Control Monitor</h1>
    <div class="container">
      <div class="card">
        <div>🌡 Temperature</div>
        <div class="value temp">)rawliteral" + String(lastTemp) + R"rawliteral(</div>
      </div>
      <div class="card">
        <div>💧 Humidity</div>
        <div class="value hum">)rawliteral" + String(lastHum) + R"rawliteral(</div>
      </div>
      <div class="card">
        <div>👤 Motion</div>
        <div class="value motion">)rawliteral" + String(lastMotion) + R"rawliteral(</div>
      </div>
      <div class="card">
        <div>💡 Light</div>
        <div class="value light">)rawliteral" + String(lastLight) + R"rawliteral(</div>
      </div>
      <div class="card">
        <div>💨 Fan PWM</div>
        <div class="value fan">)rawliteral" + String(lastFan) + R"rawliteral(</div>
      </div>
    </div>
  </body>
  </html>
  )rawliteral";

  return page;
}


void setup() {
  Serial.begin(115200);   
  Serial2.begin(115200, SERIAL_8N1, 16, 17);

 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected! IP: " + WiFi.localIP().toString());

  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", htmlPage());
  });

   
  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){
    String json = "{";
    json += "\"temp\":\""   + String(lastTemp)   + "\",";
    json += "\"hum\":\""    + String(lastHum)    + "\",";
    json += "\"motion\":\"" + String(lastMotion) + "\",";
    json += "\"light\":\""  + String(lastLight)  + "\",";
    json += "\"fan\":\""    + String(lastFan)    + "\"";
    json += "}";
    request->send(200, "application/json", json);
  });
  
  server.begin();
}

void loop() {
  while (Serial2.available()) {
    char c = Serial2.read();
    if (c == '\n' || uartIndex >= UART_BUF_SIZE - 1) {
      uartBuf[uartIndex] = '\0'; 
      uartIndex = 0;

      // Debug
      //Serial.println(uartBuf);

     
      if (strstr(uartBuf, "Temperature") != NULL) {
        strncpy(lastTemp, uartBuf, sizeof(lastTemp));
      } else if (strstr(uartBuf, "Humidity") != NULL) {
        strncpy(lastHum, uartBuf, sizeof(lastHum));
      } else if (strstr(uartBuf, "Motion") != NULL) {
        strncpy(lastMotion, uartBuf, sizeof(lastMotion));
      } else if (strstr(uartBuf, "Light") != NULL) {
        strncpy(lastLight, uartBuf, sizeof(lastLight));
      } else if (strstr(uartBuf, "Fan value") != NULL) {
        strncpy(lastFan, uartBuf, sizeof(lastFan));
      }

    } else {
      uartBuf[uartIndex++] = c;
    }
  }
}
