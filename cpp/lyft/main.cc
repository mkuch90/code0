#include <gflags/gflags.h>
#include <ctime>
#include <iostream>
#include <string>
#include "template/autocomplete.h"
#include "template/util.h"

using namespace std;
using namespace example;

int main(int argc, char** argv) {
	int word_count = StringUtil::ParseInt(argv[0]);
	int comp_count = StringUtil::ParseInt(argv[1]);

	vector<string> words;
	for (int i = 2; i < word_count + 2; i++) {
		words.push_back(argv[i]);
	}

	vector<string> comps;
	int min_test = 2 + word_count;

	for (int i = min_test; i < min_test + comp_count; i++) {
		comps.push_back(argv[i]);
	}

	AutoComplete ac(words);
	for (string s : comps) {
		auto res = ac.GetCompletion(s);

		for (auto it = res.begin(); it != res.end(); it++) {
			cout << it->second << " (" << it->first << ")\n";
		}
	}

	return 0;
}
