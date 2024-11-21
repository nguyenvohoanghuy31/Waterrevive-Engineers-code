#include <stdio.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define MIN_PWM 0
#define MAX_PWM 4095

#define PWM_CHANNEL10 10 // Motor cuốn bóng chân 1
#define PWM_CHANNEL11 11 // Motor cuốn bóng chân 2

#define PWM_CHANNEL12 12 // Motor nâng hạ chân 1
#define PWM_CHANNEL13 13 // Motor nâng hạ chân 2

#define PWM_CHANNEL1 14 // Motor di chuyển 1 chân 1
#define PWM_CHANNEL2 15 // Motor di chuyển 1 chân 2
#define PWM_CHANNEL3 8  // Motor di chuyển 2 chân 1
#define PWM_CHANNEL4 9 // Motor di chuyển 2 chân 2

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setPWMMotorsR(int c1, int c2)
{
  char dbg_str[30];
  sprintf(dbg_str,"C1: %d\tC2: %d",c1,c2);
  Serial.println(dbg_str);
  pwm.setPin(PWM_CHANNEL1, c1, true);
  pwm.setPin(PWM_CHANNEL2, c2, true);
}
void setPWMMotorsL(int c3, int c4)
{
  char dbg_str[30];
  sprintf(dbg_str,"C3: %d\tC4: %d",c3,c4);
  Serial.println(dbg_str);
  pwm.setPin(PWM_CHANNEL3, c4, true);
  pwm.setPin(PWM_CHANNEL4, c3, true);
}

void initMotors()
{
  Wire.begin();
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
  Wire.setClock(400000);
  setPWMMotorsR(0, 0);
  setPWMMotorsL(0, 0);
  pwm.setPin(10,0);
  pwm.setPin(11,0);
  pwm.setPin(12,0);
  pwm.setPin(13,0);
}
