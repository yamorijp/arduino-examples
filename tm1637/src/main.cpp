/**
 * アップ／ダウンボタン付きカウンター
 *
 * 使用モジュール
 * - 7セグ4桁ディスプレイモジュール (TM1637)
 * - 静電容量式タッチセンサーモジュール (TTP223) x2
 *
 * ライブラリ
 * - [DigitalTube libraries](https://github.com/reeedstudio/libraries/tree/master/DigitalTube)
 */
#include <Arduino.h>
#include <TM1637.h>

const int CLK = 12;
const int DIO = 11;
const int DECR = 10;
const int INCR = 9;
const int OFF = 0x7E;

TM1637 tm1637(CLK,DIO);

int current = 0;
uint8_t DispData[4] = {OFF, OFF, OFF, 0x00};

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

  pinMode(INCR, INPUT);
  pinMode(DECR, INPUT);
}

void loop()
{
  int incr = digitalRead(INCR);
  int decr = digitalRead(DECR);
  if (incr != decr) {
    // 0 <= current <= 9999
    current = (incr == HIGH) ?
      (current + 1) % 10000 : (current + 9999) % 10000;
    display();
    delay(100);
  }
  delay(100);
}
