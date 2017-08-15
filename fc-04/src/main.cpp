/**
 * サウンドスイッチでLEDトグル
 *
 * 使用モジュール
 * - サウンドセンサースイッチモジュール (FC-04)
 * - ビルトインLED
 */
#include <Arduino.h>

const int LED_1 = LED_BUILTIN;
const int OUT = 12;

bool ledOn = false;

void setup()
{
  Serial.begin(9600);

  pinMode(LED_1, OUTPUT);
  pinMode(OUT, INPUT);
}

void loop()
{
  if (digitalRead(OUT) == HIGH) {
    ledOn = !ledOn;
    digitalWrite(LED_1, ledOn ? HIGH : LOW);
    delay(300);
  }
  delay(50);
}
