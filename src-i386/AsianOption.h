#include<vector>

class PutUpandOutOption{
public:

	//constructor
	PutUpandOutOption(
		int nInt_,
		double strike_,
		double spot_,
		double vol_,
		double r_,
		double expiry_,
		double b_
		);

	//destructor
	~PutUpandOutOption(){};

	//methods
	void generatePath();
	double getMax();
	void printPath();
	double getArithmeticPutPrice(int nReps);
	
	//members
	std::vector<double> thisPath;
	int nInt;
	double strike;
	double spot;
	double vol;
	double r;
	double expiry;
	double b;

};
