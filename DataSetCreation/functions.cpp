#include "functions.hpp"

#include <istream>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <random>

double getDecimal() {

	float temp = (float)rand() / RAND_MAX; //get double between 0-1, 0.76543

	std::string num = std::to_string(temp); //create string

	num.erase(4); //cut string, 0.76

	double returndouble = stod(num); //turn it back into double

	if (returndouble == 0.00) {

		returndouble += 0.01;
	}

	if (returndouble == 1.00) {

		returndouble -= 0.01;
	}

	return returndouble; //return double
}

double getRandomPercentage() {
	//returns a random percent of the form xx.xx

	int percent1 = rand() % 100; //returns between 0 - 99
	//double percent2 = rand(); //returns between 0 - 1
	double weight = (double)percent1 + getDecimal();
	return weight;
}

//supporting function used to get income
double getIncomeBasedOnDeposit(std::string s_deposit) {

	std::string income;
	double r_income;

	for (std::size_t i = 0; i < s_deposit.size(); i++) {

		if (s_deposit[i] == ',') {

			income = s_deposit.erase(i);
		}
	}

	r_income = stod(income);
	r_income *= 12;
	return r_income;
}

double getRandomNormalLinearizedVariable(double mean, double stddev) { //NEED TO COMMENT THIS LATER

	double percent = getRandomPercentage();
	int floor = 0; //floor
	int ceiling = 0; //ceiling
	int random = 0;

	if (percent < 0.1) { //old .1

		floor = mean - (4 * stddev);
		ceiling = mean - (3 * stddev);
		random = rand() % ceiling;
	}
	else if (percent < 2.2) { //old 2.2

		floor = mean - (3 * stddev);
		ceiling = mean - (2 * stddev);

		random = rand() % (ceiling - floor) + floor; 
	}
	else if (percent < 15.8) { //old 15.8

		floor = mean - (2 * stddev);
		ceiling = mean - (1 * stddev);

		random = rand() % (ceiling - floor) + floor;
	}
	else if (percent < 49.9) { //old 49.9

		floor = mean - (1 * stddev);
		ceiling = mean - (0 * stddev);

		random = rand() % (ceiling - floor) + floor;
	}
	else if (percent < 84.0) { //old 84

		floor = mean + (0 * stddev);
		ceiling = mean + (1 * stddev);

		random = rand() % (ceiling - floor) + floor;
	}
	else if (percent < 97.6) { //old 97.6

		floor = mean + (1 * stddev);
		ceiling = mean + (2 * stddev);

		random = rand() % (ceiling - floor) + floor;
	}
	else if (percent < 99.7) { //old 99.7

		floor = mean + (2 * stddev);
		ceiling = mean + (3 * stddev);

		random = rand() % (ceiling - floor) + floor;
	}
	else if (percent < 100.0) { //old 100.0

		floor = mean + (3 * stddev);
		ceiling = mean + (4 * stddev); //need ceiling limt, +4 stddev?

		random = rand() % (ceiling - floor) + floor;
	}

	return random;
}


std::string getFirstName() {
	
	std::size_t lineno = 1;
	int linetarget = (rand() % 146) + 1;
	std::ifstream myfile;
	std::string linestr;

	myfile.open("FirstNames.txt");

	while (lineno < linetarget) {

		std::getline(myfile, linestr);
		lineno++;
	}

	myfile.close();
	return linestr;
}

std::string getLastName(){

	std::size_t lineno = 1;
	int linetarget = (rand() % 146) + 1;
	std::ifstream myfile;
	std::string linestr;

	myfile.open("LastNames.txt");

	while (lineno < linetarget) {

		std::getline(myfile, linestr);
		lineno++;
	}

	myfile.close();
	return linestr;
}

std::string getStreetNum() {

	int streetnumber = (rand() % 30000 + 200);
	std::string streetstring = std::to_string(streetnumber);
	
	return streetstring;
}

std::string getStreetAddress() {

	std::size_t lineno = 1;
	int linetarget = (rand() % 100) + 1;
	std::ifstream myfile;
	std::string linestr;

	myfile.open("StreetNames.txt");

	while (lineno < linetarget) {

		std::getline(myfile, linestr);
		lineno++;
	}

	myfile.close();
	return linestr;
}

std::string getCity() {

	std::size_t lineno = 1;
	int linetarget = (rand() % 100) + 1;
	std::ifstream myfile;
	std::string linestr;

	myfile.open("CityNames.txt");

	while (lineno < linetarget) {

		std::getline(myfile, linestr);
		lineno++;
	}

	myfile.close();
	return linestr;
}

