#include <gmock/gmock.h>

#include <string>
#include "and_not_doc_list.h"
#include "fake_doc_list.h"

using namespace std;
using namespace testing;

class AndNotDocListBtest: public Test {

};

//Practice to design black box 
TEST_F(AndNotDocListBtest, 1) {
  EXPECT_TRUE(false);
}




