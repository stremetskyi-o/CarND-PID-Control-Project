#include <iostream>
#include <cmath>
#include "PID.h"

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;
}

void PID::UpdateError(double cte) {
  d_error = d_error == 0 ? cte : cte - d_error;
  p_error = cte;
  i_error = TotalError();
}

double PID::TotalError() {
  return i_error + p_error;
}

double PID::nextAngle(double prevAngle, double speed) {
  double angle = - Kp * p_error - Kd * d_error - Ki * i_error;
  std::cout << angle << std::endl;
  angle *= exp(-(1 - speed / 100));
  return (angle < -1) ? -1 : (1 < angle) ? 1 : angle;
}

void PID::reset() {
  d_error = 0;
  p_error = 0;
  i_error = 0;
}