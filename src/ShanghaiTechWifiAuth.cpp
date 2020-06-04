#include <ShanghaiTechWifiAuth.h>

bool connect_to_ShanghaiTech(String shanghaitech_id, String shanghaitech_password){
  DynamicJsonDocument JsonDoc(1500);

  WiFi.disconnect(true);
  WiFi.begin("ShanghaiTech");

  int trial_counter = 0;
  Serial.println("[ShanghaiTechWifiAuth]Info: Connect to SSID:ShanghaiTech...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    trial_counter++;
    if(trial_counter>MAX_CONNECT_TIMEOUT){
      Serial.println("[ShanghaiTechWifiAuth]Connection failed: Timeout");
      return false;
    }
  }

  trial_counter = 0;
  Serial.println("[ShanghaiTechWifiAuth]Info: send login request to controller...");
  while(!ShanghaiTech_controller_req(LOGIN, shanghaitech_id, shanghaitech_password, &JsonDoc)){
    trial_counter++;
    Serial.printf("[ShanghaiTechWifiAuth]Auth failed: Error occured during login request trial #%d\n", trial_counter);
    if(trial_counter>=MAX_LOGIN_TRIES){
      Serial.println("[ShanghaiTechWifiAuth]Auth failed: Max login tries exceeded");
      return false;
    }
    delay(1000);
  }

  if(JsonDoc["data"]["statusCode"]!=1000){
    String errormsg = JsonDoc["message"];
    Serial.printf("[ShanghaiTechWifiAuth]Auth failed, msg from ShanghaiTech controller: %s\n", errormsg.c_str());
    return false;
  }

  trial_counter = 0;
  Serial.println("[ShanghaiTechWifiAuth]Info: Check login result...");
  while(1){
    delay(1000);
    trial_counter++;
    if(!ShanghaiTech_controller_req(SYNC, shanghaitech_id, shanghaitech_password, &JsonDoc)){
      Serial.printf("[ShanghaiTechWifiAuth]Auth failed: Error occured during sync request #%d\n", trial_counter);
    }else{
      if(JsonDoc["data"]["portalAuthStatus"]==1){
        Serial.println("[ShanghaiTechWifiAuth]Auth succeeded!");
        return true;
      }
    }
    if(trial_counter>=MAX_SYNC_TRIES){
      Serial.println("[ShanghaiTechWifiAuth]Auth failed: Max sync tries exceeded");
      return false;
    }
    Serial.println("[ShanghaiTechWifiAuth]Info: Still checking...");
  }
}

bool ShanghaiTech_controller_req(controller_req_method method, String shanghaitech_id, String shanghaitech_password, DynamicJsonDocument* JsonDoc){
  String httpRequestData;
  String endpoint;
  if(method==LOGIN){
    endpoint = CONTROLLER_LOGIN_ENDPOINT;
    httpRequestData = "userName=" + shanghaitech_id + "&password=" + shanghaitech_password + "&hasValidateCode=false";
  }else if(method==SYNC){
    endpoint = CONTROLLER_SYNC_ENDPOINT;
    String ip = (*JsonDoc)["data"]["ip"];
    httpRequestData = "clientIp=" + ip + "&browserFlag=zh_CN";
  }

  WiFiClientSecure *client = new WiFiClientSecure;
  if(!client) {
    Serial.println("[ShanghaiTechWifiAuth]Error: Unable to create WiFiClientSecure");
    return false;
  }
  client -> setCACert(CONTROLLER_ROOTCACERTIFICATE);
  { // scope for GC
  HTTPClient https;
  if (!https.begin(*client, endpoint)) {
    Serial.println("[ShanghaiTechWifiAuth]Error: Unable to begin HTTPS connection");
    delete client;
    return false;
  }
  https.addHeader("Content-Type","application/x-www-form-urlencoded");
  if (method==SYNC){
    String sessionid = (*JsonDoc)["data"]["sessionId"];
    String cookie = "JSESSIONID=" + sessionid;
    https.addHeader("Cookie",cookie);
  }
  int httpCode = https.POST(httpRequestData);
  if (httpCode != HTTP_CODE_OK) {
    Serial.printf("[ShanghaiTechWifiAuth]Error: HTTPS POST failed, error: %s\n", https.errorToString(httpCode).c_str());
    delete client;
    return false;
  }
  String payload = https.getString();
  DeserializationError error = deserializeJson(*JsonDoc, payload);
  if (error) {
    Serial.printf("[ShanghaiTechWifiAuth]Error: deserializeJson failed: %s\n", error.c_str());
    delete client;
    return false;
  }
  https.end();
  }
  delete client;
  return true;
}