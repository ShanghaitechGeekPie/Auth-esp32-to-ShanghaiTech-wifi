#include <eduroam.h>

#define eduroam_ID "YourShanghaiTechEmailAddress"
#define eduroam_PASSWORD "YourShanghaiTechEmaillPassword"
#define Wait_Time_in_Microseconds 2000

void setup() {
  Serial.begin(115200);
  delay(10);
  
  Serial.print("Try to connect to eduroam in ");
  Serial.print(Wait_Time_in_Microseconds);
  Serial.println("ms:");
  if(connect_to_eduroam(eduroam_ID, eduroam_PASSWORD, Wait_Time_in_Microseconds)){
    Serial.println("Eduroam connected! Check Internet connectivity:"); 
    if(check_internet_connectivity()){
      Serial.println("Your esp32 is checked to have a POSITIVE Internet connectivity!");
    }else{
      Serial.println("Your esp32 is checked to have a NEGATIVE Internet connectivity!");
    }
  }else{
    Serial.println("Timeout!"); 
  }
  
}

void loop(){

}