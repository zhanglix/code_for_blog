#pragma once

#include <string>

class TranslationService {
public:
  virtual ~TranslationService(){}
  virtual bool translateToChinese(const std::string &input, 
				  std::string &output) = 0;
};

