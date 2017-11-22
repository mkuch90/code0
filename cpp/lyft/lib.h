#ifndef LIB_LIB_H_
#define LIB_LIB_H

#include <string>
using namespace std;

namespace example {
class Lib {
       public:
	Lib(std::string name);
	string GetName();

       private:
	string name_;
};

}  // example
#endif  // LIB_LIB_H_
