/**
 * 温度、湿度を交互に表示
 *
 * 使用モジュール
 * - 7セグ4桁ディスプレイモジュール (TM1637)
 * - 温度湿度センサーモジュール (DHT11)
 *
 * ライブラリ
 * - [DigitalTube libraries](https://github.com/reeedstudio/libraries/tree/master/DigitalTube)
 * - [DHT](https://github.com/markruys)
 */
#include <Arduino.h>
#include <TM1637.h>
#include <DHT.h>

const int CLK = 12;
const int DIO = 11;
const int DHT_OUT = 10;

const int OFF = 0x7E;

TM1637 tm1637(CLK,DIO);
DHT dht;
int current = 0;
boolean toggle = true;
int8_t DispData[4] = {OFF, OFF, OFF, 0x00};


void setup()
{
  Serial.begin(9600);

  dht.setup(DHT_OUT);

  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);
}

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

void loop()
{
  current = toggle ? (int)dht.getTemperature() : (int)dht.getHumidity();
  display();
  toggle = !toggle;

  delay(3000);
}
