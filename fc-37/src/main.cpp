/**
 * 水滴センサーの値を表示
 *
 * 使用モジュール
 * - 7セグ4桁ディスプレイモジュール (TM1637)
 * - 水滴センサーモジュール (FC-37)
 *
 * ライブラリ
 * - [DigitalTube liararies](https://github.com/reeedstudio/libraries/tree/master/DigitalTube)
 */
#include <Arduino.h>
#include <TM1637.h>

const int CLK = 12;
const int DIO = 11;
const int AO = A5;
const int OFF = 0x7E;

TM1637 tm1637(CLK,DIO);

int current = 0;
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
  pinMode(AO, INPUT);
}

void loop()
{
  int value = analogRead(AO);
  if (current != value) {
    current = value;
    display();
  }
  delay(500);
}
