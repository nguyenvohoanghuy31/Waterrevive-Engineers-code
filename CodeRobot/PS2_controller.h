#include <PS2X_lib.h>

PS2X ps2x;
#define BEBUG_CTRL

#define Y_JOY_CALIT 128
#define Y_JOY_CALIP 128

#define PS2_DAT 12
#define PS2_CMD 13
#define PS2_SEL 15
#define PS2_CLK 14

#define TOP_SPEED 4095
#define NORM_SPEED 2048
#define TURNING_FACTOR 1

bool quay = false;
bool nang=false,ha=false;

void setupPS2controller()
{
  int err = -1;
  while (err != 0)
  {
    err = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);
  }

}
bool PS2control()
{
  int speed = NORM_SPEED;
  if (ps2x.Button(PSB_R2))
    speed = TOP_SPEED;
  //HÀM CUỐN BÓNG
  if (ps2x.ButtonPressed(PSB_CROSS)) { // PSB_CROSS là nút A trên tay cầm
    quay = !quay; // Đảo trạng thái động cơ
    Serial.print("Motor state changed to: ");
    Serial.println(quay ? "ON" : "OFF");

    // Điều khiển động cơ thông qua PCA9685
    if (quay) {
      for (int i=0;i<=2000;i+=25){
        pwm.setPin(10,i);
        delay(50);
      }; // Bật động cơ
    } else {
      for (int i=2000;i>0;i-=25){
        pwm.setPin(10,i);
        delay(50);
      };    // Tắt động cơ
    }
  }

  //HÀM NÂNG HẠ SÀN
  if (ps2x.ButtonPressed(PSB_PAD_UP)) {
    nang = !nang; // Đảo trạng thái động cơ
    Serial.print("Motor state changed to: ");
    Serial.println(nang ? "ON" : "OFF");

    if (nang) {
      pwm.setPin(12,1024);
    } else {
      pwm.setPin(12,0);
    }
  }
  if (ps2x.ButtonPressed(PSB_PAD_DOWN)) {
    ha = !ha; // Đảo trạng thái động cơ
    Serial.print("Motor state changed to: ");
    Serial.println(ha ? "ON" : "OFF");

    if (ha) {
      pwm.setPin(13,1024);
    } else {
      pwm.setPin(13,0);
    }
  }
  //END
  int pJoyY = Y_JOY_CALIP - ps2x.Analog(PSS_RY); // Đọc y-joystick phải
  int tJoyY = Y_JOY_CALIT - ps2x.Analog(PSS_LY); // Đọc y-joystick trái
  int nMotMixR; // Giá trị điều khiển motor phải                        
  int nMotMixL; // Giá trị điều khiển motor trái
  if((pJoyY == -1) or (tJoyY == -1))
  {
    setPWMMotorsR(0, 0);
    setPWMMotorsL(0, 0);
    return 0;
  }
   nMotMixR = pJoyY;
   nMotMixL = tJoyY;
  #ifdef BEBUG_CTRL
  Serial.print(F("Calculated value from joystick: "));
  Serial.println(nMotMixL);
  Serial.println("    ");
  Serial.println(nMotMixR);
  #endif
  int c1 = 0, c2 = 0,c3 = 0,c4 = 0;

  if (nMotMixR > 0)
  {
    c1 = nMotMixR;
    c1 = map(c1, 0, 128, 0, speed);
  }

  else if (nMotMixR < 0)
  {
    c2 = abs(nMotMixR) + 1;
    c2 = map(c2, 0, 128, 0, speed);
  }
  if (nMotMixL > 0)
  {
    c3 = nMotMixL;
    c3 = map(c3, 0, 128, 0, speed);
  }

  else if (nMotMixL < 0)
  {
    c4 = abs(nMotMixL) + 1;
    c4 = map(c4, 0, 128, 0, speed);
  }
  setPWMMotorsR(c1, c2);
  setPWMMotorsL(c3, c4);
  return 1;
}
