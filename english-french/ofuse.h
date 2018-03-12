#pragma once

#include<iostream>
using std::ios;

#include<string>
using std::string;

#include<vector>
using std::vector;

// shuffles vector elements
template<typename T>
void shuffle_vector(vector<T>&);

// creates file if it doesn't exist
void create_file_if(const string&);

// checks if a specific element is present in a vector
template<typename T>
bool is_present(const T&, const vector<T>&);

// writes elements of a vector on a file
template<typename T>
void write_elements(const vector<T>&, const string&, ios::fmtflags, const string&, const string&);