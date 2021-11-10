#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0

#define LCD_RESET A4

#define BLACK 0x0000
#define WHITE 0xFFFF

#define YP A2
#define XM A3
#define YM 8
#define XP 9

#define MINPRESSURE 10
#define MAXPRESSURE 1000

int relay = 53;
bool light = false;

#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void setup(void) {
  Serial.begin(9600);

  tft.reset();

  uint16_t identifier = 0x9486;

  tft.begin(identifier);
  tft.setRotation(0);
  tft.fillScreen(BLACK);
  tft.setCursor(20, 5);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.println("Light Switch");
  tft.fillRect(10, 45, 300, 5, WHITE);
  tft.setCursor(90, 240);
  tft.setTextColor(WHITE);
  tft.setTextSize(8);
  tft.println("OFF");
  tft.drawRect(70, 220, 180, 100, WHITE);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT); 
  pinMode(53  , OUTPUT);
}

void loop(void) {
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z != 0) {
    if (light == true) {
      light = false;
      tft.fillScreen(BLACK);
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
    }
    else {
      light = true;
      tft.fillScreen(WHITE);
      pinMode(XM, OUTPUT);
      pinMode(YP, OUTPUT);
    }
  }

  if (light == true) {
    tft.setCursor(20, 5);
    tft.setTextColor(BLACK);
    tft.setTextSize(4);
    tft.println("Light Switch");
    tft.fillRect(10, 45, 300, 5, BLACK);
    tft.setCursor(115, 240);
    tft.setTextColor(BLACK);
    tft.setTextSize(8);
    tft.println("ON");
    tft.drawRect(100, 220, 120, 100, BLACK);
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    digitalWrite(53, HIGH);
  }
  if (light == false) {
    tft.setCursor(20, 5);
    tft.setTextColor(WHITE);
    tft.setTextSize(4);
    tft.println("Light Switch");
    tft.fillRect(10, 45, 300, 5, WHITE);
    tft.setCursor(90, 240);
    tft.setTextColor(WHITE);
    tft.setTextSize(8);
    tft.println("OFF");
    tft.drawRect(70, 220, 180, 100, WHITE);
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    digitalWrite(53, LOW);
  }
  delay(100);
}