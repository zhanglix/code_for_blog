#pragma once

#include <gmock/gmock.h>
#include "language_detector.h"

class MockLanguageDector : public LanguageDetector {
public:
  MOCK_METHOD1(detect, LanguageID(const std::string& text));
};
