#include "Utils.hpp"

#include "iostream"
#include "fstream"
#include "sstream"
#include <iomanip>

using namespace std;

bool ImportData(const string& inputFilePath, size_t& n, double& S, double*& w, double*& r) 
{
	ifstream file(inputFilePath);
	
	if (file.fail())
	{	
        return false;
	}
	
	string line;
	while (getline(file,line)) //questo ciclo while mi serve per memorizzare S dato nel file di input)
	{
		if (line.find("S") == 0) //file.find("S") restituisce la posizionedella stringa in cui si trova S --> sto cercando s all'inizio della riga
		{
			S = stod(line.substr(2)); // line.substr(2) estrae da line tutti i caratteri dalla seconda poszione in poi (salto la prima posizione perchè li trova ";"
		                             // stod(A) converte A in double
			break; // quando trovo S esco dal ciclo while					 
	    }
	}

	while (getline(file,line)) // come prima ma ora cerco n
	{
		if (line.find("n") == 0)
		{
			n = stoul(line.substr(2)); // stoul converte una stringa in numero
			break;
	    } 
	}	

    w = new double[n];
    r = new double[n];
 
 
	size_t i = 0;
	while (getline(file,line) and i < n)
	{
		if (line == "w;r") continue; // se la condzione dell'if è verificata con il comando continue si salta immediatamente alla iterazione successiva del while
		size_t j = line.find(";"); // memorizzo in j la posizione di ";" presente in line
		w[i] = stod(line.substr(0, j)); // prende i caratteri dalla posizione 0 alla posizione j (esclusa)
		r[i] = stod(line.substr(j+1));
		i++;
	}
	
	file.close();
	
	return true;
}	

double rate_of_return(size_t n, const double* w, const double* r)
{
	double rate = 0;
	for( size_t i=0; i<n; i++)
		rate += r[i] * w[i];
	return rate;
}	

double portfolio(double S, double rateofreturn)
{
	double V = (1 + rateofreturn) * S;
	return V;
}

bool ExportData(const string& outputFilePath, const size_t& n, const double* w, const double* r, const double& rateofreturn, const double& V, const double& S)
{
    ofstream file;
	file.open(outputFilePath);
	if (file.fail())
	{	
        return false;
	}
	
	file << "S = " << fixed << setprecision(2) << S << defaultfloat << ", n = " << n << endl;
	
	file << "w = [";
	for (size_t i=0; i<n; i++)
	{
		file << w[i];
		if (i < n-1)
		{	
	        file << " ";  //aggiungo spazio tra i valori
		}	
	}
	file << "]" << endl;
	file << "r = [";
	for (size_t i=0; i<n; i++)
	{
		file << r[i];
		if (i < n-1) 
		{
			file << " ";
		}
	}
	file << "]" << endl;
	
	file <<  "Rate of return of the portfolio:" << fixed << setprecision(4) << rateofreturn << endl;
	file << "V: " << fixed << setprecision(2) << V << endl;
	
	file.close();
	
	return true;
}
	