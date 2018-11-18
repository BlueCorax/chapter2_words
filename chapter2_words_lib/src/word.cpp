#include "word.h"

#include <string>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <iterator>

namespace word {

Word::Word() {
	string = "default";
}

Word::Word(std::string word) {
	if (word.empty() || !std::all_of(begin(word), end(word), isalpha)) {
		throw std::invalid_argument { "This is not a word!" };
	}
	string = word;
}

std::istream & Word::read(std::istream &stream) {
	std::ostringstream ss { };

	char c = stream.peek();
	while (stream.good() && !std::isalpha(c)) { //skip non letters
		stream.ignore();
		c = stream.peek();
	}
	while (stream.good() && std::isalpha(c)) { //read until non letter
		ss << c;
		stream.ignore();
		c = stream.peek();
	}

	if (stream.fail() || ss.str().empty()) {
		stream.setstate(std::ios::failbit);
	} else {
		string = ss.str();
	}

	return stream;
}

std::ostream & Word::print(std::ostream &out) const {
	out << string;
	return out;
}

int Word::cmp(Word const other) const {
	std::string own{string};
	std::string others{other.string};
	std::transform(own.begin(), own.end(), own.begin(), tolower);
	std::transform(others.begin(), others.end(), others.begin(), tolower);
	return own.compare(others);
}

bool Word::operator>(Word const other) const {
	return Word::cmp(other) > 0;
}
bool Word::operator<(Word const other) const {
	return Word::cmp(other) < 0;
}
bool Word::operator>=(Word const other) const {
	return Word::cmp(other) >= 0;
}
bool Word::operator<=(Word const other) const {
	return Word::cmp(other) <= 0;
}
bool Word::operator==(Word const other) const {
	return Word::cmp(other) == 0;
}
bool Word::operator!=(Word const other) const {
	return Word::cmp(other) != 0;
}

std::istream & operator>>(std::istream &in, Word &word) {
	return word.read(in);
}

std::ostream & operator<<(std::ostream &out, Word const word) {
	return word.print(out);
}

}

