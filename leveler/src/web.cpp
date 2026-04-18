#include <WiFi.h>
#include <WebServer.h>
#include <Arduino.h>
#include"web.h"
#include<LittleFS.h>

WebServer server (80);

static void handleRoot();
static void handlelevel();
static void handleNotFound();

void web_init() {
  WiFi.softAP("Camper", "leveler");

  Serial.println("Access Point Started");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  if (!LittleFS.begin(true)) {
    Serial.println("LittleFS Mount Failed");
  }
  Serial.println("LittleFS mounted successfully");

  if (LittleFS.exists("/index.html")) {
    Serial.println("/index.html found");
  } else {
    Serial.println("/index.html not found");

  }

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
    File file = LittleFS.open("/index.html", "r");
    if (!file) {
        server.send(404, "text/plain", "index.html not found");
        return;
    }
    server.streamFile(file, "text/html");
    file.close();
    server.send(200, "text/plain", "Camper leveler root page");
}

static void handleStyle() {
    File file = LittleFS.open("/style.css", "r");
    if (!file) {
        server.send(404, "text/plain", "style.css not found");
        return;
    }
    server.streamFile(file, "text/css");
    file.close();
}

static void handleScript() {
    File file = LittleFS.open("/script.js", "r");
    if (!file) {
        server.send(404, "text/plain", "script.js not found");
        return;
    }
    server.streamFile(file, "application/javascript");
    file.close();
}





static void handlelevel() {
    server.send(200, "application/json", "{\"roll\":0.0,\"pitch\":0.0,\"yaw\":0.0,\"status\":\"ok\"}");

}

static void handleNotFound() {
    server.send(404, "text/plain", "Not Found");
}