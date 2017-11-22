#include "lib.h"
#include <string>

namespace example {

using namespace std;
Lib::Lib(string name) { name_ = name; }
string Lib::GetName() { return name_; }

}  // example
