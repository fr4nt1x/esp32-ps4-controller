/*
 * HelTec Automation(TM) ESP32 Series Dev boards OLED draw Simple Function test code
 *
 * - Some OLED draw Simple Function function test;
 *
 * by LXYZN from HelTec AutoMation, ChengDu, China
 * 
 * www.heltec.cn
 *
 * this project also realess in GitHub:
 * https://github.com/HelTecAutomation/Heltec_ESP32
*/


// This example just provide basic function test;
// For more informations, please vist www.heltec.cn or mail to support@heltec.cn

#include "Arduino.h"
#include "heltec.h"
#include <ESP32Servo.h> 
#include <ps4.h>
#include <PS4Controller.h>
#include <ps4_int.h>

Servo myservo;  // create servo object to control a servo

// Possible PWM GPIO pins on the ESP32: 0(used by on-board button),2,4,5(used by on-board LED),12-19,21-23,25-27,32-33 
int servoPin = 2;      // GPIO pin used to connect the servo control (digital out)

int demoMode = 0;
int counter = 1;

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/, false /*LoRa use PABOOST*/);
  delay(300);
  Heltec.display -> clear();
  delay(100);
  PS4.begin("a8:3e:0e:fa:7c:e7");
  Heltec.display ->drawString(14,0,"Ready.");
  Heltec.display->display();
    // Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);// Standard 50hz servo
  myservo.attach(servoPin, 500, 2400);   // attaches the servo on servoPin to the servo object
                                         // using SG90 servo min/max of 500us and 2400us
                                         // for MG995 large servo, use 1000us and 2000us,
                                         // which are the defaults, so this line could be
                                         // "myservo.attach(servoPin);"

}
uint steering = 90;

void loop()
{
  Heltec.display -> clear();
    if (PS4.isConnected()){

      Heltec.display ->drawString(14,0,"Connected.");
    }
    else{
      Heltec.display ->drawString(14,0,"Disconnected.");
    }

    if (PS4.RStickX()) {
      steering = map(PS4.RStickX(),-128,127,50,150);
      
    }
    else{
        steering = 90;
    }
    myservo.write(steering);
  Heltec.display->display();
}