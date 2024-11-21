#include "motors.h"
#include "PS2_controller.h"

void setup()
{
  Serial.begin(115200);
  initMotors(); // Hàm khởi tạo động cơ
  setupPS2controller(); // Kết nối tay cầm
  Serial.println("Done setup!");
}

void loop()
{
  ps2x.read_gamepad(0, 0);
  PS2control(); // Đọc tay điều khiển
  delay(50);
}

