#include <FastLED.h>
#include <M5Unified.h>
#include <BluetoothSerial.h>


BluetoothSerial bts;

#define LED_PIN 27
#define LED_COUNT 25

static CRGB leds[LED_COUNT];

int counter = 0;

void setup() {

  auto cfg = M5.config();
  M5.begin(cfg);                           // M5デバイスの初期化

  Serial.begin(115200);
  bts.begin("GunController");
  delay(500);

  // FastLEDの初期化
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_COUNT);

  FastLED.setBrightness(80);

    // 全LEDを白色で点灯
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = CRGB::Black;
  }

    // 出力
  FastLED.show();


}

void loop() {
  M5.delay(1);
  M5.update();

  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();

  static constexpr const char* const names[] = { "none", "wasHold", "wasClicked", "wasPressed", "wasReleased", "wasDeciedCount" };
  int state = M5.BtnA.wasHold() ? 1
            : M5.BtnA.wasClicked() ? 2
            : M5.BtnA.wasPressed() ? 3
            : M5.BtnA.wasReleased() ? 4
            : M5.BtnA.wasDecideClickCount() ? 5
            : 0;

  if(state == 3) {
      bts.println(counter);
      Serial.println(state);
      counter++;

      for (int i = 0; i < LED_COUNT; i++) {
      leds[i] = CRGB::White;
      }
      FastLED.show();
  }

}
