#pragma once

#include "doc_list.h"

class AndDocList : public DocList {
public:
  virtual ~AndDocList(){}
  doc_id_t next(doc_id_t id) ;
  doc_id_t current() ;
};
