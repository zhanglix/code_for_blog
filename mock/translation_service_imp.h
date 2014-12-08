#pragma once

#include "translation_service.h"
#include "language_detector.h"
#include "translator.h"
#include <map>

class TranslationServiceImp : public TranslationService {
public:
  TranslationServiceImp();
  virtual ~TranslationServiceImp();
  virtual bool translateToChinese(const std::string &input, 
				  std::string &output);
  void setLanguageDetector(LanguageDetector *detector);
  void addTranslator(LanguageID lid, Translator *translator);
private:
  LanguageDetector *_detector;
  typedef std::map<LanguageID, Translator*> TranslatorMap;
  TranslatorMap _translators;
};


