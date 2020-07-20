#ifndef __MONSTERCONTROLL_H__
#define __MONSTERCONTROLL_H__

typedef enum { FORWARD, BACKWARD, STOPED, LEFTWARD, RIGHTWARD } WheelsStatus;

class MonsterControll {
 public:
  MonsterControll(int leftINA, int leftINB, int leftPwm, int rightINA,
                  int rightINB, int rightPwm);
  void begin();
  // int left(int leftPwm, int rightPwm = -1);
  // void right(int pwm);
  void forward(int leftPwm, int rightPwm = -1);
  void backward(int leftPwm, int rightPwm = -1);
  void leftward(int leftPwm, int rightPwm = -1);
  void rightward(int leftPwm, int rightPwm = -1);
  void stop();
  void leftWheel(int pwm);
  void rightWheel(int pwm);

 private:
  int _leftINA;
  int _leftINB;
  int _leftPwm;
  int _rightINA;
  int _rightINB;
  int _rightPwm;

  int _leftPwmChannel = 0;
  int _leftFrequency = 10000;
  int _leftPwmResolution = 10;

  int _rightPwmChannel = 1;
  int _rightFrequency = 10000;
  int _rightPwmResolution = 10;

  int _forwardBitMaskSet = 0b00;
  int _forwardBitMaskClear = 0b00;
  int _backwardBitMaskSet = 0b00;
  int _backwardBitMaskClear = 0b00;
  int _leftwardBitMaskSet = 0b00;
  int _leftwardBitMaskClear= 0b00;
  int _rightwardBitMaskSet = 0b00;
  int _rightwardBitMaskClear = 0b00;

  uint8_t _leftWheelStatus;
  uint8_t _rightWheelStatus;
  uint8_t _robotStatus = STOPED;

  void _setBitMasks();
};

#endif  // __MONSTERCONTROLL_H__