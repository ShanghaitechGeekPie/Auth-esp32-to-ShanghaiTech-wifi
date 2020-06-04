#ifndef ShanghaiTechWifiAuth_h
#define ShanghaiTechWifiAuth_h

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define CONTROLLER_ROOTCACERTIFICATE  "-----BEGIN CERTIFICATE-----\n\
MIIEPjCCAyagAwIBAgIESlOMKDANBgkqhkiG9w0BAQsFADCBvjELMAkGA1UEBhMC\n\
VVMxFjAUBgNVBAoTDUVudHJ1c3QsIEluYy4xKDAmBgNVBAsTH1NlZSB3d3cuZW50\n\
cnVzdC5uZXQvbGVnYWwtdGVybXMxOTA3BgNVBAsTMChjKSAyMDA5IEVudHJ1c3Qs\n\
IEluYy4gLSBmb3IgYXV0aG9yaXplZCB1c2Ugb25seTEyMDAGA1UEAxMpRW50cnVz\n\
dCBSb290IENlcnRpZmljYXRpb24gQXV0aG9yaXR5IC0gRzIwHhcNMDkwNzA3MTcy\n\
NTU0WhcNMzAxMjA3MTc1NTU0WjCBvjELMAkGA1UEBhMCVVMxFjAUBgNVBAoTDUVu\n\
dHJ1c3QsIEluYy4xKDAmBgNVBAsTH1NlZSB3d3cuZW50cnVzdC5uZXQvbGVnYWwt\n\
dGVybXMxOTA3BgNVBAsTMChjKSAyMDA5IEVudHJ1c3QsIEluYy4gLSBmb3IgYXV0\n\
aG9yaXplZCB1c2Ugb25seTEyMDAGA1UEAxMpRW50cnVzdCBSb290IENlcnRpZmlj\n\
YXRpb24gQXV0aG9yaXR5IC0gRzIwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEK\n\
AoIBAQC6hLZy254Ma+KZ6TABp3bqMriVQRrJ2mFOWHLP/vaCeb9zYQYKpSfYs1/T\n\
RU4cctZOMvJyig/3gxnQaoCAAEUesMfnmr8SVycco2gvCoe9amsOXmXzHHfV1IWN\n\
cCG0szLni6LVhjkCsbjSR87kyUnEO6fe+1R9V77w6G7CebI6C1XiUJgWMhNcL3hW\n\
wcKUs/Ja5CeanyTXxuzQmyWC48zCxEXFjJd6BmsqEZ+pCm5IO2/b1BEZQvePB7/1\n\
U1+cPvQXLOZprE4yTGJ36rfo5bs0vBmLrpxR57d+tVOxMyLlbc9wPBr64ptntoP0\n\
jaWvYkxN4FisZDQSA/i2jZRjJKRxAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAP\n\
BgNVHRMBAf8EBTADAQH/MB0GA1UdDgQWBBRqciZ60B7vfec7aVHUbI2fkBJmqzAN\n\
BgkqhkiG9w0BAQsFAAOCAQEAeZ8dlsa2eT8ijYfThwMEYGprmi5ZiXMRrEPR9RP/\n\
jTkrwPK9T3CMqS/qF8QLVJ7UG5aYMzyorWKiAHarWWluBh1+xLlEjZivEtRh2woZ\n\
Rkfz6/djwUAFQKXSt/S1mja/qYh2iARVBCuch38aNzx+LaUa2NSJXsq9rD1s2G2v\n\
1fN2D807iDginWyTmsQ9v4IbZT+mD12q/OWyFcq1rca8PdCE6OoGcrBNOTJ4vz4R\n\
nAuknZoh8/CbCzB428Hch0P+vGOaysXCHMnHjf87ElgI5rY97HosTvuDls4MPGmH\n\
VHOkc8KT/1EQrBVUAdj8BbGJoX90g5pJ19xOe4pIb4tF9g==\n\
-----END CERTIFICATE-----\n"

#define CONTROLLER_LOGIN_ENDPOINT "https://controller.shanghaitech.edu.cn:8445/PortalServer/Webauth/webAuthAction!login.action"
#define CONTROLLER_SYNC_ENDPOINT "https://controller.shanghaitech.edu.cn:8445/PortalServer/Webauth/webAuthAction!syncPortalAuthResult.action"
#define MAX_CONNECT_TIMEOUT 15
#define MAX_LOGIN_TRIES 15
#define MAX_SYNC_TRIES 15

enum controller_req_method{
  LOGIN, SYNC
};

/**
  * @brief  Connect to ShanghaiTech.
  * 
  * @attention 1. Your ShanghaiTech id & password MAY BE DIFFERENT w/ your eduroam password, egate password or GAuth password, be careful.
  * @attention 2. Log and error message will be printed if serial is opened.
  * @attention 3. DO CHECK connectivity after the task done, NO MATTER the auth succeeded or failed.
  * 
  * @param  shanghaitech_id: Your ShanghaiTech WiFi id, same as the one you use for ethernet and VPN(remote access).
  * @param  shanghaitech_password: Your ShanghaiTech WiFi password, same as the one you use for ethernet and VPN(remote access).
  * 
  * @return
  *    - true: Your board is connected and authed to ShanghaiTech WiFi.
  *    - false: Connection or Auth failed.
  */
bool connect_to_ShanghaiTech(String shanghaitech_id, String shanghaitech_password);

/**
  * @brief  Basic ShanghaiTech auth request
  * 
  * @param  method: LOGIN for the first request, SYNC for the following ones.
  * @param  shanghaitech_id: Your ShanghaiTech WiFi id, same as the one you use for ethernet and VPN(remote access).
  * @param  shanghaitech_password: Your ShanghaiTech WiFi password, same as the one you use for ethernet and VPN(remote access).
  * @param  JsonDoc: A StaticJsonDocument ptr, preallocated mem for response deserialization and sessioning.
  * 
  * @return
  *    - true: Request succeeded.
  *    - false: Request failed.
  */
bool ShanghaiTech_controller_req(controller_req_method method, String shanghaitech_id, String shanghaitech_password, DynamicJsonDocument* JsonDoc);

#endif
