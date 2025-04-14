#include <iostream>
#include <fstream>
#include <sstream> 
#include <iomanip>
#include "Utils.hpp"

using namespace std;

int main()
{
	string input_file = "data.txt";
	size_t n = 0;
	double* w = nullptr;
    double* r = nullptr;
	double S = 0;
	
	if (!ImportData(input_file, n, S, w, r))
	{
		return 1;
	}
	
	double rate = rate_of_return(n, w, r);
	
	double V = portfolio(S, rate);
	
	string output_file = "result.txt";
	if (!ExportData(output_file, n, w, r, rate, V, S))
	{
		return 2;
	}	
	
	delete [] w;
	delete [] r;
	
    return 0;
}
