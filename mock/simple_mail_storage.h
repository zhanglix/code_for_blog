#pragma once

class RemoteKeyValueService;
class SimpleMailStorage {
public:
  SimpleMailStorage(RemoteKeyValueService *remoteKeyValueService);
  virtual ~SimpleMailStorage();
  virtual bool writeMail(const std::string &id, const std::string &content);
  static const int ATTEMPTS_LIMIT = 3;
private:
  RemoteKeyValueService *_remoteKeyValueService;
};
