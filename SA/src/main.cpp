#include <Arduino.h>

// Include application, user and local libraries
#include "SPI.h"
#include "TFT_22_ILI9225.h"

#define TFT_RST 8
#define TFT_RS  9
#define TFT_CS  10  // SS
#define TFT_SDI 11  // MOSI
#define TFT_CLK 13  // SCK
#define TFT_LED 3   // 0 if wired to +5V directly
//#endif

// Use hardware SPI (faster - on Uno: 13-SCK, 12-MISO, 11-MOSI)
TFT_22_ILI9225 tft = TFT_22_ILI9225(TFT_RST, TFT_RS, TFT_CS, TFT_LED);

/*
 * Tux black/white image in 180x220 converted using Ardafruit bitmap converter
 * https://github.com/ehubin/Adafruit-GFX-Library/tree/master/Img2Code
 */

void draw_AUTO(){
  tft.drawText(10,150, "AUTO",COLOR_GREEN);
}

void rm_AUTO(){
  tft.drawText(10,150, "AUTO",COLOR_BLACK);
}

// void drawRec(int x,int y, int rangeX, int rangeY){
//   for(int i = x; i <= x + rangeX; i++){
//     for(int j = y; j <= y + rangeY; j++){
//       tft.drawPixel(i , j , COLOR_RED);
//     }
//   }
// }

void drawRec_G(){
  for(int i = 150; i <= 212; i++){
    for(int j = 150; j <= 164; j++){
      tft.drawPixel(i , j , COLOR_GREEN);
    }
  }
}

void drawRec_Y(){
  for(int i = 150; i <= 212; i++){
    for(int j = 132; j <= 146; j++){
      tft.drawPixel(i , j , COLOR_YELLOW);
    }
  }
}

void drawRec_O(){
  for(int i = 150; i <= 212; i++){
    for(int j = 114; j <= 128; j++){
      tft.drawPixel(i , j , COLOR_ORANGE);
    }
  }
}

void drawRec_R(){
  for(int i = 150; i <= 212; i++){
    for(int j = 96; j <= 110; j++){
      tft.drawPixel(i , j , COLOR_RED);
    }
  }
}

bool changeAuto = true;

void setup() {
  tft.begin();
  Serial.begin(9600);
  tft.setOrientation(1);
}

// Loop
void loop() {

  uint8_t mapPot = map(analogRead(A0), 0, 1023, 0, 4), mapPot_Change;
  delay(300);
  mapPot_Change = map(analogRead(A0), 0, 1023, 0, 4)

  if(mapPot != mapPot_Change)
    changeAuto = false;

  tft.setFont(Terminal12x16);
  tft.drawText(22, 10, "100ug/m^3");
  tft.fillCircle(12, 16, 5, COLOR_YELLOW);
  drawRec_G();
  drawRec_Y();
  drawRec_O();
  drawRec_R();
  draw_AUTO();

}