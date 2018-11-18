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
	std::stringstream in{line};
	WList sentence{std::istream_iterator<word::Word>{in}, std::istream_iterator<word::Word>{}};
	return sentence;
}

void kwic::kwic(std::istream & in, std::ostream & out) {
	std::set<WList> rotationSet {};
	std::string line{};
	while (std::getline(in, line)) {
		auto sentence = parseWords(line);
		for (unsigned int i = 0; i < sentence.size(); i++) {
			rotationSet.insert(sentence);
			std::rotate(begin(sentence), begin(sentence) + 1, end(sentence));
		}
	}
	std::for_each(begin(rotationSet), end(rotationSet), [&out](WList wl){
		std::copy(begin(wl), end(wl), std::ostream_iterator<word::Word>(out, " "));
		out << '\n';
	});
}
