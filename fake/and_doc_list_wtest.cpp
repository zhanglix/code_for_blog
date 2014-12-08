#include <gmock/gmock.h>

#include <string>

using namespace std;
using namespace testing;

//just for demo, not enough for real life tests
class AndDocListWTest: public Test {
public:
};


TEST_F(AndDocListWTest, oneTerm) {
  EXPECT_TRUE(false);
}

