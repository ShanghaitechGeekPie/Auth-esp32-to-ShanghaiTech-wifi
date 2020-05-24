#include <eduroam.h>

void connect_to_eduroam(const char *eduroam_id, const char *eduroam_password){
  const char* ssid = "eduroam";

  // WPA2 enterprise magic starts here
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)eduroam_id, strlen(eduroam_id));
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)eduroam_id, strlen(eduroam_id));
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)eduroam_password, strlen(eduroam_password));
  esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT();
  esp_wifi_sta_wpa2_ent_enable(&config);

  WiFi.begin(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
  }
}