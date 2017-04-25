/*

 Version 1.0 - finally.
 
 August, 10   2016 - overflo
 complete rewrite for ESP8266 

 March 2017, finally found time to work on this again.
 Thanks to fbr's motivation and software support on the raspberry pi side.


needs the following libraries to compile

Arduino (1.8.1)
EP8266WiFi 1.0 
PubSubClient for MQTT support

SparkFun_MMA8452Q (https://github.com/sparkfun/SparkFun_MMA8452Q_Arduino_Library)
OneButton Library (https://github.com/mathertel/OneButton)

WiFiManager         //https://github.com/tzapu/WiFiManager
ArduinoJson       //https://github.com/bblanchon/ArduinoJson


///////////// REMARKS

The whole sound implementation relies on delay() and should therefor not be used DURING a game but only on init and end of a game when there are no sensor values to be read.
The same is true for most motor events



BUGS: 

Sometimes the accelerometer wont initialize.
The whole thing just hangs in there and does nothing.
This seems to be a hardware problem on the breakoutboard.
wontfix :(

--

the analogRead() in the battery chack breaks the setup.
might be a hardware issue due to a wrong voltage divider, needs investigation.



//TODOS

- find better accelerometer algorithm.
- get rid of all delay() uses and make everython based on callbacks / timers

*/


#include <ESP8266WiFi.h>
#include <Ticker.h>




// FOR MQTT but also used in wifiManager setup
//define your default values here, if there are different values in config.json, they are overwritten.
char mqtt_server[40];
char mqtt_port[5] = "1883";


char sysname[13] = {};



void setup()
{
  
  
    
  Serial.begin(115200);
  
  
  Serial.println("");
  Serial.println("<<< START >>>");

  battery_setup();
  
  createUniqueSystemName();

  motor_setup();   // ok

  button_setup(); //ok
  
  sound_setup(); //ok

  leds_setup();

  wifi_setup();
  
  mqtt_setup();

  accelerometer_setup();   // this breaks sometimes.. why? seems to be a hardware issue with the breakoutboard after several reeboots. usually everything works again after switching off the device for some time (over night)

  
  
}





void loop()
{

 battery_check();
  
 mqtt_work();




 button_work();
 leds_work();

 // maybe if we switch to asynchronous sound playback..
 //sound_work();
 
 // printOrientation();
  //  printAcceleration();

  accelerometer_work();



} 

