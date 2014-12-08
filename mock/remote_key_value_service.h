#pragma once

#include <string>

class RemoteKeyValueService {
public:
  typedef enum { OK = 0,
		 TIMEOUT,
		 KEY_NOT_FOUND,
  } RetCode;
  virtual ~RemoteKeyValueService() {}
  virtual RetCode put(const std::string &key, const std::string &value) = 0;
  virtual RetCode get(const std::string &key, std::string &value) = 0;
};
