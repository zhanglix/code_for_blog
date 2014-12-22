#include <gmock/gmock.h>

#include <string>
#include "or_doc_list.h"
#include "fake_doc_list.h"

using namespace std;
using namespace testing;


class OrDocListBtest: public Test {
public:
  OrDocList _orDocList;
};

//Practice to design class interfaces by black box testings
TEST_F(OrDocListBtest, oneTerm) {
  _orDocList.addDocList(new FakeDocList(1, 6, 2));
  EXPECT_TRUE(false);
}


TEST_F(OrDocListBtest, threeTerm) {
  EXPECT_TRUE(false);
}

TEST_F(OrDocListBtest, composition) {
  EXPECT_TRUE(false);
}



