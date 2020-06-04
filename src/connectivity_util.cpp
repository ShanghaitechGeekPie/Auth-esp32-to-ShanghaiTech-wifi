#include "connectivity_util.h"

bool check_internet_connectivity(){
  HTTPClient httpClient;

  httpClient.begin(INTERNET_CONNECTIVITY_CHECK_URL);
  int response_code = httpClient.GET();

  // TODO: provide more info in log if connection check fails
  return response_code == HTTP_CODE_OK;
}