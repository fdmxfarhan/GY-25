#include <Adafruit_SH1106_STM32.h>
Adafruit_SH1106 display(-1);
int buff[8];
int counter = 0;
int GY;

void setup() {
  display.begin(0x2, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  delay(500);
  display.display();
  delay(500); 
  Serial.begin(115200);
  Serial.write(0XA5);
  Serial.write(0X54);
  delay(500);
  Serial.write(0XA5);
  Serial.write(0X51);
}

void loop() {
  if(digitalRead(PB5)){
    Serial.write(0XA5);
    Serial.write(0X55);
    while(digitalRead(PB5));
  }
  Serial.write(0XA5);
  Serial.write(0X51);
  while (true) {   
    buff[counter] = Serial.read();
    if(counter == 0 && buff[0] != 0xAA) break;
    counter++;       
    if(counter==8)
    {   
    counter=0;                 
    if(buff[0]==0xAA && buff[7]==0x55)
      {         
       GY=(int16_t)(buff[1]<<8|buff[2])/100.00; 
      } 
    }    
  }
  display.clearDisplay();
  ///////////////////-----GY-25
  display.setCursor(40,0);
  display.print("GY:");
  display.print(GY);
  display.display();
}
