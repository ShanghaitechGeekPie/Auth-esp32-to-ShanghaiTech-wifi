#include "connectivity_util.h"

int check_internet_connectivity(){
  HTTPClient httpClient;

  httpClient.begin(INTERNET_CONNECTIVITY_CHECK_URL);
  int response_code = httpClient.GET();

  return (response_code == 200) ? response_code : -response_code;
}