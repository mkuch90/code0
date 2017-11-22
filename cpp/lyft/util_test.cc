#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "template/util.h"

namespace example {
using namespace std;

TEST(StringUtilTest, TestSplit) {
	vector<string> lines;
	EXPECT_TRUE(
	    FileUtil::GetContents("template/testdata/testcsv.txt", &lines));
	bool entered_loop = false;
	for (const string& line : lines) {
		vector<string> split;
		StringUtil::Split(line, ",", &split);
		EXPECT_EQ(split.size(), 3);
		entered_loop = true;
	}
	EXPECT_TRUE(entered_loop);
}
TEST(StringUtilTest, TestParseInt) {
	EXPECT_EQ(StringUtil::ParseInt("1"),1);
	EXPECT_EQ(StringUtil::ParseInt("0"),0);
	EXPECT_EQ(StringUtil::ParseInt("100"),100);
	EXPECT_EQ(StringUtil::ParseInt("-100"),-100);
	EXPECT_EQ(StringUtil::ParseInt("123abc"),123);
	EXPECT_EQ(StringUtil::ParseInt("abc123"),0);
}

TEST(FileUtilTest, TestGetContents) {
	vector<string> lines;
	EXPECT_TRUE(
	    FileUtil::GetContents("template/testdata/testfile1.txt", &lines));
	EXPECT_EQ(lines.size(), 6);
	EXPECT_EQ(lines.at(5), "line6");
}

TEST(FileUtilTest, TestWriteContents) {
	vector<string> lines;
	lines.push_back("Line 1");
	lines.push_back("Line 2");
	lines.push_back("Line 3");
	EXPECT_TRUE(FileUtil::WriteContents("testoutput.txt", lines));
	vector<string> lines_in;
	EXPECT_TRUE(FileUtil::GetContents("testoutput.txt", &lines_in));
	EXPECT_EQ(lines_in.size(), 3);
	for (uint i = 0; i < lines_in.size(); i++) {
		EXPECT_EQ(lines.at(i), lines_in.at(i));
	}
}
}  // example
