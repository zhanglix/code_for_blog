#include "tokenizer.h"
#include <assert.h>

using namespace std;
vector<string> Tokenizer::tokenize(const std::string &str) {
  vector<string> result;
  size_t startOfSegment = 0;
  size_t end = str.size();
  while(startOfSegment <= end) {
    startOfSegment = processCurrentSegment(str, startOfSegment, result);
  }
  return result;
}

size_t Tokenizer::processCurrentSegment(const string&str, size_t start, 
					vector<string> &result) 
{
  assert(start <= str.size());
  size_t pos = start;
  size_t end = str.size();

  char buffer[end - start];
  size_t bufferIndex = 0;
  bool escapeMode = false;
  for(;pos < end; pos++) {
    char c = str[pos];
    if (_escape && c == '\\') {
      if(escapeMode) {
	escapeMode = false;
      } else {
	escapeMode = true;
	continue;
      }
    }
    if (escapeMode || c != _delimiter) {
      escapeMode = false;
      buffer[bufferIndex++] = c;
    } else {
      break;
    }
  }
  string seg = str.substr(start, pos-start);
  if (!_filterEmptySegs || bufferIndex > 0) {
    result.push_back(string(buffer, bufferIndex));
  }
  return pos + 1;
}
