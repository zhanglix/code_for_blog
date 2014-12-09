#pragma once

#include <vector>
#include "doc_list.h"

class AndDocList : public DocList {
public:
  AndDocList();
  virtual ~AndDocList();
  doc_id_t next(doc_id_t id);

  void addDocList(DocList * docList);
  size_t size();
private:
  std::vector<DocList*> _children;
};
