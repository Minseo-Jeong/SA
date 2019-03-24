
#include <Arduino.h>

// Include application, user and local libraries
#include "SPI.h"
#include "TFT_22_ILI9225.h"
#include "SoftwareSerial.h"
#include <FanController.h>

#define SENSOR_PIN 2
#define SENSOR_THRESHOLD 1000

FanController fan(SENSOR_PIN, SENSOR_THRESHOLD);

#define TFT_RST 8                                                                                                                                                                                                                                                                                                                                                                             
#define TFT_RS  9
#define TFT_CS  53  // SS
#define TFT_SDI 51  // MOSI
#define TFT_CLK 52  // SCK
#define TFT_LED 3   

#define pwmFan 10

TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED);

//int Vo = A0;
//int V_LED = 2;
//
//float Vo_value = 0;
//float Voltage = 0;
//float dustDensity = 0;
//float dustCleanVoltage = 0.44;
//int samplingTime = 280;
//int deltaTime = 40;
//int sleepTime = 9680;
//
//int checkDust(){
//  digitalWrite(V_LED,LOW); //ired 'on'
//    delayMicroseconds(samplingTime);
//    Vo_value = analogRead(Vo); //read the dust value
//    delayMicroseconds(deltaTime);// pulse width 0.32 - 0.28 = 0.04 msec
//    //0.32 msec의 펄스폭을 유지하기 위해 필요한 코드입니다
//
//    digitalWrite(V_LED,HIGH); //ired 'off'
//    delayMicroseconds(sleepTime);
//
//
//    /*
//    이 센서의 출력전압(Vo)는 먼지가 없을 때의 출력전압(Voc)과 먼지 농도(ΔV)에 비례하여 출력됩니다.
//    다시 표현하면 ΔV = Vo – Voc
//    미세먼지 농도[µg/m³] = (Vo – Voc) / 0.005
//    */
//    Voltage = Vo_value * (5.0 / 1024.0);
//
//    dustDensity = (Voltage - dustCleanVoltage)/0.005;
//
//    // Serial.print(" Raw Signal Value (0-1023):");
//    // Serial.print(Vo_value);
//    // Serial.print(" | Volatage:");
//    // Serial.print(Voltage);
//    // Serial.print(" | Dust Density:");
//    // Serial.print(dustDensity);
//    // Serial.print("[ug/m3]");
//
//    return dustDensity;
//
//}

int Vo = A0;
int V_LED = 3;

float Vo_value = 0;
float Voltage = 0;
float dustDensity = 0;
float dustCleanVoltage = 0.44;
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

int checkDust(){
  digitalWrite(V_LED,LOW); //ired 'on'
delayMicroseconds(samplingTime);
Vo_value = analogRead(Vo); //read the dust value
delayMicroseconds(deltaTime);// pulse width 0.32 - 0.28 = 0.04 msec
//0.32 msec의 펄스폭을 유지하기 위해 필요한 코드입니다

digitalWrite(V_LED,HIGH); //ired 'off'
delayMicroseconds(sleepTime);


/*
이 센서의 출력전압(Vo)는 먼지가 없을 때의 출력전압(Voc)과 먼지 농도(ΔV)에 비례하여 출력됩니다.
다시 표현하면 ΔV = Vo – Voc
미세먼지 농도[µg/m³] = (Vo – Voc) / 0.005
*/
Voltage = Vo_value * (5.0 / 1024.0);

dustDensity = (Voltage - dustCleanVoltage)/0.005;

//Serial.print(" Raw Signal Value (0-1023):");
//Serial.print(Vo_value);
//Serial.print(" | Volatage:");
//Serial.print(Voltage);
//Serial.print(" | Dust Density:");
//Serial.print(dustDensity);
//Serial.print("[ug/m3]");

return dustDensity;

}

void CH_Level0(float density){
    if(density < 20 ){
       CH_Level1();
        analogWrite(pwmFan,100);
    }
    else if(density < 40){
       CH_Level2();
        analogWrite(pwmFan,150);
    }
    else if(density < 80){
       CH_Level3();
        analogWrite(pwmFan,200);
    }
    else{
       CH_Level4();
        analogWrite(pwmFan,255);
    }
}

void CH_Level1(){
  RM_Level2();
  RM_Level3();
  RM_Level4();
}

void CH_Level2(){
//   analogWrite(pwmFan,150);
  for(int i = 150; i <= 212; i++){
    for(int j = 132; j <= 146; j++){
      tft.drawPixel(i , j , COLOR_YELLOW);
    }
  }
  RM_Level3();
  RM_Level4();
}

void RM_Level2(){
  for(int i = 150; i <= 212; i++){
    for(int j = 132; j <= 146; j++){
      tft.drawPixel(i , j , COLOR_BLACK);
    }
  }
}

void drawLevel2(){
  for(int i = 150; i <= 212; i++){
    for(int j = 132; j <= 146; j++){
      tft.drawPixel(i , j , COLOR_YELLOW);
    }
  }
}

