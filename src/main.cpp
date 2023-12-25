/**
 * @file main.cpp
 * @author Helical
 * @brief M5StackxUnityシューティングのメインコード
 * @version 0.1
 * @date 2023-12-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <BluetoothSerial.h>
#include <M5Unified.h>

//----------------------------------------
// Static
//----------------------------------------
//! 拳銃のトリガーピン
#define TRG_PIN 26

//----------------------------------------
// Variables
//----------------------------------------
//! Bluetoothクラス
BluetoothSerial bts;
//! 割り込み待機時間[us]
volatile int WaitingTimer = 1000;
//! 割り込み許可フラグ
volatile bool interruptFlag = false;
//! 最後に割り込みが実施された時間
volatile uint64_t lastInterruptTime = 0;
;

/**
 * @brief トリガー割り込み関数
 */
void IRAM_ATTR onInterrupt() {
    uint64_t currentTime = millis();

    // 前回の割り込みから一定時間経過してたら割り込み許可
    if (currentTime - lastInterruptTime > WaitingTimer) {
        interruptFlag = true;  // 割り込み許可フラグをたてる
        lastInterruptTime = currentTime;  // 最後の割り込み実施時間を更新
    }
}

/**
 * @brief 24VのDC入力の有無判定
 * @param status DC電源の有無フラグ 1:DC入力あり
 */
void Display_Power(uint8_t status) {
    if (status) {
        M5.Display.fillTriangle(98, 15, 105, 19, 112, 3, ORANGE);
        M5.Display.fillTriangle(108, 14, 115, 18, 101, 30, ORANGE);
    } else {
        M5.Display.fillRect(98, 2, 18, 30, BLACK);
    }
}

/**
 * @brief M5StickCのバッテリー残量判定
 * @param status バッテリー残量電圧[V]
 */
void Display_Battery(uint8_t status) {
    if (status > 4) status = 4;
    M5.Display.fillRect(121, 6, 10, 24, BLACK);
    if (status) {
        M5.Display.fillRect(121, 26, 10, 4, DARKGREEN);
        for (int i = 0; i < status; i++) {
            M5.Display.fillRect(121, 21 - i * 5, 10, 5, DARKGREEN);
        }
    } else {
        M5.Display.fillRect(121, 26, 10, 4, RED);
    }
}

/**
 * @brief M5StickCのディスプレイ初期化
 */
void Display_Ini() {
    M5.Display.fillScreen(BLACK);
    M5.Display.fillRect(119, 4, 14, 28, WHITE);
    M5.Display.fillRect(123, 2, 6, 2, WHITE);
    M5.Display.fillRect(121, 6, 10, 24, BLACK);

    Display_Battery(2);
    Display_Power(1);
}

/**
 * @brief 初期化関数
 */
void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);  // M5デバイスの初期化

    //----------------------------------------
    // M5StickCのディスプレイ設定
    //----------------------------------------
    M5.Display.setTextSize(1);
    Display_Ini();

    //----------------------------------------
    // ペリフェラルの設定
    //----------------------------------------
    pinMode(TRG_PIN, INPUT_PULLUP);  // トリガーピンプルアップ
    attachInterrupt(G26, onInterrupt, FALLING);  // 割り込み関数を適用

    //----------------------------------------
    // シリアル通信初期化
    //----------------------------------------
    Serial.begin(115200);
    bts.begin("GunController");

    delay(500);
}

/**
 * @brief ループ関数
 */
void loop() {
    //    M5.delay(1);
    M5.update();

    //----------------------------------------
    // トリガーを押した場合の処理
    //----------------------------------------
    if (interruptFlag) {        // トリガー割り込みが発生した場合
        Serial.println("Yes");  // シリアル送信
        bts.println("1");       // Bluetooth送信
        interruptFlag = false;  // 割り込み許可フラグをさげる
    }

    //----------------------------------------
    // M5StickCのボタンを押した場合の処理
    //----------------------------------------
    //   static constexpr const char* const names[] = {
    //       "none",       "wasHold",     "wasClicked",
    //       "wasPressed", "wasReleased", "wasDeciedCount"};
    //   int state = : M5.BtnA.wasPressed() ? 1 : 0;
    //   int state = : M5.BtnB.wasPressed() ? 2 : 0;
    //
    //   switch (state) {
    //       case 1:
    //           delay(50);
    //           break;
    //       case 2:
    //           delay(50);
    //           break;
    //       default:;
    //           break;
    //  }
}
