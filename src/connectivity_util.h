#ifndef connecticity_util_h
#define connecticity_util_h

#include <HTTPClient.h>
// #include "esp_log.h"

#define INTERNET_CONNECTIVITY_CHECK_URL "http://wap.baidu.com/" // Should be an http site. Slash at the end should not be omitted.

/**
  * @brief  Check Internet connectivity against an http site.
  *
  * @return
  *    - 200: Your board is connected to Internet
  *    - <0: Negated response code in the case of connectivity error
  */
int check_internet_connectivity();

#endif