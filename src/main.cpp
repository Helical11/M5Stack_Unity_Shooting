#include <FastLED.h>
#include <M5UnitGLASS2.h>
#include <M5Unified.h>
#include <BluetoothSerial.h>

BluetoothSerial bts;

#define LED_PIN 27
#define LED_COUNT 25
#define TRG_PIN 25

static CRGB leds[LED_COUNT];

int counter = 0;

void setup() {

  auto cfg = M5.config();
  cfg.external_display.unit_glass2 = true;
  M5.begin(cfg);                           // M5デバイスの初期化

  M5.Display.setTextSize(1);
  M5.Display.println("HELLO WORLD");

  for( int i = 0; i < 12; i++ ) {
    int32_t x = 10*( i+1 );
    int32_t y = -( 0.000025*x*x*x + 0.1*x - 60 );
    M5.Display.fillRect(x, y, 8, 62 - y, WHITE);
    delay(50);
  }

  pinMode(TRG_PIN, OUTPUT);

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
  digitalWrite(TRG_PIN,LOW);

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

      digitalWrite(TRG_PIN, HIGH);
      delay(50);
 }

}
