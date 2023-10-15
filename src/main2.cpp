#include <M5Unified.h>
#include <BluetoothSerial.h>

BluetoothSerial bts;

#define TRG_PIN 26

int counter = 0;

void setup() {

  auto cfg = M5.config();
  M5.begin(cfg);                           // M5デバイスの初期化

  M5.Display.setTextSize(1);
  M5.Display.println("HELLO WORLD");

  pinMode(TRG_PIN, OUTPUT);

  Serial.begin(115200);
  bts.begin("GunController");
  delay(500);

}

void loop() {
  M5.delay(1);
  M5.update();

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

      digitalWrite(TRG_PIN, HIGH);
      delay(50);
 }

}
