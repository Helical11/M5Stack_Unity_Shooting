#include <M5Unified.h>
#include <BluetoothSerial.h>

BluetoothSerial bts;

char buf[60];

int counter = 0;

// put function declarations here:
void myFunction();

void setup() {

  M5.begin();
  Serial.begin(115200);
  bts.begin("GunController");
  delay(500);

}

void loop() {
  M5.update();
  bts.println(counter);
  counter++;
  delay(500);
}

// put function definitions here:
void myFunction() {

}