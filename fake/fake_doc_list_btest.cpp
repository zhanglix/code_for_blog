#include <gmock/gmock.h>

#include <string>
#include "fake_doc_list.h"

using namespace std;
using namespace testing;

//just for demo, not enough for real life tests
class FakeDocListBtest: public Test {
public:
  DocList *_docList;
  FakeDocListBtest() {
    _docList = NULL;
  }

  ~FakeDocListBtest() {
    if(_docList) {
      delete _docList;
    }
  }
};


TEST_F(FakeDocListBtest, esstep2) {
  _docList = new FakeDocList(1, 6, 2);
  EXPECT_EQ(1, _docList->next(0));
  EXPECT_EQ(3, _docList->next(2));
  EXPECT_EQ(3, _docList->next(3));
  EXPECT_EQ(5, _docList->next(4));
  EXPECT_EQ(DocList::INVALID_DOC_ID, _docList->next(6));
}

TEST_F(FakeDocListBtest, step5) {
  _docList = new FakeDocList(5, 91, 5);
  EXPECT_EQ(5, _docList->next(0));
  EXPECT_EQ(35, _docList->next(31));
  EXPECT_EQ(40, _docList->next(36));
  EXPECT_EQ(90, _docList->next(86));
  EXPECT_EQ(DocList::INVALID_DOC_ID, _docList->next(91));
}
