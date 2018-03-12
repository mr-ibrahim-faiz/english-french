#include "ofuse.h"

#include<fstream>
using std::fstream;

#include<chrono>
using std::chrono::system_clock;

#include<algorithm>
using std::random_shuffle;

#include<stdexcept>
using std::exception;

// shuffles vector elements
template<typename T>
void shuffle_vector(vector<T>& vec) 
// rearranges the elements of a vector vec randomly
{
	unsigned seed = (unsigned)system_clock::now().time_since_epoch().count();
	srand(seed);
	random_shuffle(vec.begin(), vec.end());
}

template void shuffle_vector<int>(vector<int>& vec);

// creates file if it doesn't exist
void create_file_if(const string& filename)
// checks if a file exists
// creates it if it doesn't
{
	fstream file;
	file.open(filename);
	if (!file.is_open())
		fstream(filename, ios::out);
	file.close();	
}

// checks if a specific element is present in a vector
template<typename T>
bool is_present(const T& x, const vector<T>& vec)
// searches a value in a vector
// returns true if it finds it
// returns false otherwise
{
	for (T t : vec)
		if (t == x)
			return true;
	return false;
}

template bool is_present<int>(const int& x, const vector<int>& vec);

// writes elements of a vector on a file
template<typename T>
void write_elements(const vector<T>& vec, const string& file_name, ios::fmtflags flag, const string& delimiter, const string& period)
// write elements of vec on file_name
// elements are delimited by the delimiter
// the writing is ended by the period
{
	fstream file;
	create_file_if(file_name);
	file.open(file_name, flag);

	if (file.is_open()) {
		size_t size = vec.size();

		if (size == 0)
			file << period;
		else
			for (size_t i = 0; i < size; ++i)
				file << vec[i] << ((i != size - 1) ? delimiter : period);

		file.close();
	}
	else
		throw exception("(write vector elements) unable to open file.");
}

template void write_elements<int>(const vector<int>& vec, const string& file_name, ios::fmtflags flag, const string& delimiter, const string& period);