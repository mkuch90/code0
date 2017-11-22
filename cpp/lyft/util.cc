#include "util.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <iostream>

namespace example {
using namespace std;
namespace StringUtil {

void Split(string word, string delim, vector<string>* split) {
	if (word.length() == 0) {
		return;
	}
	size_t place = word.find(delim);

	if (place == string::npos) {
		split->push_back(word);
		return;
	}
	split->push_back(word.substr(0, place));
	Split(word.substr(place + delim.length()), delim, split);
}

int ParseInt(string word) {
	stringstream s(word);
	int out_val = 0;
	s >> out_val;
	return out_val;
	;
}
}  // StringUtil

namespace FileUtil {

bool GetContents(string filename, vector<string>* contents) {
	string line;
	ifstream myfile(filename);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			contents->push_back(line);
		}
		myfile.close();
		return true;
	}

	cout << "Unable to open file";
	return false;
}

bool WriteContents(string filename, const vector<string>& contents) {
	std::ofstream out(filename);
	if (out.is_open()) {
		for (string s : contents) {
			out << s << "\n";
		}
		out.close();
		return true;
	}
	return false;
}

}  // FileUtil

void PrintLine(string line) { cout << line << "\n"; }

}  // example
