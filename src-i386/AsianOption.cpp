#include<iostream>
#include<cmath>
#include"getOneGaussianByBoxMueller.h"
#include"AsianOption.h"


//definition of constructor
PutUpandOutOption::PutUpandOutOption(
	int nInt_,
	double strike_,
	double spot_,
	double vol_,
	double r_,
	double expiry_,
	double b_){
		nInt = nInt_;
		strike = strike_;
		spot = spot_;
		vol = vol_;
		r = r_;
		expiry = expiry_;
		b = b_;
		generatePath();
}

//method definition
void PutUpandOutOption::generatePath(){
	double thisDrift = (r * expiry - 0.5 * vol * vol * expiry) / double(nInt);
	double cumShocks = 0;
	thisPath.clear();

	for(int i = 0; i < nInt; i++){
		cumShocks += (thisDrift + vol * sqrt(expiry / double(nInt)) * getOneGaussianByBoxMueller());
		thisPath.push_back(spot * exp(cumShocks));
	}
}



//method definition
double PutUpandOutOption::getMax(){

	double val_max = thisPath[0];

	for(int i = 0; i < nInt; i++){
		if(val_max < thisPath[i]){
			val_max = thisPath[i];
		}
	}
	return val_max;
}


//method definition
void PutUpandOutOption::printPath(){

	for(int i = 0;  i < nInt; i++){

		std::cout << thisPath[i] << "\n";

	}

}



//method definition
double PutUpandOutOption::getArithmeticPutPrice(int nReps){

	double variance = vol * vol * expiry;
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5 * variance;

	double movedSpot = spot * exp(r * expiry + itoCorrection);
	double thisSpot;
	double rollingSum = 0;
	double thisMax = 0.0;
	for (int i = 0; i < nReps; i++) {
		double thisGaussian = getOneGaussianByBoxMueller();
		thisSpot = movedSpot * exp(rootVariance * thisGaussian);
		thisMax=getMax();
		rollingSum += (thisSpot < strike && thisMax < b) ? (strike - thisSpot) : 0;
	}

	double mean = rollingSum / nReps;
	mean = mean * exp(-r * expiry);
	return mean;

}





