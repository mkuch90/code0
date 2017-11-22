#include "template/lib.h"
#include <string>
#include "gtest/gtest.h"

using std::string;

namespace example {

TEST(HelloTest, GetGreet) {
	Lib lib("name");
	EXPECT_EQ(lib.GetName(), "name");
}
};
