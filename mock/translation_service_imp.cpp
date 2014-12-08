#include "translation_service_imp.h"

using namespace std;

TranslationServiceImp::TranslationServiceImp(){
  _detector = NULL;
}

//** TODO: add unit test for this destructor
TranslationServiceImp::~TranslationServiceImp(){
  if (_detector) {
    delete _detector;
  }
  
  for (TranslatorMap::iterator it = _translators.begin();
       it != _translators.end(); it++) {
    delete it->second;					
    it->second = NULL;
  } 
}

bool TranslationServiceImp::
translateToChinese(const string &input, string &output) {
  if(input == "") {
    output = "";
    return true;
  }

  LanguageID lid = _detector->detect(input);
  if (LID_UNKNOWN != lid ) {
    if (LID_CHINESE == lid) {
      output = input;
      return true;
    }

    TranslatorMap::const_iterator it = _translators.find(lid);
    if (it != _translators.end()) {
      output = it->second->translate(input);
      return true;
    }
  } 

  output = "Sorry! I can't understand this language.";
  return false;
}

void TranslationServiceImp::
setLanguageDetector(LanguageDetector *detector){
  if (_detector) {
    delete _detector;
  }
  _detector = detector;
}

void TranslationServiceImp::
addTranslator(LanguageID lid, Translator *translator) {
  TranslatorMap::iterator it = _translators.find(lid);
  if (it != _translators.end()) {
    delete it->second;
    _translators.erase(it);
  }
  _translators[lid] =  translator;
}

