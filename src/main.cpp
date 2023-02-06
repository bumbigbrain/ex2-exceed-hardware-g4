// If you want to run in WOKWi
// change pin and wifi

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "traffic.h"
#include <Arduino.h>
#include <Bounce2.h>
#define BUTTON 27
#define RED 26
#define YELLOW 25
#define GREEN 33
#define LDR 32





Bounce debouncer = Bounce();

int status_red = 0;
int status_green = 1;
int status_yellow = 0;
int check_ldr;

void Connect_Wifi();


void setup(){
    Connect_Wifi();
    Serial.begin(115200);
    debouncer.attach(BUTTON, INPUT_PULLUP);
    debouncer.interval(25); 
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    digitalWrite(GREEN, 1);

}


void loop(){
   

    if (status_green){
        digitalWrite(GREEN, 1);//GREEN ON
        //POST(codeกลุ่ม, GREEN)
        POST_traffic("GREEN");
        //GET(4, 5)
        GET_traffic();
        while(1){
            debouncer.update();
            if (debouncer.fell()){
                digitalWrite(GREEN, 0);
                digitalWrite(YELLOW, 1);//YELLOW ON
                //POST(codeกลุ่ม, YELLOW)
                POST_traffic("YELLOW");
                delay(8000);
                digitalWrite(YELLOW, 0);
                status_red = 1;
                status_green = 0;
                break;
            }
        }
    }else if (status_red){
       digitalWrite(RED, 1);//RED ON
       //POST(codeกลุ่ม, RED)
       POST_traffic("RED");
       //GET(4, 5)
       GET_traffic();
       delay(5000);
       while (1){
            check_ldr = analogRead(LDR);
            //Serial.println(check_ldr);
            if (check_ldr < 400){
                digitalWrite(RED, 0);
                status_green = 1;
                status_red = 0;
                break;
            }
       }
       
       


    }




}





void Connect_Wifi()
{
  const char *ssid = "Texxy";
  const char *password = "300300300";
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());
  Serial.println("----------------------------------");
}
