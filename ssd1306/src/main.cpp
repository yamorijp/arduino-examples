/**
 * SSD1306でフォントを変えてテキスト表示
 *
 * モジュール
 * - 0.96インチ 128x64 OLEDディスプレイ SSD1306
 *
 * ライブラリ
 * - Adafruit_GFX_Library
 * - Adafruit_SSD1306
 *
 *
 * 配線
 * A4 - SDA
 * A5 - SCL
 *
 * OLEDディスプレイに応じた設定
 *
 * 1. 裏面の``IIC ADRESS SELECT``を確認してI2Cアドレスを調べる
 *
 *     0x78: 0x3C
 *     0x7A: 0x3A
 *
 * 2. ``Adafruit_SSD1306.h``へI2Cアドレスとディスプレイ解像度を設定(コメントイン／アウトする)
 *
 *     define SSD1306_I2C_ADDRESS 0x3C
 *     define SSD1306_128_64
 */
#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int OLED_RESET = 4;

Adafruit_SSD1306 display(OLED_RESET);

void testFont(String name, const GFXfont * font, int offset) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  // NOTE: classicとフォント指定時で描画位置決定の挙動が異なる (classic=左上, new=ベースライン)

  // classic font (built-in)
  display.setFont(NULL);
  display.setTextWrap(false);
  display.setCursor(0, 0); //
  display.println(name);

  // new font
  display.setFont(font);
  display.setTextWrap(true);
  display.setCursor(0, 20 + offset);
  display.println("The quick brown fox jumps over the lazy dog. 1234567890");

  display.display();

  delay(5000);
}

void setup()   {
  display.begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);

  // スプラッシュロゴ表示
  display.display();
  delay(3000);
}


#include "font/FreeMono9pt7b.h"
#include "font/FreeSans9pt7b.h"
#include "font/FreeSerif9pt7b.h"
#include "font/Org_01.h"
#include "font/Picopixel.h"
#include "font/TomThumb.h"

void loop() {
  testFont("FreeMono9pt7b", &FreeMono9pt7b, 14);
  testFont("FreeSans9pt7b", &FreeSans9pt7b, 16);
  testFont("FreeSerif9pt7b", &FreeSerif9pt7b, 16);
  testFont("Org_01", &Org_01, 7);
  testFont("Picopixel", &Picopixel, 7);
  testFont("TomThumb", &TomThumb, 8);
}
