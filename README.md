# Auth-esp32-to-ShanghaiTech-wifi
**Connect your esp32 board to ShanghaiTech WiFi or eduroam.**  

[![PlatformIO library registry](https://img.shields.io/badge/PIOlibrary-%237415-brightgreen)](https://platformio.org/lib/show/7415/ShanghaiTech%20WiFi%20Auth)  

## How to use
See examples for basic usage!  
| Function | for |
|  ----  | ----  |
| connect_to_ShanghaiTech() | SSID:ShanghaiTech authentication |
| connect_to_eduroam() | eduroam authentication |
| check_internet_connectivity() | simple connectivity check |

## Install
1. * **PlatformIO** - [ShanghaiTech WiFi Auth by Luxcoldury](https://platformio.org/lib/show/7415/ShanghaiTech%20WiFi%20Auth/installation)
   * 您亦可手动引入此library

2. 按需要引入头文件并调用相关函数，见examples文件夹内的样例  
   * ```#include <ShanghaiTechWifiAuth.h>``` 连接ShanghaiTech
   * ```#include <eduroam.h>``` 连接eduroam
   * ```#include <connectivity_util.h>``` 检查互联网连接
   
## Dependency
ArduinoJson  
