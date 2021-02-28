
#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>

std::string getLastName();
std::string getFirstName();

std::string getStreetNum();

//TODOS
std::string getStreetAddress(); //returns address string from file
std::string getCity();
std::string getState();
std::string getZipCode();

int getInitialBalance(std::string deposit); // currently returns income

std::string getDeposit();
//int getWithdrawal(std::string deposit);
std::string getLoans();
double getPurchases(std::string deposit);

//other supporting functions
double getRandomPercentage();
double getDecimal();
double getIncomeBasedOnDeposit(std::string s_deposit);
double getRandomNormalLinearizedVariable(double mean, double stddev);

void Test();

/*
double getRandomPercentage();
Returns a random double in a percentage form between 0.01 - 99.99.Used for a lot of random generation.

double getDecimal();
Returns a double decimal between 0.01 and .99 to be added to a base.

double getIncomeBasedOnDeposit(std::string s_deposit);
Calculates total year income based on the calculated deposit string.
double getRandomNormalLinearizedVariable(double mean, double stddev);
Returns a random approximate normalized value given a meanand standard deviation.Used to keep most data within reasonable ranges.

std::string getLastName();
Returns a random last name string gotten from LastNames.txt file.

std::string getFirstName();
Returns a random first name string gotten from FirstNames.txt file.

std::string getStreetNum();
Returns a random street num represented as a string.

std::string getStreetAddress();
Returns a random street name string gotten from StreetNames.txt file.

std::string getCity();
Returns a random city name string gotten from CityNamess.txt file.

std::string getState();
Returns a random state name string gotten from StateNames.txt file.Returns the two character acronym.

std::string getZipCode();
Returns a random five digit zip code represented as a string.

int getInitialBalance(std::string deposit);
Returns the initial balance for a month in an integer.Based on savings data for each income bracket.Uses random linear normalization to another level of scrambled return values.

std::string getDeposit();
Takes a random percentageand generates a static weighted monthly deposit amount.Returns as a long string, each month separated by commas.Not normally weighted like other functions.

std::string getLoans();
Returns the loans owed for each month as a long string.Customers can either have no loans, varied loans, or static loans across 12 months.Uses two levels of random normal scrambling.

double getPurchases(std::string deposit);
Returns the amount of purchases per month based on rough percentage of income.Those with higher incomes spend less percentage of monthly income, one level of normalized randomness.
*/


#endif