void drawLevel3(){
  for(int i = 150; i <= 212; i++){
    for(int j = 114; j <= 128; j++){
      tft.drawPixel(i , j , COLOR_ORANGE);
    }
  }
}

void CH_Level3(){
//   analogWrite(pwmFan,200);
   for(int i = 150; i <= 212; i++){
    for(int j = 114; j <= 128; j++){
      tft.drawPixel(i , j , COLOR_ORANGE);
    }
  }
  RM_Level4();
  drawLevel2();
}

void RM_Level3(){
  for(int i = 150; i <= 212; i++){
    for(int j = 114; j <= 128; j++){
      tft.drawPixel(i , j , COLOR_BLACK);
    }
  }
}

void CH_Level4(){
  analogWrite(pwmFan,255);
  for(int i = 150; i <= 212; i++){
    for(int j = 96; j <= 110; j++){
      tft.drawPixel(i , j , COLOR_RED);
    }
  }
  drawLevel2();
  drawLevel3();
}

void RM_Level4(){
  for(int i = 150; i <= 212; i++){
    for(int j = 96; j <= 110; j++){
      tft.drawPixel(i , j , COLOR_BLACK);
    }
  }
}

void draw_AUTO(){
  tft.drawText(10,150, "AUTO",COLOR_GREEN);
}

void rm_AUTO(){
  tft.drawText(10,150, "AUTO",COLOR_BLACK);
}

void draw_Density(float density){
  String dens;
  tft.setFont(Terminal12x16);
  dens = String(density)+"ug/m^3";
  tft.drawText(22, 10, dens);
}

int sw = 1;
bool cls = 1;
void setup(){
  
 Serial.begin(9600);
 fan.begin();

/*digital output:*/
  pinMode(V_LED, OUTPUT);
   tft.begin();
//  Serial.begin(9600);
//  BT.begin(9600);
  pinMode(V_LED, OUTPUT);
  pinMode(Vo,INPUT);
  tft.setOrientation(1);
  pinMode(6,OUTPUT);
//  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM00); 
//   TCCR0B = _BV(CS00); /* uno register*/

   TCCR2B = TCCR2B & 0b11111000 | 0x01;

/*analog input:*/

  for(int i = 150; i <= 212; i++){
    for(int j = 150; j <= 164; j++){
      tft.drawPixel(i , j , COLOR_GREEN);
    }
  }
}

void loop() {
    float inpdens = 0.0;
    uint8_t BTN = 0;
    int ds_md= 0;
    int density;

    int avr = 0;

//    if(BT.available()){
//        BTN = BT.read();
//        if(BTN == 0)
//            sw = 1;
//    }

    uint8_t  mapPot_Change, BTData = 0,mapPot;
//    uint8_t mapPot = map(analogRead(A1), 0, 1023, 0, 4);
//    uint8_t mapPot = analogRead(A1)/205;
    if(analogRead(A1)<190)
      mapPot = 0;
    else if(analogRead(A1)<380)
      mapPot = 1;
    else if(analogRead(A1)<570)
      mapPot = 2;
    else if(analogRead(A1)<760)
      mapPot = 3;
    else
      mapPot = 4;
    
    // delay(100);
//     mapPot_Change = map(analogRead(A1), 0, 1023, 0, 4);
//    //Serial.println(mapPot);
//    if(mapPot == 0)
//        sw = 1;
//    else
//      sw = 0;
//
      for(int i = 0;i< 20; i++){
        avr += checkDust();

        //Serial.println(avr);
        delay(1);
      }
      density = avr/20;
      draw_Density(density);
      //Serial.println(density);

    //-------------------------------------------------------------------------------------------------------
    //미세먼지 농도 RGB표시 
    if(density < 20 ){
      tft.fillCircle(12, 16, 5, COLOR_GREEN);
    }
    else if(density < 40){
      tft.fillCircle(12, 16, 5, COLOR_YELLOW);
    }
    else if(density < 80){
      tft.fillCircle(12, 16, 5, COLOR_ORANGE);
    }
    else{
      tft.fillCircle(12, 16, 5, COLOR_RED);
    }
    //-------------------------------------------------------------------------------------------------------

//    Serial.println(mapPot);
    
    switch(mapPot){
     
        case 0 : CH_Level0(density);break;
        case 1 : CH_Level1();analogWrite(pwmFan,100);break;
        case 2 : CH_Level2();analogWrite(pwmFan,150);break;
        case 3 : CH_Level3();analogWrite(pwmFan,200);break;
        case 4 : CH_Level4();analogWrite(pwmFan,255);break;
    }

    unsigned int rpms = fan.getSpeed(); // Send the command to get RPM
//  Serial.print(rpms);
//  Serial.println("RPM");
  String RPM = String(rpms)+"RPM";
//  Serial.println(RPM);
  tft.drawText(17,50,RPM);
    if(!mapPot){
      draw_AUTO();
      if(cls){
        RM_Level2();
        RM_Level3();
        RM_Level4();
        cls = 0;
      }
    }
      
    else{
      rm_AUTO();
      cls = 1;
    }
      


    
}