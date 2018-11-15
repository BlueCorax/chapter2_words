#include "kwic.h"
#include "word.h"

#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <sstream>

using WList = std::vector<word::Word>;

WList parseWords(std::string & line) {
	WList sentence{};
	word::Word word{};
	std::stringstream in{line};

	in >> word;
	while(in.good()){
		sentence.push_back(word);
		in >> word;
	}
	return sentence;
}

void kwic::kwic(std::istream & in, std::ostream & out) {
	std::set<WList> rotationSet { };
	while (in.good()) {
		std::string line;
		std::getline(in, line);
		WList sentence = parseWords(line);
		for (unsigned int i = 0; i < sentence.size(); i++) {
			rotationSet.insert(sentence);
			std::rotate(begin(sentence), begin(sentence) + 1, end(sentence));
		}
	}
}
