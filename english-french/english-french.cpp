#include "english-french.h"
#include "ofuse.h"

#include<iostream>
using std::ws;
using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::streamsize;

#include<fstream>
using std::ifstream;

#include<stdexcept>
using std::exception;
using std::runtime_error;

#include<chrono>
using std::chrono::system_clock;

#include<algorithm>
using std::find;
using std::random_shuffle;

#include<limits>
using std::numeric_limits;

//const string practice_filename { "messed_up.txt" };

// displays menu
void display_menu()
// displays main menu
// informs the user about available choices
{
	cout << "[1] English-french" << endl;
	cout << "[2] French-english" << endl;
	cout << "[3] Practice English-french" << endl;
	cout << "[4] Practice French-english" << endl;
	cout << "[x] Exit" << endl;
}

// gets a shuffled vector of indexes
vector<int> get_random_indexes(const size_t& size)
// shuffles a vector of integers ranging from 0 to size-1 and returns it
{
	vector<int> indexes;
	indexes.reserve(size);
	for (unsigned int i = 0; i < size; ++i)
		indexes.push_back(i);

	shuffle_vector(indexes);

	return indexes;
}

// gets words from file
void get_words(const string& filename)
// gets words from file named filename
// stores them in left_words and right_words
// syntax "left_word: right_word"
{
	string word { "" };

	create_file_if(filename);
	ifstream dictionary(filename);
	if (dictionary.is_open()) {
		while (getline(dictionary, word, ':')) {
			left_words.push_back(word);
			dictionary >> ws;
			getline(dictionary, word);
			right_words.push_back(word);
		}
		dictionary.close();

		if (left_words.size() != right_words.size())
			throw exception("(retrieve words) size mismatch.");
	}
	else
		throw runtime_error("(get words) unable to open file.");
}

// gets indexes from files
vector<int> get_indexes(const string& filename, const char& period)
// retrieves indexes from filename
// returns a vector of integers containing the retrieved values
{
	vector<int> indexes;

	create_file_if(filename);
	ifstream file(filename);
	if (file.is_open()) {
		int index { 0 };
		while (file >> index)
			indexes.push_back(index);
		
		file.clear();
		file.ignore(numeric_limits<streamsize>::max(), period);
	}
	else
		throw runtime_error("(get indexes) unable to open file.");

	return indexes;
}

// displays scores
void display_score(const size_t& score, const size_t& size) {
	cout << "\nResults: " << score << "\\" << size << "." << endl;
	if (score == size)
		cout << "Perfect score !" << endl;
	else if (score == 0)
		cout << "Not Good At All. Try Again." << endl;
	else {}
}

// displays messed up words
void display_messed_up_words(const size_t& score, const size_t& size, const vector<int>& messed_up, const vector<string>& left, const vector<string>& right) {
	if (score != size) {
		cout << "\nMessed up words:\n" << endl;
		for (unsigned i = 0; i < messed_up.size(); ++i)
			cout << left[messed_up[i]] << ": " << right[messed_up[i]] << endl;
	}
}

// main quiz function
void vocabulary_quiz(const vector<string>& left, const vector<string>& right, vector<int>& messed_up, const string& practice_filename) {
	const char cperiod { '$' };
	const string& sdelimiter { " " };
	const string& speriod { " $" };
	messed_up = get_indexes(practice_filename, cperiod);
	size_t score = test_vocabulary(left, right, messed_up);
	write_elements(messed_up, practice_filename, ios::out, sdelimiter, speriod);

	size_t size = left.size();
	display_score(score, size);
	display_messed_up_words(score, size, messed_up, left, right);
}

// vocabulary quiz main function
int test_vocabulary(const vector<string>& left, const vector<string>& right, vector<int>& messed_up_indexes)
// displays a word and waits for the user's guess
// keeps track of the score i.e. number of right guesses
// keeps track of the failed words
{
	if (left.size() != right.size())
		throw exception("(vocabulary quiz) size mismatch.");

	size_t size = left.size();
	vector<int> indexes = get_random_indexes(size);
	
	int score { 0 };
	for (unsigned int i = 0; i < size; ++i) {
		int index = indexes[i];
		cout << left[index] << ": ";

		string answer { "" };
		getline(cin, answer);

		if (right[index] == answer) {
			// removes the index from indexes if present
			vector<int>::iterator it = find(messed_up_indexes.begin(), messed_up_indexes.end(), index);
			if (it != messed_up_indexes.end())
				messed_up_indexes.erase(it);
			++score;
		}
		else 
			if(!is_present(index, messed_up_indexes))
				messed_up_indexes.push_back(index);
	}
	
	return score;
}

// main practice function
void practice_vocabulary(const vector<string>& left, const vector<string>& right, vector<int>& messed_up)
{
	size_t size = messed_up.size();
	int score { 0 };
	vector<int> failed;

	shuffle_vector(messed_up);

	for (unsigned int i = 0; i < size; ++i) {
		int index = messed_up[i];
		cout << left[index] << ": ";

		string answer { "" };
		getline(cin, answer);

		if (right[index] == answer)
			++score;
		else
			failed.push_back(index);
	}

	display_score(score, size);
	display_messed_up_words(score, size, failed, left, right);
}