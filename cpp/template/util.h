
#include <string>
#include <vector>

namespace example {

using namespace std;

namespace StringUtil {

// Splits a string on a delimiter and puts the output into an output
// string vector.
// Notes: This function uses recursion, so long strings could lead to
// a stack overflow.
extern void Split(string word, string delim, vector<string>* split);

// Takes a string word and parses it into val.
// Note, on the first non-integer character the function quits.
// Example "123abc" -> 123
//         "abc123" -> 0
extern int ParseInt(string word);
}

namespace FileUtil {

// Given a string filename, this function opens and reads the file
// outputting the contents line by line into the contents vector.
extern bool GetContents(string filename, vector<string>* contents);

// Given a string filename, this function opens and writes to the file
// the contents vector line by line.
extern bool WriteContents(string filename, const vector<string>& contents);
}

extern void PrintLine(string line);

}  // example
