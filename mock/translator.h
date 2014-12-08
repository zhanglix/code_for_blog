#pragma once

#include <string>

class Translator {
public:
  virtual ~Translator(){}
  virtual std::string translate(const std::string &text) = 0;
};
