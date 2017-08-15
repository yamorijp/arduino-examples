/**
 * 超音波距離センサーで距離測定
 *
 * モジュール
 * - 7セグ4桁ディスプレイモジュール (TM1637)
 * - 超音波距離センサーモジュール (HC-SR04)
 *
 * ライブラリ
 * - [DigitalTube liararies](https://github.com/reeedstudio/libraries/tree/master/DigitalTube)
 */
#include <Arduino.h>
#include <TM1637.h>

const int CLK = 12;
const int DIO = 11;
const int TRIG = 9;
const int ECHO = 10;

const int OFF = 0x7E;

TM1637 tm1637(CLK,DIO);

double duration = 0;
double current = 0;

int8_t DispData[4] = {OFF, OFF, OFF, 0x00};

void display()
{
  int value = current > 9999 ? 9999 : current;
  for (int i=0; i<4; i++) {
    if (value == 0) {
      DispData[3-i] = i == 0 ? 0 : OFF;
    } else {
      DispData[3-i] = value % 10;
      value /= 10;
    }
  }
  tm1637.display(DispData);
}

void setup()
{
  Serial.begin(9600);

  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);
  display();

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop()
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);  // 往復時間 (usec)
  Serial.println(duration);
  if (duration > 0) {
    // 音速 340.29m/sで計算
    current = duration * 340.29 / 2 / 1000;  // 距離 (mm)
    display();
  }
  delay(250);
}
