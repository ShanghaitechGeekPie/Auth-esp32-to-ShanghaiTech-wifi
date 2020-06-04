#include <ShanghaiTechWifiAuth.h>
#include <connectivity_util.h>

#define ShanghaiTech_ID "directing"
#define ShanghaiTech_PASSWORD "directing"

void setup() {
  Serial.begin(115200);
  delay(10);
  
  Serial.println("Try to connect to ShanghaiTech...");
  if(connect_to_ShanghaiTech(ShanghaiTech_ID, ShanghaiTech_PASSWORD)){
    Serial.println("ShanghaiTech connected and authed! Check Internet connectivity:"); 
  }else{
    Serial.println("ShanghaiTech connecting or auth failed. See log above."); 
  }

  if(check_internet_connectivity()){
    Serial.println("Your esp32 is checked to have a POSITIVE Internet connectivity!");
  }else{
    Serial.println("Your esp32 is checked to have a NEGATIVE Internet connectivity!");
  }
}

void loop(){

}