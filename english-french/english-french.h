#pragma once

#include<string>
using std::string;
using std::wstring;

#include<vector>
using std::vector;

extern vector<wstring> left_words;
extern vector<wstring> right_words;
extern vector<int> left_messed_up;
extern vector<int> right_messed_up;

// displays menu
void display_menu();

// gets a shuffled vector of indexes
vector<int> get_random_indexes(const size_t&);

// gets words from file
void get_words(const string&);

// gets indexes from files
vector<int> get_indexes(const string&, const char&);

// displays scores
void display_score(const size_t&, const size_t&);

// displays messed up words
void display_messed_up_words(const size_t&, const size_t&, const vector<int>&, const vector<wstring>&, const vector<wstring>&);

// main function
void vocabulary_quiz(const vector<wstring>&, const vector<wstring>&, vector<int>&, const string&);

// vocabulary quiz main function
int test_vocabulary(const vector<wstring>&, const vector<wstring>&, vector<int>&);

// main practice function
void practice_vocabulary(const vector<wstring>&, const vector<wstring>&, vector<int>&);
