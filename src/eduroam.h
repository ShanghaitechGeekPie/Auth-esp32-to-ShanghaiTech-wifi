#ifndef eduroam_h
#define eduroam_h

#include <WiFi.h>
#include "esp_wpa2.h"
#include "connectivity_util.h"

struct eduroam_recipe{
  const char *eduroam_id;
  const char *eduroam_password;
  TaskHandle_t caller;
};

/**
  * @brief  Basic eduroam connection task
  * 
  * @param  void_edac: An eduroam_account sturct ptr should be passed through this param.
  */
void connect_to_eduroam_task(void* void_edac);

/**
  * @brief  Connect to eduroam. (Blocking!)
  * 
  * @attention 1. The core you run this function on will be BLOCKED until eduroam connection established.
  * @attention 2. This function does NOT append "@shanghaitech.edu.cn" to eduroam_id for you, plz include it on your own.
  * @attention 3. Your eduroam password MAY BE DIFFERENT w/ your ShanghaiTech password, egate password or GAuth password, be careful.
  *
  * @param  eduroam_id: Your eduroam id, which is also your edu email address. 
  * @param  eduroam_password: Your eduroam password, which is also your edu email password.
  * 
  * @return
  *    - true: Your board is connected to eduroam
  */
bool connect_to_eduroam(const char *eduroam_id, const char *eduroam_password);

/**
  * @brief  Connect to eduroam. (Blocking but w/ timeout)
  * 
  * @attention 1. The core you run this function on will be BLOCKED until eduroam connection established.
  * @attention 2. This function does NOT append "@shanghaitech.edu.cn" to eduroam_id for you, plz include it on your own.
  * @attention 3. Your eduroam password MAY BE DIFFERENT w/ your ShanghaiTech password, egate password or GAuth password, be careful.
  *
  * @param  eduroam_id: Your eduroam id, which is also your edu email address. 
  * @param  eduroam_password: Your eduroam password, which is also your edu email password.
  * @param  timeout: Stop blocking after assgined timeout, in microseconds.
  *
  * @return
  *    - true: Your board is connected to eduroam
  *    - false: Timeout
  */
bool connect_to_eduroam(const char *eduroam_id, const char *eduroam_password, int timeout);

#endif