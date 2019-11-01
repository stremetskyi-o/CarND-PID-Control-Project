#include <iostream>
#include <cmath>
#include "PID.h"

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  k = {Kp_, Kd_, Ki_};
  if (twiddleEnabled) {
    k[twiddleI] += twiddleCoeff[twiddleI];
  }
}

void PID::UpdateError(double cte) {
  d_error = d_error == 0 ? cte : cte - d_error;
  p_error = cte;
  i_error = TotalError();
  if (twiddleEnabled) {
    twiddleN += 1;
    twiddleError += pow(cte, 2);
  }
}

double PID::TotalError() {
  return i_error + p_error;
}

double PID::nextAngle(double prevAngle, double speed) {
  double angle = - k[0] * p_error - k[1] * d_error - k[2] * i_error;
  //std::cout << angle << std::endl;
  angle *= exp(-(1 - speed / 100));
  return (angle < -1) ? -1 : (1 < angle) ? 1 : angle;
}

void PID::reset() {
  if (twiddleEnabled) {
    twiddleError /= twiddleN;
    std::cout << "error " << twiddleError << std::endl;
    if (twiddlePositive) {
      if (twiddleError < bestTwiddleError) {
        std::cout << k[0] << " " << k[1] << " " << k[2] << std::endl;
        bestTwiddleError = twiddleError;
        twiddleCoeff[twiddleI] *= 1.1;
      } else {
        twiddlePositive = false;
        k[twiddleI] -= 2 * twiddleCoeff[twiddleI];
      }
    } else {
      if (twiddleError < bestTwiddleError) {
        std::cout << k[0] << " " << k[1] << " " << k[2] << std::endl;
        bestTwiddleError = twiddleError;
        twiddleCoeff[twiddleI] *= 1.1;
      } else {
        twiddlePositive = true;
        k[twiddleI] += twiddleCoeff[twiddleI];
        twiddleCoeff[twiddleI] *= 0.9;
        twiddleI = (twiddleI + 1) % k.size();
        k[twiddleI] += twiddleCoeff[twiddleI];
      }
    }
    twiddleError = 0;
    twiddleN = 0;
  } else {
   d_error = 0;
   p_error = 0;
   i_error = 0;
  }
}