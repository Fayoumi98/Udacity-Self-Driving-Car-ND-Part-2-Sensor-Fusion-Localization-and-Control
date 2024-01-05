#include <iostream>
#include "eigen3/Eigen/Dense"
#include <vector>
#include "ukf.h"

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::vector;

int main() {

	//Create a UKF instance
	UKF ukf;
    
    // step 1 : Generate Sigma Points
    MatrixXd Xsig = MatrixXd(5, 11);
    ukf.GenerateSigmaPoints(&Xsig);

    // step 2 : Generate Augmented Sigma Points
    MatrixXd Xsig_aug = MatrixXd(7, 15);
    ukf.AugmentedSigmaPoints(&Xsig_aug);
    
    //print result (Sigma Points)
    //std::cout << "Xsig_aug = " << std::endl << Xsig << std::endl;
    //std::cout << "Xsig_aug = " << std::endl << Xsig_aug << std::endl;

    // Step 3 : Sigma Point Prediction
    MatrixXd Xsig_pred = MatrixXd(15, 5);
    ukf.SigmaPointPrediction(&Xsig_pred);
    
    // Step 4 : Sigma Point Prediction
    VectorXd x_pred = VectorXd(5);
    MatrixXd P_pred = MatrixXd(5, 5);
    ukf.PredictMeanAndCovariance(&x_pred, &P_pred);

    // Step 5 : Predict Radar Measurement
    VectorXd z_out = VectorXd(3);
    MatrixXd S_out = MatrixXd(3, 3);
    ukf.PredictRadarMeasurement(&z_out, &S_out);

    // Step 6 : Update State
    VectorXd x_out = VectorXd(5);
    MatrixXd P_out = MatrixXd(5, 5);
    ukf.UpdateState(&x_out, &P_out);

	return 0;
}