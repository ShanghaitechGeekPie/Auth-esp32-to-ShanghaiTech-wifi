#include <eduroam.h>

void connect_to_eduroam_task(void* void_edrp){
  const char* ssid = "eduroam";
  eduroam_recipe *edrp = (eduroam_recipe *)void_edrp;

  // WPA2 enterprise magic starts here
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)edrp->eduroam_id, strlen(edrp->eduroam_id));
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)edrp->eduroam_id, strlen(edrp->eduroam_id));
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)edrp->eduroam_password, strlen(edrp->eduroam_password));
  esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT();
  esp_wifi_sta_wpa2_ent_enable(&config);

  WiFi.begin(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
  }

  if(edrp->caller) xTaskNotifyGive(edrp->caller);
}


bool connect_to_eduroam(const char *eduroam_id, const char *eduroam_password){
  eduroam_recipe edrp = {eduroam_id, eduroam_password, NULL};
  connect_to_eduroam_task(&edrp);
  return true;
}


bool connect_to_eduroam(const char *eduroam_id, const char *eduroam_password, int ms_to_wait){
  TaskHandle_t edu_connect_task;
  TickType_t xTicksToWait = ms_to_wait / portTICK_PERIOD_MS;
  eduroam_recipe edrp = {eduroam_id, eduroam_password, xTaskGetCurrentTaskHandle()};

  xTaskCreate(connect_to_eduroam_task, "eduroam_connecting_task", 2048, &edrp, 0, &edu_connect_task);
  int success =  ulTaskNotifyTake(pdTRUE, xTicksToWait);
  Serial.println("notify get:");
  Serial.println(success);
  vTaskDelete(edu_connect_task);
  return (bool)success;
}