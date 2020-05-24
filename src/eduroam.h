#ifndef eduroam_h
#define eduroam_h

#include <WiFi.h>
#include "esp_wpa2.h"
// #include "esp_log.h"
// #include "connectivity.h"

void connect_to_eduroam(const char *eduroam_id, const char *eduroam_password);

#endif