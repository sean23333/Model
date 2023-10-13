#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);
const byte address[6] = "00001";

int x = A1;
int y = A2;

int buttonC = 0;

struct Data_Package {
  byte xPotX;
  byte yPotY;
};                  

Data_Package data;

void setup() {
  Serial.begin(9600);
  pinMode (x, INPUT);
  pinMode (y, INPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
  delay(10);
  
  data.xPotX = 127; 
  data.yPotY = 127;
}

void loop() {
  data.xPotX = map(analogRead(A1), 0, 1023, 0, 255); 
  data.yPotY = map(analogRead(A2), 0, 1023, 0, 255);

  Serial.print("x: ");
  Serial.println(data.yPotY);
  
  radio.write(&data, sizeof(Data_Package));
}