std::string getState() {

	std::size_t lineno = 1;
	int linetarget = (rand() % 50) + 1;
	std::ifstream myfile;
	std::string linestr;

	myfile.open("StateNames.txt");

	while (lineno < linetarget) {

		std::getline(myfile, linestr);
		lineno++;
	}

	myfile.close();
	return linestr;
}

std::string getZipCode() {

	int zipcode = (rand() % 30000 + 10000);
	std::string zipcodestring = std::to_string(zipcode);

	return zipcodestring;
}

std::string getDeposit() { //need 12 of each of these
	//data for this method is in the server, using weighted distrubtion, pinned

	double weight = getRandomPercentage();
	int deposit = 0;
	double t_deposit;

	//using if else sytax
	if (weight < 11.3) {

		//gets random number between 5000 and 10000
		deposit = rand() % 5000 + 5000;  //////////////////////////////ADDED INCOME FLOOR
		deposit /= 12;
	}
	else if (weight < 19.3) {

		//gets random number between 10000 and 14999
		deposit = rand() % 5000 + 10000;
		deposit /= 12;
	}
	else if (weight < 33.2) {

		//gets random number between 15000 and 24999
		deposit = rand() % 10000 + 15000;
		deposit /= 12;
	}
	else if (weight < 45.0) {

		//gets random number between 25000 and 34999
		deposit = rand() % 10000 + 25000;
		deposit /= 12;
	}
	else if (weight < 59.5) {

		//gets random number between 35000 and 49999
		deposit = rand() % 15000 + 35000;
		deposit /= 12;
	}
	else if (weight < 76.4) {

		//gets random number between 50000 and 74999
		deposit = rand() % 25000 + 50000;
		deposit /= 12;
	}
	else if (weight < 85.6) {

		//gets random number between 75000 and 99999
		deposit = rand() % 25000 + 75000;
		deposit /= 12;
	}
	else if (weight < 94) {

		//gets random number between 100000 and 149999
		deposit = rand() % 50000 + 100000;
		deposit /= 12;
	}
	else if (weight < 96.9) {

		//gets random number between 150000 and 199999
		deposit = rand() % 50000 + 150000;
		deposit /= 12;
	}
	else if (weight < 99.7) {

		//gets random number between 200000 and 500000
		deposit = rand() % 300000 + 200000;
		deposit /= 12;
	}
	else if (weight < 100.0) {

		//gets random number between 500000 and 1000000
		deposit = rand() % 500000 + 500000;
		deposit /= 12;
	}

	t_deposit = (double)deposit +getDecimal(); /////////////////////////////////////////CHANGE HERE
	std::string s_deposit = std::to_string(t_deposit);

	//need to get rid of tailing 0's
	for (std::size_t i = 0; i < s_deposit.size(); i++) {

		bool remove = false;

		if (s_deposit[i] == '.') {

			remove = true;
			i += 3;
		}

		if (remove == true) {

			s_deposit.erase(i);
		}
	}

	std::string r_deposit = s_deposit + ',' + s_deposit + ',' + s_deposit + ',' + s_deposit + ','
						  + s_deposit + ',' + s_deposit + ',' + s_deposit + ',' + s_deposit + ','
						  + s_deposit + ',' + s_deposit + ',' + s_deposit + ',' + s_deposit;
	  
	return r_deposit;
	//return r_deposit;
}

int getInitialBalance(std::string deposit) { 
	//use linear normal approximation

	int income = (int)getIncomeBasedOnDeposit(deposit);
	int savings = 0;
	int stddev = 0;

	if (income < 25000) {

		savings = 6021;
		stddev = 1000;
	}
	else if (income < 44999) {

		savings = 11719;
		stddev = 2000;
	}
	else if (income < 69999) {

		savings = 13179;
		stddev = 2000;
	}
	else if (income < 114999) {

		savings = 15333;
		stddev = 2000;
	}
	else if (income < 159999) {

		savings = 37645;
		stddev = 3000;
	}
	else {

		savings = 117771;
		stddev = 10000;
	}

	int initialbalance = (int)getRandomNormalLinearizedVariable((double)savings, (double)stddev);
	/*
	double negative = getRandomPercentage();
	if (negative < 10.00) { //there is a 10% chance that the person is in debt

		initialbalance = initialbalance - (2 * initialbalance);
	} */

	return initialbalance;
}

/*
int getWithdrawal(std::string deposit) {

}
*/

