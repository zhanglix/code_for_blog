#include "doc_list.h"
#include <vector>

class FakeDocList : public DocList {
public:
  FakeDocList(const std::vector<doc_id_t> &docidVector);
  virtual ~FakeDocList();
  virtual doc_id_t next(doc_id_t id);
}
