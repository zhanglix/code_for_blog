#include <gmock/gmock.h>

#include <string>

using namespace std;
using namespace testing;

#include "mock_remote_key_value_service.h"
#include "simple_mail_storage.h"

class SimpleMailStorageWTest: public Test {
public:
  MockRemoteKeyValueService *_mockRemoteKVService;
  SimpleMailStorage * _simpleMailStorage;
  string _mailId;
  string _mailContent;

  SimpleMailStorageWTest() {
    _mockRemoteKVService = new MockRemoteKeyValueService;
    _simpleMailStorage = new SimpleMailStorage(_mockRemoteKVService);
  }

  ~SimpleMailStorageWTest() {
    delete  _simpleMailStorage;
  }
};


TEST_F(SimpleMailStorageWTest, writeFailAfterRetry) {
  EXPECT_CALL(*_mockRemoteKVService, put(_mailId, _mailContent))             
    .WillOnce(Return(RemoteKeyValueService::TIMEOUT))
    .WillOnce(Return(RemoteKeyValueService::TIMEOUT))
    .WillOnce(Return(RemoteKeyValueService::TIMEOUT));
  EXPECT_FALSE(_simpleMailStorage->writeMail(_mailId, _mailContent));
}

TEST_F(SimpleMailStorageWTest, writeSuccessAt2ndRetry) {
  EXPECT_CALL(*_mockRemoteKVService, put(_mailId, _mailContent))             
    .WillOnce(Return(RemoteKeyValueService::TIMEOUT))
    .WillOnce(Return(RemoteKeyValueService::TIMEOUT))
    .WillOnce(Return(RemoteKeyValueService::OK));
  EXPECT_TRUE(_simpleMailStorage->writeMail(_mailId, _mailContent));
}

