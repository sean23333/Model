#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#define IN1 A2  
#define IN2 A3  
#define ENA 9 
#define IN3 6  
#define IN4 5  
#define ENB 10 
#define IN5 A0   
#define IN6 A1    
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Servo M1;

RF24 radio(7, 8);
const byte address[6] = "00001";

struct Data_Package {
  byte xPotX;
  byte yPotY;
  byte r;
  byte p;
  byte buttonC;
  byte F;
};              

void setup() {

  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  M1.attach(3);
  
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN5,OUTPUT);
  pinMode(IN6,OUTPUT);
  
}
Data_Package data;


void loop() {
  int x;
  int y;
   if (radio.available()) {
      radio.read(&data, sizeof(Data_Package)); 
      if (data.yPotY>132){   
        digitalWrite(IN1,HIGH);  
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,HIGH);  
        digitalWrite(IN4,LOW);
        if (data.xPotX>132){
          analogWrite(ENA,0);
          analogWrite(ENB,255);
          }
        else if (data.xPotX<128){
          analogWrite(ENA,255);
          analogWrite(ENB,0);
          }
        else if (128<data.xPotX<132){
          digitalWrite(IN1,HIGH);  
          digitalWrite(IN2,LOW);
          digitalWrite(IN3,HIGH);  
          digitalWrite(IN4,LOW);
          analogWrite(ENA,255);
          analogWrite(ENB,255);
          }
        }
      else if (data.yPotY<120){   
        digitalWrite(IN1,LOW);  
        digitalWrite(IN2,HIGH);
        digitalWrite(IN3,LOW);  
        digitalWrite(IN4,HIGH);
        if (data.xPotX>132){
          analogWrite(ENA,255);
          analogWrite(ENB,0);
        }
        else if (data.xPotX<128){
          analogWrite(ENA,0);
          analogWrite(ENB,255);
        }
        else if (128<data.xPotX<132){
          digitalWrite(IN1,LOW);  
          digitalWrite(IN2,HIGH);
          digitalWrite(IN3,LOW);  
          digitalWrite(IN4,HIGH);
          analogWrite(ENA,255);
          analogWrite(ENB,255);
          }
        }
      else{
        if (data.xPotX>155){
          digitalWrite(IN1,LOW);  
          digitalWrite(IN2,HIGH);
          digitalWrite(IN3,HIGH);  
          digitalWrite(IN4,LOW);
          analogWrite(ENA,255);
          analogWrite(ENB,255);
          }
        else if (data.xPotX<100){
          digitalWrite(IN1,HIGH);  
          digitalWrite(IN2,LOW);
          digitalWrite(IN3,LOW);  
          digitalWrite(IN4,HIGH);
          analogWrite(ENA,255);
          analogWrite(ENB,255);
          }
        else {
          digitalWrite(IN1,LOW);  
          digitalWrite(IN2,LOW);
          digitalWrite(IN3,LOW);  
          digitalWrite(IN4,LOW);
          }  
        }  

    if (data.r > 200){   
        digitalWrite(IN5,HIGH);  
        digitalWrite(IN6,LOW); 
        }
    else if (data.r < 50){   
        digitalWrite(IN6,HIGH);  
        digitalWrite(IN5,LOW);
       }
    else if (50<data.r<200){
        digitalWrite(IN6,LOW);  
        digitalWrite(IN5,LOW);     
       }
    }
} 
