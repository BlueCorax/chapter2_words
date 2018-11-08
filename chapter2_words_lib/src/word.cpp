#include "word.h"

#include <string>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <iterator>

Word::Word() {
	string = "default";
}

Word::Word(std::string word) {
	string = word;
}

std::istream & Word::read(std::istream &stream) {
	std::ostringstream ss { };

	char const c = stream.peek();
	while (stream.good() && !std::isalpha(c)) { //skip non letters
		stream.ignore();
		c = stream.peek();
	}
	while (stream.good() && std::isalpha(c)) { //read until non letter
		ss << c;
		stream.ignore();
		c = stream.peek();
	}

	if (stream.good()) {
		string = ss.str();
	}

	return stream;
}

std::ostream & Word::print(std::ostream &out) const {
	out << string;
	return out;
}

int Word::cmp(Word const other) const {
	return std::lexicographical_compare(std::begin(string), std::end(string), std::begin(other.string), std::end(other.string), [](char const l, char const r){
		return std::tolower(l) - std::tolower(r);
	});
}

bool Word::operator>(Word const other) {
	return Word::cmp(other) > 0;
}
bool Word::operator<(Word const other) {
	return Word::cmp(other) < 0;
}
bool Word::operator>=(Word const other) {
	return Word::cmp(other) >= 0;
}
bool Word::operator<=(Word const other) {
	return Word::cmp(other) <= 0;
}
bool Word::operator==(Word const other) {
	return Word::cmp(other) == 0;
}
bool Word::operator!=(Word const other) {
	return Word::cmp(other) != 0;
}

std::istream & operator>>(std::istream &in, Word &word) {
	return word.read(in);
}

std::ostream & operator<<(std::ostream &out, Word const word) {
	return word.print(out);
}
