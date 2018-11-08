#ifndef KWIC_H_
#define KWIC_H_

#include "word.h"

#include <string>
#include <vector>
#include <set>

class KWIC{
public:
	std::set<std::vector<Word>> sentences;

	KWIC();
	explicit KWIC(std::string text);

	void add(std::string text);

};



#endif /* KWIC_H_ */
