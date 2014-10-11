#include <gmock/gmock.h>

#include <string>
#include "tokenizer.h"

using namespace std;
using namespace testing;
class TokenizerBBTest: public Test {
};

//input splits
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

TEST_F(TokenizerBBTest, CommaFilterNoEscape) {
  Tokenizer tokenizer(',', true); 
  EXPECT_THAT(tokenizer.tokenize(""), ElementsAre());
  EXPECT_THAT(tokenizer.tokenize(","), ElementsAre());
  EXPECT_THAT(tokenizer.tokenize("\\,,"), ElementsAre("\\"));
}

TEST_F(TokenizerBBTest, EscapeNoFilterNoEscape) {
  Tokenizer tokenizer('\\');
  EXPECT_THAT(tokenizer.tokenize("\\,,"), ElementsAre("", ",,"));
  EXPECT_THAT(tokenizer.tokenize("ss\\\\"), ElementsAre("ss","", ""));
}

TEST_F(TokenizerBBTest, EscapeNoFilterEscape) {
  Tokenizer tokenizer('\\',false, true);
  EXPECT_THAT(tokenizer.tokenize("\\\\\\e"), ElementsAre("","e"));
}

TEST_F(TokenizerBBTest, EscapeFilterEscape) {
  Tokenizer tokenizer('\\',true, true);
  EXPECT_THAT(tokenizer.tokenize("\\\\,,"), ElementsAre(",,"));
  EXPECT_THAT(tokenizer.tokenize("ss\\\\\\e"), ElementsAre("ss","e"));
}
