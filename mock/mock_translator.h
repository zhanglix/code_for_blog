#pragma once

#include <gmock/gmock.h>
#include "translator.h"

class MockTranslator : public Translator {
public:
  MOCK_METHOD1(translate, std::string(const std::string &text));
};
