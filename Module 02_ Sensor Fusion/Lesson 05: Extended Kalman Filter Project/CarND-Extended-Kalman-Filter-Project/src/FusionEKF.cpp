#include "FusionEKF.h"
#include <iostream>
#include "eigen3/Eigen/Dense"
#include "tools.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::cout;
using std::endl;
using std::vector;

/**
 * Constructor.
 */
FusionEKF::FusionEKF() {
  is_initialized_ = false;

  previous_timestamp_ = 0;

  // initializing matrices
  R_laser_ = MatrixXd(2, 2);
  R_radar_ = MatrixXd(3, 3);
  H_laser_ = MatrixXd(2, 4);
  Hj_ = MatrixXd(3, 4);

  //measurement covariance matrix - laser
  R_laser_ << 0.0225, 0,
              0, 0.0225;

  //measurement covariance matrix - radar
  R_radar_ << 0.09, 0, 0,
              0, 0.0009, 0,
              0, 0, 0.09;


  ekf_.P_ = MatrixXd(4, 4);
  ekf_.P_ << 1, 0, 0, 0,
             0, 1, 0, 0,
             0, 0, 1000, 0,
             0, 0, 0, 1000;

  H_laser_ << 1, 0, 0, 0,
              0, 1, 0, 0;


}

/**
 * Destructor.
 */
FusionEKF::~FusionEKF() {}


void FusionEKF::ProcessMeasurement(const MeasurementPackage &measurement_pack) {

  /*****************************************************************************************/
  /*********************************** Initialization **************************************/
  /*****************************************************************************************/

  if (!is_initialized_) {

    // first measurement
    cout << "EKF: " << endl;
    ekf_.x_ = VectorXd(4);
    ekf_.x_ << 1, 1, 1, 1;

    if (measurement_pack.sensor_type_ == MeasurementPackage::RADAR) {
      cout << "EKF : First measurement RADAR" << endl;

      double rho = measurement_pack.raw_measurements_[0];     // range
  	  double phi = measurement_pack.raw_measurements_[1];     // bearing
  	  double rho_dot = measurement_pack.raw_measurements_[2]; // velocity of rho

  	  // Coordinates convertion from polar to cartesian
      
      //// to prevent division by 0
  	  double x = rho * cos(phi);
      if ( x < 0.0001 ) {
        x = 0.0001;
      }
  	  double y = rho * sin(phi);
      if ( y < 0.0001 ) 
      {
        y = 0.0001;
      }

  	  double vx = rho_dot * cos(phi);
  	  double vy = rho_dot * sin(phi);

      // initial state from first reading (Radar)
      ekf_.x_ << x, y, vx , vy;
    }
    else if (measurement_pack.sensor_type_ == MeasurementPackage::LASER) 
    {
      
      cout << "EKF : First measurement LASER" << endl;
      
      // initial state from first reading (Radar)
      ekf_.x_ << measurement_pack.raw_measurements_[0], measurement_pack.raw_measurements_[1], 0, 0;

    }

    // Saving first timestamp in seconds
    previous_timestamp_ = measurement_pack.timestamp_ ;

    // done initializing, no need to predict or update
    is_initialized_ = true;

    return;
  }

  /*****************************************************************************************/
  /*********************************** Prediction ******************************************/
  /*****************************************************************************************/

  // calculate delta time and convert it from micro seconds to seconds
  double dt = (measurement_pack.timestamp_ - previous_timestamp_) / 1000000.0;
  // update previous timestamp for the next iteration
  previous_timestamp_ = measurement_pack.timestamp_;

  // State transition matrix update with delta time
  ekf_.F_ = MatrixXd(4, 4);
  ekf_.F_ << 1, 0, dt, 0,
             0, 1, 0, dt,
             0, 0, 1, 0,
             0, 0, 0, 1;

  // Noise covariance matrix computation
  // Noise values from the task
  double noise_ax = 9.0;
  double noise_ay = 9.0;

  double dt_2 = dt * dt;      //dt^2
  double dt_3 = dt_2 * dt;    //dt^3
  double dt_4 = dt_3 * dt;    //dt^4
  double dt_4_4 = dt_4 / 4;   //dt^4/4
  double dt_3_2 = dt_3 / 2;   //dt^3/2

  // Supdate state covariance matrix 
  ekf_.Q_ = MatrixXd(4, 4);
  ekf_.Q_ << dt_4_4 * noise_ax, 0, dt_3_2 * noise_ax, 0,
	         0, dt_4_4 * noise_ay, 0, dt_3_2 * noise_ay,
	         dt_3_2 * noise_ax, 0, dt_2 * noise_ax, 0,
 	         0, dt_3_2 * noise_ay, 0, dt_2 * noise_ay;

  // call Predict function
    ekf_.Predict();


  /*****************************************************************************************/
  /*************************************** Update ******************************************/
  /*****************************************************************************************/


   // Use the sensor type to perform the update step.
   // Update the state and covariance matrices.


  if (measurement_pack.sensor_type_ == MeasurementPackage::RADAR) {
    
    // Radar updates
    ekf_.H_ = tools.CalculateJacobian(ekf_.x_);             // calculate Hj
  	ekf_.R_ = R_radar_;
  	ekf_.UpdateEKF(measurement_pack.raw_measurements_);     // call measurement update

  } else {
    // Laser updates
    ekf_.H_ = H_laser_;                                     // Use H
  	ekf_.R_ = R_laser_;                                     // Use R
  	ekf_.Update(measurement_pack.raw_measurements_);        // call measurement update

  }

  // print the output
  cout << "x_ = " << ekf_.x_ << endl;
  cout << "P_ = " << ekf_.P_ << endl;
}
