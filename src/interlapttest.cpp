/**
 * @file interlapttest.cpp
 * @brief
 * @author Helical
 * @date 2023-12-25
 * @copyright Copyright (c) 2023
 */
#include <M5Unified.h>

volatile bool interruptFlag = false;  // 割り込みが発生したかを示すフラグ
unsigned long lastInterruptTime = 0;  // 最後に割り込みが発生した時刻

void IRAM_ATTR onInterrupt() {
    unsigned long currentTime = millis();

    // デバウンス処理（前回の割り込みから一定時間が経過しているか）
    if (currentTime - lastInterruptTime > 1000) {
        interruptFlag = true;             // フラグを立てる
        lastInterruptTime = currentTime;  // 割り込み時間を更新
    }
}

void setup() {
    M5.begin();
    Serial.begin(115200);

    pinMode(G26, INPUT_PULLUP);
    attachInterrupt(G26, onInterrupt, FALLING);
}

void loop() {
    if (interruptFlag) {
        // 割り込みが発生した場合の処理
        Serial.println("Yes");
        interruptFlag = false;  // フラグをリセット
    }

    M5.update();
}
