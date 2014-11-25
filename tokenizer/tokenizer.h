#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include <vector>
#include <string>

class Tokenizer {
public:
  Tokenizer(char delimiter = ' ', 
	    bool filterEmptySegs = false, 
	    bool escape = false);
  std::vector<std::string> tokenize(const std::string &str);

private:
  char _delimiter;
  bool _filterEmptySegs;
  char _escape;

private:
  size_t processCurrentSegment(const std::string&str, size_t start, 
			       std::vector<std::string> &result);
};

#endif
