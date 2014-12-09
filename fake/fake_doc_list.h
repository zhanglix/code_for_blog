#pragma once

#include "doc_list.h"
#include <vector>

class FakeDocList : public DocList {
public:
  FakeDocList(const std::vector<doc_id_t> &docidVector);
  FakeDocList(doc_id_t first, doc_id_t last, doc_id_t step);
  virtual ~FakeDocList();
  virtual doc_id_t next(doc_id_t id);
private:
  void reset(const std::vector<doc_id_t> &docidVector);

private:
  std::vector<doc_id_t> _docIds;
  std::vector<doc_id_t>::iterator _it;
};
