#include <gmock/gmock.h>
#include "mock_language_detector.h"
#include "mock_translator.h"
#include "translation_service_imp.h"
#include <string>

using namespace std;
using namespace testing;


class TranslationServiceWTest: public Test {
protected:
  TranslationService *_service;
  MockLanguageDector *_mockDetector;
  MockTranslator *_mockEngTranslator;
  MockTranslator *_mockJapTranslator;
  MockTranslator *_mockKoreanTranslator;
  string _input;
  string _output;
  string _expected;

  TranslationServiceWTest() {
    _mockDetector = new MockLanguageDector;
    _mockEngTranslator = new MockTranslator;
    _mockJapTranslator = new MockTranslator; 
    _mockKoreanTranslator = new MockTranslator;
    
    TranslationServiceImp *serviceImp = new TranslationServiceImp;
    serviceImp->setLanguageDetector(_mockDetector);
    serviceImp->addTranslator(LID_ENGLISH, _mockEngTranslator);
    serviceImp->addTranslator(LID_JAPANESE, _mockJapTranslator);
    serviceImp->addTranslator(LID_KOREAN, _mockKoreanTranslator);
    _service = serviceImp;
    _input = "外文输入";
    _expected = "中文翻译";
  }

  ~TranslationServiceWTest() {
    delete _service;
  }
};

TEST_F(TranslationServiceWTest, english) {
  EXPECT_CALL(*_mockDetector, detect(_input))             
    .WillOnce(Return(LID_ENGLISH));
  EXPECT_CALL(*_mockEngTranslator, translate(_input))             
    .WillOnce(Return(_expected));
  
  EXPECT_TRUE(_service->translateToChinese(_input, _output));
  EXPECT_EQ(_expected, _output);
}


TEST_F(TranslationServiceWTest, japanese) {//duplicated case
  EXPECT_CALL(*_mockDetector, detect(_input))             
    .WillOnce(Return(LID_JAPANESE));
  EXPECT_CALL(*_mockJapTranslator, translate(_input))             
    .WillOnce(Return(_expected));
  
  EXPECT_TRUE(_service->translateToChinese(_input, _output));
  EXPECT_EQ(_expected, _output);
}

TEST_F(TranslationServiceWTest, korean) {//duplicated case
  EXPECT_CALL(*_mockDetector, detect(_input))             
    .WillOnce(Return(LID_KOREAN));
  EXPECT_CALL(*_mockKoreanTranslator, translate(_input))             
    .WillOnce(Return(_expected));
  
  EXPECT_TRUE(_service->translateToChinese(_input, _output));
  EXPECT_EQ(_expected, _output);
}

TEST_F(TranslationServiceWTest, chinese) {
  EXPECT_CALL(*_mockDetector, detect(_input))             
    .WillOnce(Return(LID_CHINESE));
  EXPECT_TRUE(_service->translateToChinese(_input, _output));
  EXPECT_EQ(_input, _output);
}

TEST_F(TranslationServiceWTest, unknow) {
  EXPECT_CALL(*_mockDetector, detect(_input))             
    .WillOnce(Return(LID_UNKNOWN));
  EXPECT_FALSE(_service->translateToChinese(_input, _output));
  EXPECT_EQ("Sorry! I can't understand this language.", _output);
}

TEST_F(TranslationServiceWTest, noSuchTranslator) {
  EXPECT_CALL(*_mockDetector, detect(_input))             
    .WillOnce(Return(LID_RUSSIAN));
  EXPECT_FALSE(_service->translateToChinese(_input, _output));
  EXPECT_EQ("Sorry! I can't understand this language.", _output);
}

TEST_F(TranslationServiceWTest, empty) {
  EXPECT_TRUE(_service->translateToChinese("", _output));
  EXPECT_EQ("", _output);
}
