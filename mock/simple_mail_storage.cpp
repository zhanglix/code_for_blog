#include <string>

#include "simple_mail_storage.h"
#include "remote_key_value_service.h"

using namespace std;

SimpleMailStorage::
SimpleMailStorage(RemoteKeyValueService* remoteKeyValueService) {
  _remoteKeyValueService = remoteKeyValueService;
}

SimpleMailStorage::~SimpleMailStorage() {
  if(_remoteKeyValueService) {
    delete _remoteKeyValueService;
  }
}

bool SimpleMailStorage::writeMail(const string &id, const string &content) {
  RemoteKeyValueService::RetCode rc;
  for (int attempt = 0; attempt < ATTEMPTS_LIMIT; attempt ++) {
    rc = _remoteKeyValueService->put(id, content);
    if (rc == RemoteKeyValueService::OK) {
      return true;
    } 
  }
  return false;
}
