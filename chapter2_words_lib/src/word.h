#ifndef WORD_H_
#define WORD_H_

#include <string>
#include <iosfwd>

class Word{
	std::string string;

public:
	Word();
	explicit Word(std::string word);

	std::istream & read(std::istream &in);
	std::ostream & print(std::ostream &out) const;

	int cmp(Word const other) const ;

	bool operator>(Word const other);
	bool operator<(Word const other);
	bool operator>=(Word const other);
	bool operator<=(Word const other);
	bool operator==(Word const other);
	bool operator!=(Word const other);

	inline std::string toString() const{
		return string;
	}
};

std::istream & operator>>(std::istream &in, Word &word);
std::ostream & operator<<(std::ostream &out, Word const word);

#endif
