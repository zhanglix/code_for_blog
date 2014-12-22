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
  EXPECT_EQ(1, _docList->seek(0));
  EXPECT_EQ(3, _docList->seek(2));
  EXPECT_EQ(3, _docList->seek(3));
  EXPECT_EQ(5, _docList->seek(4));
  EXPECT_EQ(DocList::INVALID_DOC_ID, _docList->seek(6));
}

TEST_F(FakeDocListBtest, step5) {
  _docList = new FakeDocList(5, 91, 5);
  EXPECT_EQ(5, _docList->seek(0));
  EXPECT_EQ(35, _docList->seek(31));
  EXPECT_EQ(40, _docList->seek(36));
  EXPECT_EQ(90, _docList->seek(86));
  EXPECT_EQ(DocList::INVALID_DOC_ID, _docList->seek(91));
}

TEST_F(FakeDocListBtest, empty) {
  _docList = new FakeDocList(vector<doc_id_t>());
  EXPECT_EQ(DocList::INVALID_DOC_ID, _docList->seek(0));
  EXPECT_EQ(DocList::INVALID_DOC_ID, _docList->seek(0));
}

TEST_F(FakeDocListBtest, simple) {
  vector<doc_id_t> ids;
  ids.push_back(1);
  ids.push_back(3);
  ids.push_back(4);
  _docList = new FakeDocList(ids);
  EXPECT_EQ(1, _docList->seek(0));
  EXPECT_EQ(3, _docList->seek(2));
  EXPECT_EQ(4, _docList->seek(4));
  EXPECT_EQ(DocList::INVALID_DOC_ID, _docList->seek(5));
}

