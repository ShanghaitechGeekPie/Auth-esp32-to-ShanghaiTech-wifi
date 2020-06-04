#include <eduroam.h>

#define eduroam_ID "YourShanghaiTechEmailAddress"
#define eduroam_PASSWORD "YourShanghaiTechEmaillPassword"

void setup() {
  Serial.begin(115200);
  delay(10);
  
  Serial.println("Try to connect to eduroam:");
  connect_to_eduroam(eduroam_ID, eduroam_PASSWORD);
  Serial.println("Eduroam connected! Check Internet connectivity:");
  if(check_internet_connectivity()){
    Serial.println("Your esp32 is checked to have a POSITIVE Internet connectivity!");
  }else{
    Serial.println("Your esp32 is checked to have a NEGATIVE Internet connectivity!");
  }
}

void loop(){

}