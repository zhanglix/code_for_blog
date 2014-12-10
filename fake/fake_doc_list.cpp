#include <assert.h>
#include "fake_doc_list.h"

using namespace std;
FakeDocList::FakeDocList(const vector<doc_id_t> &docIds) {
  reset(docIds);
}

FakeDocList::FakeDocList(doc_id_t first, doc_id_t last, doc_id_t step) {
  vector<doc_id_t> docIds;
  for (doc_id_t id = first; id < last; id+=step) {
    docIds.push_back(id);
  }
  reset(docIds);
}

FakeDocList::~FakeDocList() {}

doc_id_t FakeDocList::seek(doc_id_t id) {
  assert(id >= 0);
  for (; _it != _docIds.end(); _it ++) {
    if (*_it >= id) {
      return *_it;
    }
  }
  return DocList::INVALID_DOC_ID;
}

void FakeDocList::reset(const vector<doc_id_t> &docIds) {
  _docIds = docIds;
  _it = _docIds.begin();
}
