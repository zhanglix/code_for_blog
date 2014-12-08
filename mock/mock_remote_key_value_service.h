#include "remote_key_value_service.h"

class MockRemoteKeyValueService : public RemoteKeyValueService {
 public:
  MOCK_METHOD2(put,
      RetCode(const std::string &key, const std::string &value));
  MOCK_METHOD2(get,
      RetCode(const std::string &key, std::string &value));
};
