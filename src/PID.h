#ifndef PID_H
#define PID_H

#include <limits>
#include <vector>

using std::vector;

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Ki_, double Kd_);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError();

  double nextAngle(double prevAngle, double speed);

  void reset();

 private:
  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;

  /**
   * PID Coefficients
   */ 
  double Kp;
  double Ki;
  double Kd;

  /**
   * Twiddle params
   */
  const bool twiddleEnabled = true;
  const vector<double> twiddleCoeff = {0, 0, 0};
  bool twiddlePositive = true;
  double twiddleError = std::numeric_limits<double>::max();
  int twiddleStep = 0;
};

#endif  // PID_H