#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include <vector>
#include <string>

class Tokenizer {
public:
  Tokenizer(char delimiter = ' ', 
	    bool filterEmptySegs = false, 
	    bool escape = false) : _delimiter(delimiter),
				   _filterEmptySegs(filterEmptySegs),
				   _escape(escape){ }
  std::vector<std::string> tokenize(const std::string &str);

private:
  char _delimiter;
  bool _filterEmptySegs;
  bool _escape;

private:
  size_t processCurrentSegment(const std::string&str, size_t start, 
			       std::vector<std::string> &result);
};

#endif