std::string getLoans() {

	//80% have debt, ranges between 250-1500 per month, can use normal distribution or 
	//your process in place for other variables, of those, half dont change each month, and half vary slightly
	double mean = 875.;
	double stddev = 200.;
	double percent = getRandomPercentage();
	std::string noloans;
	std::string staticloans;
	std::string dynamicloans;

	double loan = getRandomNormalLinearizedVariable(mean, stddev);
	std::string s_loan = std::to_string(loan);

	if (percent < 40.00) {
		//condition for static loan

		for (std::size_t i = 0; i < 13; i++) {

			if (i == 12) {

				std::string temp = s_loan;
				dynamicloans = dynamicloans + temp; //if last just add temp
			}
			else {
				std::string temp = s_loan + ',';
				staticloans = staticloans + temp;
			}
		}

		return staticloans;
	}
	else if (percent < 80.00) {
		//condition for dynamic loan

		for (std::size_t i = 0; i < 12; i++) {

			double randomloan = getRandomNormalLinearizedVariable(loan, (.2 * loan));
			std::string s_randomloan = std::to_string(randomloan);

			if (i == 11) {

				std::string temp = s_randomloan + ',';
				dynamicloans = dynamicloans + temp; //if last just add temp
			}
			else {

				std::string temp = s_randomloan + ',';
				dynamicloans = dynamicloans + temp;
			}
		}


		return dynamicloans;
	}
	else {
		//condition for no loans

		noloans = "0,0,0,0,0,0,0,0,0,0,0,0,";

		return noloans;
	}

	//return "its fucking 4am";
}

double getPurchases(std::string deposit) {
	//use reasonable estimates, one estimate sasy about 76% of yearly income
	//get random linearized estimate between 61-91 centered at 76 standard dev is 5
	//do we assume the same amout of money spent each month, or should i normalize the normalizaiton for EXTRA randomness

	//so take 6 income groups, spllit them up, less income means spend more
	//after i split it up, randomize the amount the spend that month using linearization
	double income = getIncomeBasedOnDeposit(deposit);
	double purchasepercent  = 0.;
	double stddev = 0.;
	double purchases = 0.;
	double r_purchases = 0.;
	double monthlyincome = 0.;

	if (income < 25000.) { //61-66

		purchasepercent = .63;
		stddev = .1;
	}
	else if (income < 44999.) {//66-71

		purchasepercent = .68;
		stddev = .1;
	}
	else if (income < 69999.) { //71-76

		purchasepercent = .73;
		stddev = .1;
	}
	else if (income < 114999.) {//76-81

		purchasepercent = .78;
		stddev = .1;
	}
	else if (income < 159999.) {//81-86

		purchasepercent = .83;
		stddev = .1;
	}
	else { //86-91

		purchasepercent = .88;
		stddev = .1;
	}
	
	
	purchases = (purchasepercent * income)/12;

	monthlyincome = income / 12;

	//normalize AGAIN and add a random decimal
	r_purchases = getRandomNormalLinearizedVariable(purchases, (.1 * monthlyincome))+getDecimal();

	//now take monthy purchases, and normalize that with stddev = .1*monthyincome


	return r_purchases;
}

void Test() {

//     std::string s_deposit = "2855255.5252";
//     std::string * s_deposit_p = &s_deposit;
//     // std::cout << s_deposit_p << std::endl;
//     printf("%s\n",s_deposit_p);


//     double IntDeposit = std::stod(s_deposit_p->c_str());

//     std::cout << "stod(\"" << s_deposit << "\") is "
//     << IntDeposit << '\n';

//     printf("%f\n",IntDeposit);


//     double * IntDeposit_p = &IntDeposit;    
//     printf("The double pointer is :%f\n",IntDeposit_p);

//     //need to get rid of tailing 0's
//     std::string CutString = "123,45";

//     for (std::size_t i = 0; i < CutString.size(); i++) {

//         bool remove = false;

//         if (CutString[i] == ',') {

//             remove = true;
//             i ++;
//         }

//         if (remove == true) {

//             CutString.erase(i-1);
//         }

//     }

//     printf("%s\n",CutString.c_str() );
// }


// int myint1 = stoi(str1); 
// int myint2 = stoi(str2); 
// int myint3 = stoi(str3); 

// cout << "stoi(\"" << str1 << "\") is "
// << myint1 << '\n'; 


//data is based on Deposits*12 
//based on that assign this value to Normal distribution according to savings (centered around savings)


//ex 24 000
//savings would be 0 in 6000$

}



