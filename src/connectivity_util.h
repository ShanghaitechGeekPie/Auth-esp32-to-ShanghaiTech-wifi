#ifndef connecticity_util_h
#define connecticity_util_h

#include <HTTPClient.h>

#define INTERNET_CONNECTIVITY_CHECK_URL "http://wap.baidu.com/" // Should be an http site. Slash at the end should not be omitted.

/**
  * @brief  Check Internet connectivity against an http site.
  *
  * @return
  *    - true: Your board is connected to Internet
  *    - false: Connectivity seems not present
  */
bool check_internet_connectivity();

#endif