#include <M5Unified.h>
#include <BluetoothSerial.h>

BluetoothSerial bts;

#define TRG_PIN 26

int counter = 0;


void Display_Battery() {

}

void Display_Power(uint8_t status) {
  if( status ) {
    M5.Display.fillTriangle( 98, 15,105, 19,112,  3,ORANGE);
    M5.Display.fillTriangle(108, 14,115, 18,101, 30,ORANGE);
  } else {
    M5.Display.fillRect( 98,  2, 18, 30, BLACK);
  }
}

void Display_Battery(uint8_t status) {
  if( status > 4 ) status =4;
  M5.Display.fillRect(121,  6, 10, 24,BLACK);
  if( status ) {
    M5.Display.fillRect(121, 26, 10,  4,DARKGREEN);
    for( int i = 0; i<status; i++) {
      M5.Display.fillRect(121, 21-i*5, 10,  5,DARKGREEN);
    }
  } else {
    M5.Display.fillRect(121, 26, 10,  4,RED);
  }
}


void Display_Ini() {

  M5.Display.fillScreen(BLACK);
  M5.Display.fillRect(119,  4, 14, 28,WHITE);
  M5.Display.fillRect(123,  2,  6,  2,WHITE);
  M5.Display.fillRect(121,  6, 10, 24,BLACK);

  Display_Battery(2);
  Display_Power(1);

}




void setup() {

  auto cfg = M5.config();
  M5.begin(cfg);                           // M5デバイスの初期化

  M5.Display.setTextSize(1);
  M5.Display.println("HELLO WORLD");

  pinMode(TRG_PIN, OUTPUT);

  Serial.begin(115200);
  bts.begin("GunController");
  delay(500);


  Display_Ini();



}

void loop() {
  M5.delay(1);
  M5.update();

  uint8_t Battery_level = M5.Power.getBatteryLevel();

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
      M5.Display.println(Battery_level);

      digitalWrite(TRG_PIN, HIGH);
      delay(50);
 }

}
