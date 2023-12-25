#include <BluetoothSerial.h>
#include <M5Unified.h>

BluetoothSerial bts;

// GPIOピン設定

// ボタン押した回数
int counter = 0;

// 車体角度変数 加速度から
float rowAngleA = 0.0;
float AngleA = 0.0;

// 車体角度変数 ジャイロから
float rowAngleG = 0.0;
float AngleG = 0.0;

// 車体角度変数
float preAngle = 0.0;
float Angle = 0.0;

//
float pitch, roll, yaw;

float AccelOffset = 0.0;
float GyroOffset = 0.0;

float error = 0.0;
float preerror = 0.0;
float sumerror = 0.0;

// ラジアン→度変換
const float RADTODEG = 180 / 3.14;

// Teleplot用シリアル出力
void TeleplotPrint() {
    Serial.printf(">rowAngleA:%f\n", rowAngleA);
    Serial.printf(">AngleA:%f\n", AngleA);
    Serial.printf(">rowAngleG:%f\n", rowAngleG);
    Serial.printf(">AngleG:%f\n", AngleG);
    Serial.printf(">Angle:%f\n", Angle);
}

void IMUCalibration() {
    for (int i = 0; i < 1000; i++) {
        auto imu_update = M5.Imu.update();
        auto data = M5.Imu.getImuData();
        AccelOffset += atan2(data.accel.z, data.accel.y) * RADTODEG;
        GyroOffset += data.gyro.x;
        printf(">GyroOffset:%f\n", GyroOffset);
        delay(5);
    }

    AccelOffset /= 1000;
    GyroOffset /= 1000;
}

void setup() {
    auto cfg = M5.config();
    auto imu_update = M5.Imu.update();
    M5.begin(cfg);  // M5デバイスの初期化

    M5.Display.setTextSize(1);

    IMUCalibration();

    Serial.begin(115200);
    bts.begin("GunController");
    delay(500);
}

void loop() {
    M5.delay(1);
    M5.update();

    auto imu_update = M5.Imu.update();
    if (imu_update) {
        auto data = M5.Imu.getImuData();

        //        preAngle = Angle;

        // 加速度センサからの角度算出
        //        rowAngleA = atan2(data.accel.z, data.accel.y) * RADTODEG;
        //        AngleA = 0.5 * AngleA + 0.5 * (rowAngleA - AccelOffset);

        // ジャイロからの角度算出
        //        rowAngleG = -(data.gyro.x - GyroOffset) * 0.1;
        //        AngleG = preAngle + rowAngleG;

        // 相補フィルタ
        //        Angle = 0.85 * AngleG + 0.15 * AngleA;

        //    data.accel.x;   // 車体左右方向
        //    data.accel.y;   // 車体重力方向 直立時1
        //    data.accel.z;   // 車体重力方向 直立時0

        //    data.gyro.x;    // 車輪軸回転
        //    data.gyro.y;    // 旋回軸回転
        //    data.gyro.z;    // 進行軸回転

        pitch = atan2(data.accel.y, data.accel.z) * RADTODEG;
        roll = atan2(-data.accel.x, sqrt(data.accel.y * data.accel.y +
                                         data.accel.z * data.accel.z)) *
               RADTODEG;
        yaw = atan2(data.gyro.x, data.gyro.y) * RADTODEG;
    }

    //    TeleplotPrint();

    bts.print(pitch);
    bts.print(",");
    bts.print(roll);
    bts.print(",");
    bts.println(yaw);

    delay(100);
}
