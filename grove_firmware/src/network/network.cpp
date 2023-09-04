#include "network.h"

DNSServer dnsServer;
AsyncWebServer server(80);

NetworkClass *net_instances;

NetworkClass::NetworkClass(){
  net_instances = this;
}

void NetworkClass::setupServer(){
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/html", index_html); 
      debug(NET_TAG, "Client Connected");
  });
    
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
      String inputMessage;
      String inputParam;
  
      if (request->hasParam("ssid")) {
        inputMessage = request->getParam("ssid")->value();
        inputParam = "ssid";
        net_instances->ssid = inputMessage;
        data.saveAt("ssid", net_instances->ssid);
        debugVal(NET_TAG, "SSID : ", net_instances->ssid);
      }

      if (request->hasParam("password")) {
        inputMessage = request->getParam("password")->value();
        inputParam = "password";
        net_instances->pass = inputMessage;
        data.saveAt("pass", net_instances->pass);
        debugVal(NET_TAG, "Password : ", net_instances->pass);
      }
      request->send(200, "text/html", "The values entered by you have been successfully sent to the device <br><a href=\"/\">Return to Home Page</a>");
      debug(NET_TAG, "SSID obtained!");
      net_instances->_connection_status = true;
      server.end();
  });
}

void NetworkClass::connect(String ssid, String pass){
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  debugVal(NET_TAG, "Connecting to ", data.read("ssid"));
  WiFi.begin(ssid.c_str(), pass.c_str());
}

void NetworkClass::reset(){
  debug(NET_TAG, "Network data reset");
  data.format();
}

bool NetworkClass::get_status(){
  if(WiFi.status() == WL_CONNECTED){
    return true;
  } else{
    return false;
  }
}

void NetworkClass::begin(){
  unsigned long print = millis();
  if(data.read("ssid")==""){
    String ap = DEFAULT_AP_SSID;
    net_instances->reconnect(ap);
    while(!net_instances->_connection_status){
      dnsServer.processNextRequest();
      if(millis() - print > 1000){
        Serial.print("-");
        print = millis();
      }
    }
    Serial.print("");
  } else{
    debug(NET_TAG, "Data acquired");
    net_instances->ssid = data.read("ssid");
    net_instances->pass = data.read("pass");
  }

  net_instances->connect(net_instances->ssid, net_instances->pass);

  uint8_t connect_chance = 30;
  while (!net_instances->get_status()){
    if(millis() - print > 1000){
      Serial.print(".");
      print = millis();
      connect_chance--;
      if(connect_chance < 1){
        debug(NET_TAG, "WiFi not found!");
        data.format();
        debug(NET_TAG, "Restarting...");
        ESP.restart();
      }
    }
  }
  ntp.begin();
  debug(NET_TAG, ntp.get_time());
  Serial.println("");
  debug(NET_TAG, "Connected!");
}

void NetworkClass::reconnect(String ap_name){
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_name.c_str());
  debugVal(NET_TAG, "AP IP address: ", WiFi.softAPIP());
  net_instances->setupServer();
  debug(NET_TAG, "Starting DNS Server");
  dnsServer.start(53, "*", WiFi.softAPIP());
  server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);//only when requested from AP
  //more handlers...
  server.begin();
}

String NetworkClass::get_ssid(){
    return net_instances->ssid;
}

String NetworkClass::get_ip(){
    return WiFi.localIP().toString();
}

NetworkClass net;