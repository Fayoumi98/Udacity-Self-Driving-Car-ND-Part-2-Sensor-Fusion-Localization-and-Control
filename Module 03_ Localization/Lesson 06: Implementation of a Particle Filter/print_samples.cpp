#include <random>
#include <iostream>

using namespace std;

// @param gps_x 	GPS provided x position
// @param gps_y 	GPS provided y position
// @param theta		GPS provided yaw
void printSamples(double gps_x, double gps_y, double theta) {
	default_random_engine gen;

    // Standard deviations for x, y, and theta
	double std_x, std_y, std_theta; 

	// Set standard deviations for x, y, and theta
    std_x = 2;
    std_y = 2;
    std_theta = 0.05;
	 

	// This line creates a normal (Gaussian) distribution for x
	normal_distribution<double> dist_x(gps_x, std_x);
	
	// TODO: Create normal distributions for y and theta
	normal_distribution<double> dist_y(gps_y, std_y);
	normal_distribution<double> dist_theta(theta, std_theta);

	
	for (int i = 0; i < 3; ++i) {
		double sample_x, sample_y, sample_theta;
		
		// Sample  and from these normal distrubtions like this: 
		//	 sample_x = dist_x(gen);
		//	 where "gen" is the random engine initialized earlier.
    
        sample_x = dist_x(gen);
        sample_y = dist_y(gen);
        sample_theta = dist_theta(gen);	 
        
        // Print your samples to the terminal.
        cout << "Sample " << i + 1 << " " << sample_x << " " << sample_y << " " << sample_theta << endl;
	}

}

int main() {
	
	// Set GPS provided state of the car.
	double gps_x = 4983;
	double gps_y = 5029;
	double theta = 1.201;
	
	// Sample from the GPS provided position.
	printSamples(gps_x, gps_y, theta);
	
	return 0;
}