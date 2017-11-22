#ifndef LIB_LIB_H_
#define LIB_LIB_H

#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
struct Node {
	string l;  // letter in the node;
	std::map<string, Node*> children;
	// The last node on a comleted word contains the word.

	string word_completed;
};

namespace example {
class AutoComplete {
       public:
	AutoComplete(vector<string> dict) { BuildTrie(dict); }
	std::map<int, string> GetCompletion(string s);

       private:
	void BuildTrie(const vector<string>& dict);
	void InsertWord(Node* n, string word, string r_chars);
	Node* GetCompletionInternal(Node* n, string s);

	void collectWords(Node* n, set<string>* words);
	std::unordered_map<string, int> dict;
	std::unordered_map<string, Node*> roots;
};

}  // example
#endif  // LIB_LIB_H_
