#pragma once
#include <iostream>

using namespace std;


bool ImportData(const string& inputFilePath, size_t& n, double& S, double*& w, double*& r);
double rate_of_return(size_t n, const double* w, const double* r);
double portfolio(double S, double rateofreturn);
bool ExportData(const string& outputFilePath, const size_t& n, const double* w, const double* r, const double& rateofreturn, const double& V, const double& S);