#include <gmock/gmock.h>

#include <string>
#include "tokenizer.h"

using namespace std;
using namespace testing;
class TokenizerBBTest: public Test {
};

TEST_F(TokenizerBBTest, defaultSetting) {
  Tokenizer tokenizer; 
  EXPECT_THAT(tokenizer.tokenize(""),
	      ElementsAre(""));
  EXPECT_THAT(tokenizer.tokenize("some normal string"),
	      ElementsAre("some", "normal", "string"));
}

TEST_F(TokenizerBBTest, CommaNoFilterNoEscape) {
  Tokenizer tokenizer(','); 
  EXPECT_THAT(tokenizer.tokenize(",,"), ElementsAre("", "", ""));
  EXPECT_THAT(tokenizer.tokenize(",\\,"), ElementsAre("","\\",""));
  EXPECT_THAT(tokenizer.tokenize(",\\,some,,normal string,"),
	      ElementsAre("","\\","some","", "normal string",""));
  EXPECT_THAT(tokenizer.tokenize("some normal string"),
	      ElementsAre("some normal string"));
}

TEST_F(TokenizerBBTest, CommaFilterNoEscape) {
  Tokenizer tokenizer(',', true); 
  EXPECT_THAT(tokenizer.tokenize(""), ElementsAre());
  EXPECT_THAT(tokenizer.tokenize(","), ElementsAre());
  EXPECT_THAT(tokenizer.tokenize("\\,,"), ElementsAre("\\"));
}

TEST_F(TokenizerBBTest, CommaNoFilterEscape) {
  Tokenizer tokenizer(',', false, true); 
  EXPECT_THAT(tokenizer.tokenize("\\,,"), ElementsAre(",", ""));
  EXPECT_THAT(tokenizer.tokenize("s,\\"), ElementsAre("s", ""));
}

TEST_F(TokenizerBBTest, CommaFilterEscape) {
  Tokenizer tokenizer(',', true, true); 
  EXPECT_THAT(tokenizer.tokenize("s,\\\\,"), ElementsAre("s", "\\"));
  EXPECT_THAT(tokenizer.tokenize(",\\,,"), ElementsAre(","));
  EXPECT_THAT(tokenizer.tokenize("\\,\\,"), ElementsAre(",,"));
}

TEST_F(TokenizerBBTest, EscapeNoFilterNoEscape) {
  Tokenizer tokenizer('\\');
  EXPECT_THAT(tokenizer.tokenize("\\,,"), ElementsAre("", ",,"));
  EXPECT_THAT(tokenizer.tokenize("ss\\\\"), ElementsAre("ss","", ""));
}

TEST_F(TokenizerBBTest, EscapeNoFilterEscape) {
  Tokenizer tokenizer('\\',false, true);
  //the escape charater will be changed to '/' when the delimiter is '\'
  EXPECT_THAT(tokenizer.tokenize("s\\\\o\\a"), 
	      ElementsAre("s","","o","a"));
}

TEST_F(TokenizerBBTest, EscapeFilterEscape) {
  Tokenizer tokenizer('\\',true, true);
  EXPECT_THAT(tokenizer.tokenize("\\\\,,"), ElementsAre(",,"));
  EXPECT_THAT(tokenizer.tokenize("ss/\\\\/\\e"), ElementsAre("ss\\","\\e"));
  EXPECT_THAT(tokenizer.tokenize("s/\\//o\\a"), 
	      ElementsAre("s\\/o","a"));
}

TEST_F(TokenizerBBTest, WithZeroBytes) {
  Tokenizer tokenizer(',',true, true);
  const char buffer[] = "a\0""c,\0,def\\,\0"",";
  const string input(buffer, sizeof(buffer));
  string zero = string(1, '\0');
  vector<string> expected;
  expected.push_back(string(buffer,3));//"a\0c"
  expected.push_back(zero);//"\0"
  expected.push_back(string("def,\0",5));//"def,\0"
  expected.push_back(zero);//"\0"
  EXPECT_THAT(tokenizer.tokenize(input), ContainerEq(expected));
}
