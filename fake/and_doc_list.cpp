#include <assert.h>
#include "and_doc_list.h"

using namespace std;

AndDocList::AndDocList() {
}

AndDocList::~AndDocList() {
  for (vector<DocList*>::iterator it = _children.begin();
       it != _children.end(); it++) {
    delete *it;
  }
}

doc_id_t AndDocList::next(doc_id_t id) {
  assert(id >= 0);
  doc_id_t lastId = id;
  vector<DocList*>::iterator it = _children.begin();
  while (it != _children.end()) {
    doc_id_t nextId = (*it)->next(lastId);
    if (nextId == lastId) {
      it++;
    } else if (nextId != DocList::INVALID_DOC_ID) {
      lastId = nextId;
      it = _children.begin();
    } else {
      return DocList::INVALID_DOC_ID;
    }
  }
  return lastId;
}

void AndDocList::addDocList(DocList *docList) {
  _children.push_back(docList);
}


size_t AndDocList::size() {
  return _children.size();
}
