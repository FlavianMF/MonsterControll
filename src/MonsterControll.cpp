#include <Arduino.h>
#include <MonsterControll.h>

MonsterControll::MonsterControll(int leftINA, int leftINB, int leftPwm,
                                 int rightINA, int rightINB, int rightPwm) {
  _leftINA = leftINA;
  _leftINB = leftINB;
  _leftPwm = leftPwm;
  _rightINA = rightINA;
  _rightINB = rightINB;
  _rightPwm = rightPwm;
}

void MonsterControll::begin() {
  // REG_WRITE(GPIO_ENABLE_REG, (_leftINA + _leftINB + _rightINA + _rightINB));
  gpio_config_t io_config;
  io_config.mode = GPIO_MODE_OUTPUT;
  io_config.pin_bit_mask =
      (1 << _leftINA) | (1 << _leftINB) | (1 << _rightINA) | (1 << _rightINB);
  gpio_config(&io_config);
  _setBitMasks();
  ledcAttachPin(_leftPwm, _leftPwmChannel);
  ledcSetup(_leftPwmChannel, _leftFrequency, _leftPwmResolution);
  ledcAttachPin(_rightPwm, _rightPwmChannel);
  ledcSetup(_rightPwmChannel, _rightFrequency, _rightPwmResolution);
}

void MonsterControll::forward(int leftPwm, int rightPwm) {
  ledcWrite(_leftPwmChannel, leftPwm);
  ledcWrite(_rightPwmChannel, rightPwm == -1 ? leftPwm : rightPwm);
  if (_robotStatus != FORWARD) {
    _robotStatus = FORWARD;
    GPIO.out_w1ts = _forwardBitMaskSet;
    GPIO.out_w1tc = _forwardBitMaskClear;
    digitalWrite(LED_BUILTIN, true);
  }
}

void MonsterControll::backward(int leftPwm, int rightPwm) {
  ledcWrite(_leftPwmChannel, leftPwm);
  ledcWrite(_rightPwmChannel, rightPwm == -1 ? leftPwm : rightPwm);
  if (_robotStatus != BACKWARD) {
    _robotStatus = BACKWARD;
    GPIO.out_w1ts = _backwardBitMaskSet;
    GPIO.out_w1tc = _backwardBitMaskClear;
    digitalWrite(LED_BUILTIN, true);
  }
}

void MonsterControll::leftward(int leftPwm, int rightPwm) {
  ledcWrite(_leftPwmChannel, leftPwm);
  ledcWrite(_rightPwmChannel, rightPwm == -1 ? leftPwm : rightPwm);
  if (_robotStatus != LEFTWARD) {
    _robotStatus = LEFTWARD;
    GPIO.out_w1ts = _leftwardBitMaskSet;
    GPIO.out_w1tc = _leftwardBitMaskClear;
  }
}

void MonsterControll::rightward(int leftPwm, int rightPwm) {
  ledcWrite(_leftPwmChannel, leftPwm);
  ledcWrite(_rightPwmChannel, rightPwm == -1 ? leftPwm : rightPwm);
  if (_robotStatus != RIGHTWARD) {
    _robotStatus = RIGHTWARD;
    GPIO.out_w1ts = _rightwardBitMaskSet;
    GPIO.out_w1tc = _rightwardBitMaskClear;
  }
}

void MonsterControll::leftWheel(int pwm) {
  if (pwm > 0) {
    ledcWrite(_leftPwmChannel, pwm);
    if (_leftWheelStatus != FORWARD) {
      _leftWheelStatus = FORWARD;
      GPIO.out_w1ts = (1 << _leftINA);
      GPIO.out_w1tc = (1 << _leftINB);
    }
  } else if (pwm < 0) {
    ledcWrite(_leftPwmChannel, -pwm);
    if (_leftWheelStatus != BACKWARD) {
      _leftWheelStatus = BACKWARD;
      GPIO.out_w1ts = (1 << _leftINB);
      GPIO.out_w1tc = (1 << _leftINA);
    }
  } else {
    ledcWrite(_leftPwmChannel, 0);
    if (_leftWheelStatus != STOPED) {
      _leftWheelStatus = STOPED;
      GPIO.out_w1ts = (1 << _leftINA) | (1 << _leftINB);
    }
  }
}

void MonsterControll::rightWheel(int pwm) {
  if (pwm > 0) {
    ledcWrite(_rightPwmChannel, pwm);
    if (_rightWheelStatus != FORWARD) {
      _rightWheelStatus = FORWARD;
      GPIO.out_w1ts = (1 << _rightINA);
      GPIO.out_w1tc = (1 << _rightINB);
    }
  } else if (pwm < 0) {
    ledcWrite(_rightPwmChannel, -pwm);
    if (_rightWheelStatus != BACKWARD) {
      _rightWheelStatus = BACKWARD;
      GPIO.out_w1ts = (1 << _rightINB);
      GPIO.out_w1tc = (1 << _rightINA);
    }
  } else {
    ledcWrite(_rightPwmChannel, 0);
    if (_rightWheelStatus != STOPED) {
      _rightWheelStatus = STOPED;
      GPIO.out_w1ts = (1 << _rightINA) | (1 << _rightINB);
    }
  }
}

void MonsterControll::_setBitMasks() {
  _forwardBitMaskSet = (1 << _leftINA) | (1 << _rightINA);
  _forwardBitMaskClear = (1 << _leftINB) | (1 << _rightINB);
  _backwardBitMaskSet = (1 << _leftINB) | (1 << _rightINB);
  _backwardBitMaskClear = (1 << _leftINA) | (1 << _rightINA);
  _leftwardBitMaskSet = (1 << _leftINB) | (1 << _rightINA);
  _leftwardBitMaskClear = (1 << _leftINA) | (1 << _rightINB);
  _rightwardBitMaskSet = (1 << _leftINA) | (1 << _rightINB);
  _rightwardBitMaskClear = (1 << _leftINB) | (1 << _rightINA);
}