#pragma once

#include <string>

enum LanguageID {
  LID_UNKNOWN = 0,
  LID_CHINESE,
  LID_ENGLISH,
  LID_JAPANESE,
  LID_KOREAN,
  LID_RUSSIAN
};

class LanguageDetector {
public:
  virtual ~LanguageDetector(){}
  virtual LanguageID detect(const std::string& text) = 0;
};
