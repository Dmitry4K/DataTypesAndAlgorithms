#include<string>
#include<vector>

inline bool space(char c) {
	return std::isspace(c);
}

inline bool notspace(char c) {
	return !std::isspace(c);
}
std::vector<std::string> split(const std::string& s) { 
  typedef std::string::const_iterator iter; 
  std::vector<std::string> ret; 
  iter i = s.begin(); 
  while (i != s.end()) { 
    i = std::find_if(i, s.end(), notspace); // find the beginning of a word 
    iter j = std::find_if(i, s.end(), space); // find the end of the same word
    if (i != s.end()) { 
      ret.push_back(std::string(i, j)); //insert the word into vector 
      i = j; // repeat 1,2,3 on the rest of the line. 
    } 
  } 
  return ret; 
}
