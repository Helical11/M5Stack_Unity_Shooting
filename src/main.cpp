#include <M5Unified.h>
#include <BluetoothSerial.h>

BluetoothSerial bts;

int counter = 0;

void setup() {

  auto cfg = M5.config();
  M5.begin(cfg);                           // M5デバイスの初期化

  Serial.begin(115200);
  bts.begin("GunController");
  delay(500);

}

void loop() {
  M5.delay(1);
  M5.update();

  static constexpr const char* const names[] = { "none", "wasHold", "wasClicked", "wasPressed", "wasReleased", "wasDeciedCount" };
  int state = M5.BtnA.wasHold() ? 1
            : M5.BtnA.wasClicked() ? 2
            : M5.BtnA.wasPressed() ? 3
            : M5.BtnA.wasReleased() ? 4
            : M5.BtnA.wasDecideClickCount() ? 5
            : 0;

  if(state == 2) {
      bts.println(counter);
      Serial.println(state);
      counter++;
  }

}
