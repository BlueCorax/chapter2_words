#ifndef WORD_H_
#define WORD_H_

#include <string>
#include <iosfwd>

namespace word {

	class Word {
		std::string string;
		int cmp(Word const other) const;

	public:
		Word();
		explicit Word(std::string word);

		std::istream & read(std::istream &in);
		std::ostream & print(std::ostream &out) const;

		bool operator>(Word const other) const;
		bool operator<(Word const other) const;
		bool operator>=(Word const other) const;
		bool operator<=(Word const other) const;
		bool operator==(Word const other) const;
		bool operator!=(Word const other) const;

		inline std::string toString() const {
			return string;
		}
	};

	std::istream & operator>>(std::istream &in, word::Word &word);
	std::ostream & operator<<(std::ostream &out, word::Word const word);
}


#endif
