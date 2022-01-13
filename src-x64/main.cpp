#include <Rcpp.h>
#include<vector>
#include<ctime>
#include<cstdlib>
#include"AsianOption.h"
#include"getVecMean.h"
#include"getVecStdDev.h"

using std::vector;
using std::cout;
using std::cin;
using namespace Rcpp;

// [[Rcpp::export]]
double getArithmeticPutPrice(
    int nInt,
    double strike,
    double spot,
    double vol,
    double r,
    double expiry,
    double b,
    int nReps
){

	// set the seed
	srand( time(NULL) );

	//create a new instance of class
	PutUpandOutOption myInformation(nInt, strike, spot, vol, r, expiry,b);
	
	//run Monte Carlo to obtain theoretical price of Asian options
	return myInformation.getArithmeticPutPrice(nReps);
}
