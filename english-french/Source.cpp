#include<iostream>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::ws;
using std::streamsize;

#include<vector>
using std::vector;

#include<string>
using std::string;

#include<limits>
using std::numeric_limits;

#include<algorithm>
using std::random_shuffle;

#include<ctime>

#include<fstream>
using std::ofstream;
using std::ifstream;

void get_choice() {
	cout << "[1] English-french" << endl;
	cout << "[2] French-english" << endl;
	cout << "[x] Exit" << endl;
}

int main() {
	vector<int> indexes;
	vector<string> english_words;
	vector<string> french_words;
	string input_word {""};
	int score {0};

	string line {""};
	ifstream dictionary("english_french.txt");
	if (dictionary.is_open()) {
		while (getline(dictionary, line, ':')) {
			english_words.push_back(line);
			dictionary >> ws;
			getline(dictionary, line);
			french_words.push_back(line);
		}
		dictionary.close();
	}
		
	else
		cerr << "Error: Unable to open files." << endl;

	get_choice();

	indexes.reserve(english_words.size());
	for (unsigned int i = 0; i < english_words.size(); ++i)
		indexes.push_back(i);

	char choice {'?'};
	while (cin >> choice) {
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		srand((unsigned int)time(NULL));
		random_shuffle(indexes.begin(), indexes.end());

		switch (choice) {
		case '1':
		{
			vector<int> messed_up_indexes;
			cout << endl;
			for (vector<int>::iterator it = indexes.begin(); it != indexes.end(); ++it) {
				cout << english_words[*it] << ": ";
				getline(cin, input_word);

				if (french_words[*it] == input_word) {
					++score;
				}
				else
					messed_up_indexes.push_back(*it);
			}

			cout << "\nResults: " << score << "\\" << english_words.size() << "." << endl;
			if (score == english_words.size())
				cout << "Perfect score !" << endl;
			else if (score == 0)
				cout << "Not Good At All. Try Again." << endl;
			else {}

			if (score != english_words.size()) {
				cout << "\nMessed up words:\n" << endl;
				for (vector<int>::iterator it = messed_up_indexes.begin(); it != messed_up_indexes.end(); ++it)
					cout << french_words[*it] << ": " << english_words[*it] << endl;
			}

			score = 0;
		}
			break;

		case '2':
		{
			vector<int> messed_up_indexes;
			cout << endl;
			for (vector<int>::iterator it = indexes.begin(); it != indexes.end(); ++it) {
				cout << french_words[*it] << ": ";
				getline(cin, input_word);

				if (english_words[*it] == input_word) {
					++score;
				}
				else
					messed_up_indexes.push_back(*it);
			}

			cout << "\nResults: " << score << "\\" << french_words.size() << "." << endl;
			if (score == french_words.size())
				cout << "Perfect score !" << endl;
			else if (score == 0)
				cout << "Not Good At All. Try Again." << endl;
			else {}

			if (score != french_words.size()) {
				cout << "\nMessed up words:\n" << endl;
				for (vector<int>::iterator it = messed_up_indexes.begin(); it != messed_up_indexes.end(); ++it)
					cout << french_words[*it] << ": " << english_words[*it] << endl;
			}

			score = 0;
		}
		
			break;

		case 'x':
			cout << "\nGoodbye !" << endl;
			return 0;

		default:
			cout << "\nPlease enter a valid choice !" << endl;
			break;
		}

		cout << endl;
		get_choice();
	}

	return 0;
}