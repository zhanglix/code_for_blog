#pragma once

#include "translation_service.h"

class TranslationServiceImp : public TranslationService {
public:
  virtual ~TranslationServiceImp(){}
  virtual bool translateToChinese(const std::string &input, 
				  std::string &output);
};


