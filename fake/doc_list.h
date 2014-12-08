#pragma once

typedef int doc_id_t;
// A doc id list in ascending order
class DocList {
public:
  virtual ~DocList(){}

  //find the first doc id which is greater or equal than id
  //return: the doc id found or INVALID_DOC_ID if no such doc id found
  //side effect: current doc id will be set accordingly
  virtual doc_id_t next(doc_id_t id) = 0;

  virtual doc_id_t current() = 0;

  static const doc_id_t INVALID_DOC_ID = doc_id_t(-1);
};
