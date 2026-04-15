#include <WiFi.h>
#include <WebServer.h>
#include <Arduino.h>
#include"web.h"


WebServer server (80);

static void handleRoot();
static void handlelevel();
static void handleNotFound();

void web_init() {
  WiFi.softAP("Camper", "leveler");
  
  Serial.println("Access Point Started");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/level", HTTP_GET, handlelevel);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("web server started");
}

void web_update() {
    server.handleClient();
}

static void handleRoot() {
    server.send(200, "text/plain", "Camper leveler root page");

}

static void handlelevel() {
    server.send(200, "application/json", "{\"roll\":0.0,\"pitch\":0.0,\"yaw\":0.0,\"status\":\"ok\"}");

}

static void handleNotFound() {
    server.send(404, "text/plain", "Not Found");
}