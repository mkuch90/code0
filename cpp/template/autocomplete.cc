#include "autocomplete.h"
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace example {

using namespace std;

void AutoComplete::BuildTrie(const vector<string>& words) {
	for (uint i = 1; i < words.size(); i++) {
		string w = words.at(i);
		dict[w] = i;
		Node* root = nullptr;
		// If this character is new to the trie, then we need a new root.
		if (roots.find(w.substr(0, 1)) == roots.end()) {
			root = new Node;
			root->l = w.substr(0, 1);
			root->word_completed = "";
			roots[root->l] = root;
			// Single character word.
			if (w.length() == 1) {

				root->word_completed = w;
				return;
			}
		}
		root = roots[w.substr(0, 1)];
		InsertWord(root, w, w);
	}
}
void AutoComplete::InsertWord(Node* n, string word, string r_chars) {
	string curr_char = r_chars.substr(0, 1);
	// Find the next character in the trie. If there is none, then 
	// create the new node.
	if (n->children.find(curr_char) == n->children.end()) {
		Node* new_node = new Node();
		new_node->l = curr_char;
		new_node->word_completed = "";
		(n->children)[curr_char] = new_node;

		// Word is not in trie, and we are at the end of the word.
		if (r_chars.length() == 1) {
			new_node->word_completed = word;
			return;
		}
		// Recurse on the new node.
		InsertWord(new_node, word, r_chars.substr(1));
		return;
	}
	// Word is  already in dict.
	if (r_chars.length() == 1) {
		return;
	}
	// Traverse down the tree to the found child.
	InsertWord((n->children)[curr_char], word, r_chars.substr(1));
}

// For all words that are teminal, collect them.
void AutoComplete::collectWords(Node* n, set<string>* words) {
	if (n->word_completed != "") {
		words->insert(n->word_completed);
	}
	for (auto it = n->children.begin(); it != n->children.end(); it++) {
		collectWords(it->second, words);
	}
}

// Get completion traverses teh trie maps each founc completion to a 
// rank.
std::map<int, string> AutoComplete::GetCompletion(string s) {
	string c = s.substr(0, 1);

	std::map<int, string> comp;
	if (roots.find(c) == roots.end()) {
		return comp;
	}
	Node* root = roots[c];
	Node* n = GetCompletionInternal(root, c);
	if(n == nullptr){
           return comp;
	}
	set<string> words;
	collectWords(n, &words);
	for (auto it = words.begin(); it != words.end(); it++) {
		comp[dict[*it]] = *it;
	}
	return comp;
}
// GetCompletionsInternal finds the node where completion ends.
Node* AutoComplete::GetCompletionInternal(Node* n, string s) {
	string curr_char = s.substr(0, 1);
	if (n->l == curr_char) {
		if (s.length() == 1) {
			return n;
		}
		if (n->children.find(curr_char) == n->children.end()) {
			return nullptr;
		}

		return GetCompletionInternal(n->children[curr_char], s.substr(1));
	}
	return nullptr;
}
}  // example
