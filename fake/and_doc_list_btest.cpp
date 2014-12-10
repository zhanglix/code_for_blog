#include <gmock/gmock.h>

#include <string>
#include "and_doc_list.h"
#include "fake_doc_list.h"

using namespace std;
using namespace testing;

//just for demo, not enough for real life tests
class AndDocListBtest: public Test {
public:
  AndDocList _andDocList;
};


TEST_F(AndDocListBtest, oneTerm) {
  _andDocList.addDocList(new FakeDocList(1, 6, 2));
  EXPECT_EQ(1, _andDocList.seek(0));
  EXPECT_EQ(3, _andDocList.seek(2));
  EXPECT_EQ(3, _andDocList.seek(3));
  EXPECT_EQ(5, _andDocList.seek(4));
  EXPECT_EQ(DocList::INVALID_DOC_ID, _andDocList.seek(6));
}


TEST_F(AndDocListBtest, threeTerm) {
  _andDocList.addDocList(new FakeDocList(5, 91, 5));
  _andDocList.addDocList(new FakeDocList(0, 81, 3));
  _andDocList.addDocList(new FakeDocList(0, 61, 2));
  EXPECT_EQ(3, _andDocList.size());
  EXPECT_EQ(30, _andDocList.seek(0));
  EXPECT_EQ(60, _andDocList.seek(31));
  EXPECT_EQ(DocList::INVALID_DOC_ID, _andDocList.seek(61));
}

TEST_F(AndDocListBtest, composition) {
  AndDocList *child = new AndDocList();
  child->addDocList(new FakeDocList(5, 91, 5));
  child->addDocList(new FakeDocList(0, 81, 3));
  _andDocList.addDocList(child);
  _andDocList.addDocList(new FakeDocList(0, 61, 2));
  EXPECT_EQ(2, _andDocList.size());
  EXPECT_EQ(30, _andDocList.seek(0));
  EXPECT_EQ(60, _andDocList.seek(31));
  EXPECT_EQ(DocList::INVALID_DOC_ID, _andDocList.seek(61));
}



