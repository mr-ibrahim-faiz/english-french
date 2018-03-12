#include "english-french.h"
#include "ofuse.h"

#include<iostream>
using std::cin;
using std::cerr;
using std::cout;
using std::endl;

#include<stdexcept>
using std::exception;
using std::runtime_error;

vector<string> left_words;
vector<string> right_words;
vector<int> left_messed_up;
vector<int> right_messed_up;

int main() 
try
{
	const string filename { "english_french.txt" };
	const string practice_filename_left { "messed_up_left.txt" };
	const string practice_filename_right { "messed_up_right.txt" };
	get_words(filename);

	while (true) {
		display_menu();
		string choice { "" };
		getline(cin, choice);

		if (choice == "exit" || choice == "x")
			break;
		else if (choice.size() != 1)
			choice = "?";

		switch (choice[0])
		{
		case '1':
		{
			cout << endl;
			if (!left_words.empty())
				vocabulary_quiz(left_words, right_words, left_messed_up, practice_filename_left);
			else
				cout << "No words available." << endl;
		}
		break;

		case '2':
		{
			cout << endl;
			if (!right_words.empty())
				vocabulary_quiz(right_words, left_words, right_messed_up, practice_filename_right);
			else
				cout << "No words available." << endl;
		}
		break;

		case '3':
		{
			cout << endl;
			const char period { '$' };
			left_messed_up = get_indexes(practice_filename_left, period);

			if (!left_messed_up.empty())
				practice_vocabulary(left_words, right_words, left_messed_up);
			else
				cout << "No words available." << endl;
		}
		break;

		case '4':
		{
			cout << endl;
			const char period { '$' };
			right_messed_up = get_indexes(practice_filename_right, period);

			if (!right_messed_up.empty())
				practice_vocabulary(right_words, left_words, right_messed_up);
			else
				cout << "No words available." << endl;
		}
		break;

		default:
			cout << "\nPlease enter a valid choice !" << endl;
			break;
		}
		cout << endl;
	}

	cout << "\nGoodbye." << endl;

	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << endl;
	return 1;
}
catch (...) {
	cerr << "Error: unknown exception caught." << endl;
	return 2;
}