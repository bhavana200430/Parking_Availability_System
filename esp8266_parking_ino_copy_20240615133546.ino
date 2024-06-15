#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// WiFi credentials
const char* ssid = "OnePlus Nord";
const char* password = "t356zcua";

// Slot sensor IR pin definitions
const int slotSensorPins[] = {D1, D6}; // IR sensors connected to D1 and D6
const int numSensors = 2;
bool slotOccupied[numSensors];

// Web server on port 80
ESP8266WebServer server(80);

void handleRoot() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>Parking System</title>";
  html += "<style>";
  html += "body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; margin: 0; padding: 0; background-color: #f0f0f0; background-image: url('https://cdnb.artstation.com/p/assets/images/images/009/771/777/large/hoshino-yu-x-oidikgoir51vec9jho1-r2-1280.jpg?1520824413'); }";
  html += ".container { max-width: 800px; padding: 20px; background-color: #fff; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); border-radius: 8px; margin: 20px auto; }";
  html += "h1 { text-align: center; color: #333; }";
  html += ".slots { display: grid; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); gap: 10px; }";
  html += ".slot { padding: 15px; border-radius: 5px; box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1); display: flex; justify-content: space-between; align-items: center; font-size: 18px; background-color: #c8e6c9; }";
  html += ".slot.occupied { background-color: #ffcdd2; }";
  html += ".slot span:first-child { font-weight: bold; }";
  html += "button { margin: 10px; padding: 12px 20px; font-size: 16px; background-color: #4caf50; color: #fff; border: none; border-radius: 5px; cursor: pointer; transition: background-color 0.3s ease; }";
  html += "button:hover { background-color: #45a049; }";
  html += "</style>";
  html += "</head><body>";
  html += "<div class='container'>";
  html += "<h1>Parking System</h1>";
  html += "<div class='slots' id='slots-container'></div>";
  html += "<button onclick='controlBarrier(\"open\")'>Open Barrier</button>";
  html += "<button onclick='controlBarrier(\"close\")'>Close Barrier</button>";
  html += "</div>";
  html += "<script>";
  html += "function fetchData() { fetch('/status').then(response => response.json()).then(data => { const slotsContainer = document.getElementById('slots-container'); slotsContainer.innerHTML = ''; data.forEach((occupied, index) => { const slotDiv = document.createElement('div'); slotDiv.classList.add('slot', occupied ? 'occupied' : 'free'); slotDiv.innerHTML = `<span>Slot ${index + 1}</span><span>${occupied ? 'Occupied' : 'Free'}</span>`; slotsContainer.appendChild(slotDiv); }); }); }";
  html += "function controlBarrier(action) { fetch('/' + action); }";
  html += "setInterval(fetchData, 1000); fetchData();";
  html += "</script>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleStatus() {
  String json = "[";
  for (int i = 0; i < numSensors; i++) {
    json += slotOccupied[i] ? "true" : "false";
    if (i < numSensors - 1) json += ",";
  }
  json += "]";
  server.send(200, "application/json", json);
}

void handleOpen() {
  // Code to open barrier goes here
  server.send(200, "text/plain", "Barrier opened");
}

void handleClose() {
  // Code to close barrier goes here
  server.send(200, "text/plain", "Barrier closed");
}

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi.");
  int maxRetries = 20; // Set a limit for retries
  int retryCount = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    retryCount++;
    if (retryCount >= maxRetries) {
      Serial.println("Failed to connect to WiFi. Please check your credentials.");
      return;
    }
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize slot sensors (mocked for example)
  // You should adapt this part according to your actual sensor logic
  pinMode(D1, INPUT);
  pinMode(D6, INPUT);

  // Initialize web server
  server.on("/", HTTP_GET, handleRoot);
  server.on("/status", HTTP_GET, handleStatus);
  server.on("/open", HTTP_GET, handleOpen);
  server.on("/close", HTTP_GET, handleClose);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Mocking sensor data (replace with actual sensor reading logic)
  slotOccupied[0] = digitalRead(D1) == LOW; // LOW indicates occupied
  slotOccupied[1] = digitalRead(D6) == LOW; // LOW indicates occupied

  // Handle web server
  server.handleClient();
}
