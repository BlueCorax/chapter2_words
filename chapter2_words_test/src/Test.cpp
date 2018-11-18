#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "src/word.h"
#include "src/kwic.h"

#include <string>
#include <sstream>
#include <stdexcept>

using namespace word;

//operator tests
void test_opGT_lt() {
	word::Word w1 { "abc" };
	word::Word w2("def");
	ASSERT(!(w1 > w2));
}

void test_opGT_eq() {
	word::Word w1 { "abc" };
	word::Word w2("abc");
	ASSERT(!(w1 > w2));

}

void test_opGT_gt() {
	word::Word w1 { "def" };
	word::Word w2("abc");
	ASSERT(w1 > w2);

}

void test_opLT_lt() {
	word::Word w1 { "abc" };
	word::Word w2("def");
	ASSERT(w1 < w2);

}

void test_opLT_eq() {
	word::Word w1 { "abc" };
	word::Word w2("abc");
	ASSERT(!(w1 < w2));

}

void test_opLT_gt() {
	word::Word w1 { "def" };
	word::Word w2("abc");
	ASSERT(!(w1 < w2));
}

void test_opGTE_lt() {
	word::Word w1 { "abc" };
	word::Word w2("def");
	ASSERT(!(w1 >= w2));
}

void test_opGTE_eq() {
	word::Word w1 { "abc" };
	word::Word w2("abc");
	ASSERT(w1 >= w2);
}

void test_opGTE_gt() {
	word::Word w1 { "def" };
	word::Word w2("Abc");
	ASSERT(w1 >= w2);
}

void test_opLTE_lt() {
	word::Word w1 { "abC" };
	word::Word w2("def");
	ASSERT(w1 <= w2);
}

void test_opLTE_eq() {
	word::Word w1 { "abC" };
	word::Word w2("abc");
	ASSERT(w1 <= w2);

}

void test_opLTE_gt() {
	word::Word w1 { "def" };
	word::Word w2("ABC");
	ASSERT(!(w1 <= w2));

}

void test_opEQ_lt() {
	word::Word w1 { "abC" };
	word::Word w2("def");
	ASSERT(!(w1 == w2));

}

void test_opEQ_eq() {
	word::Word w1 { "abC" };
	word::Word w2("abc");
	ASSERT(w1 == w2);

}

void test_opEQ_gt() {
	word::Word w1 { "def" };
	word::Word w2("ABC");
	ASSERT(!(w1 == w2));

}

void test_opNEQ_lt() {
	word::Word w1 { "abC" };
	word::Word w2("def");
	ASSERT(w1 != w2);

}

void test_opNEQ_eq() {
	word::Word w1 { "abC" };
	word::Word w2("abc");
	ASSERT(!(w1 != w2));

}

void test_opNEQ_gt() {
	word::Word w1 { "def" };
	word::Word w2("ABC");
	ASSERT(w1 != w2);

}

//IO Tests
void test_print() {
	word::Word word { "HulaHop" };
	std::ostringstream out { };
	word.print(out);
	ASSERT_EQUAL("HulaHop", out.str());
}

void test_read_once_valid() {
	std::istringstream in { " hall0" };
	word::Word word { };
	word.read(in);
	ASSERT_EQUAL("hall", word.toString());
}

void test_read_twice_valid() {
	std::istringstream in { "once, twice!" };
	word::Word w1 { }, w2 { };
	w1.read(in);
	w2.read(in);
	ASSERT("once" == w1.toString() && "twice" == w2.toString());
}

void test_read_empty_invalid() {
	std::istringstream in { "" };
	word::Word word { };
	word.read(in);
	ASSERT(word.toString() == "default" && in.eof());
}

void test_read_numeric_invalid() {
	std::istringstream in { "1984" };
	word::Word word { };
	word.read(in);
	ASSERT(word.toString() == "default" && in.eof());
}

void test_read_twice_numericDelimiter_valid() {
	std::istringstream in { "Time4Tea" };
	word::Word w1 { };
	word::Word w2 { };
	w1.read(in);
	w2.read(in);
	ASSERT("Time" == w1.toString() && "Tea" == w2.toString());
}

void test_read_four_multipleDelimiters_valid() {
	std::istringstream in { "One 1 tWo 2- thRee 3;!fouR" };
	word::Word w1 { }, w2 { }, w3 { }, w4 { };
	w1.read(in);
	w2.read(in);
	w3.read(in);
	w4.read(in);
	ASSERT("One" == w1.toString() && "tWo" == w2.toString() && "thRee" == w3.toString() && "fouR" == w4.toString());
}

void test_opOUT_valid() {
	word::Word word { "abcdefghijklmnop" };
	std::ostringstream out { };
	out << word;
	ASSERT_EQUAL("abcdefghijklmnop", out.str());
}

void test_opIN_valid() {
	word::Word word { };
	std::istringstream in { "--hula--" };
	in >> word;
	ASSERT_EQUAL("hula", word.toString());
}

void test_opIN_invalid() {
	word::Word word { };
	std::istringstream in { "&2012%" };
	word.read(in);
	ASSERT(word.toString() == "default" && in.eof());
}

//kwic tests
void test_1line_10words() {
	std::istringstream in { "eis zwoei drueue vier fueuef saechs sibae acht nueuen zaeaeh\n" };
	std::ostringstream out { };
	kwic::kwic(in, out);
	ASSERT_EQUAL("acht nueuen zaeaeh eis zwoei drueue vier fueuef saechs sibae \n"
			"drueue vier fueuef saechs sibae acht nueuen zaeaeh eis zwoei \n"
			"eis zwoei drueue vier fueuef saechs sibae acht nueuen zaeaeh \n"
			"fueuef saechs sibae acht nueuen zaeaeh eis zwoei drueue vier \n"
			"nueuen zaeaeh eis zwoei drueue vier fueuef saechs sibae acht \n"
			"saechs sibae acht nueuen zaeaeh eis zwoei drueue vier fueuef \n"
			"sibae acht nueuen zaeaeh eis zwoei drueue vier fueuef saechs \n"
			"vier fueuef saechs sibae acht nueuen zaeaeh eis zwoei drueue \n"
			"zaeaeh eis zwoei drueue vier fueuef saechs sibae acht nueuen \n"
			"zwoei drueue vier fueuef saechs sibae acht nueuen zaeaeh eis \n", out.str());
}

void test_2lines_3words() {
	std::istringstream in { "one two three\n four five six\n" };
	std::ostringstream out { };
	kwic::kwic(in, out);
	ASSERT_EQUAL("five six four \n"
			"four five six \n"
			"one two three \n"
			"six four five \n"
			"three one two \n"
			"two three one \n", out.str());
}

void test_2lines_samewords() {
	std::istringstream in { "ABC DEF GHI\nDEF GHI ABC\n" };
	std::ostringstream out { };
	kwic::kwic(in, out);
	ASSERT_EQUAL("ABC DEF GHI \n"
			"DEF GHI ABC \n"
			"GHI ABC DEF \n", out.str());
}

void test_identical_lines() {
	std::istringstream in { "Abc aBc abC\nabC Abc aBc\n" };
	std::ostringstream out { };
	kwic::kwic(in, out);
	ASSERT_EQUAL("Abc aBc abC \n", out.str());
}

void test_same_words_different_lines() {
	std::istringstream in { "aaa aaa bbb\nbbb aaa bbb\n" };
	std::ostringstream out { };
	kwic::kwic(in, out);
	ASSERT_EQUAL("aaa aaa bbb \n"
			"aaa bbb aaa \n"
			"aaa bbb bbb \n"
			"bbb aaa aaa \n"
			"bbb aaa bbb \n"
			"bbb bbb aaa \n", out.str());
}

void test_empty() {
	std::istringstream in { };
	std::ostringstream out { };
	kwic::kwic(in, out);
	ASSERT_EQUAL("", out.str());
}

void test_no_words() {
	std::istringstream in { "23./66 &&& *\n" };
	std::ostringstream out { };
	kwic::kwic(in, out);
	ASSERT_EQUAL("", out.str());
}

//provided tests

void test_cannot_create_empty_word() {
	ASSERT_THROWS(Word { "" }, std::invalid_argument);
}

void test_cannot_create_word_with_space() {
	ASSERT_THROWS(Word { "abc xyz" }, std::invalid_argument);
}

void test_cannot_create_word_with_number() {
	ASSERT_THROWS(Word { "abc3xyz" }, std::invalid_argument);
}

void test_cannot_create_word_with_punctuation() {
	ASSERT_THROWS(Word { "abc.xyz" }, std::invalid_argument);
}

void test_output_operator() {
	std::string const expected { "Python" };
	Word const w { expected };
	std::ostringstream output { };
	output << w;
	ASSERT_EQUAL(expected, output.str());
}

void test_same_words_are_equal() {
	ASSERT_EQUAL(Word { "Ruby" }, Word { "Ruby" });
}

void test_different_words_are_not_equal() {
	ASSERT_NOT_EQUAL_TO(Word { "Haskell" }, Word { "ML" });
}

void test_same_word_with_different_cases_are_equal() {
	ASSERT_EQUAL(Word { "BASIC" }, Word { "basic" });
}

void test_same_word_is_not_lower_than() {
	ASSERT(!(Word { "Erlang" } < Word { "Erlang" }));
}

void test_smaller_word_is_smaller() {
	ASSERT_LESS(Word { "Erlang" }, Word { "Fortran" });
}

void test_smaller_word_with_capital_letters_is_smaller() {
	ASSERT_LESS(Word { "ADA" }, Word { "java" });
}

void test_same_word_with_different_cases_are_not_smaller() {
	ASSERT(!(Word { "Groovy" } < Word { "groovy" }));
}

void test_greater_word_is_greater() {
	ASSERT_GREATER(Word { "Rust" }, Word { "Prolog" });
}

void test_greater_word_with_capital_letters_is_greater() {
	ASSERT_GREATER(Word { "Lisp" }, Word { "brainfuck" });
}

void test_smaller_word_is_less_equal() {
	ASSERT_LESS_EQUAL(Word { "Algol" }, Word { "BCPL" });
}

void test_same_word_is_less_equal() {
	ASSERT_LESS_EQUAL(Word { "Assembler" }, Word { "Assembler" });
}

void test_greater_word_is_greater_equal() {
	ASSERT_GREATER_EQUAL(Word { "RPG" }, Word { "Perl" });
}

void test_same_word_is_greater_equal() {
	ASSERT_GREATER_EQUAL(Word { "Scala" }, Word { "Scala" });
}

void test_input_operator_single_word() {
	std::istringstream input { "Elixir" };
	Word w { };
	input >> w;
	ASSERT_EQUAL(Word { "Elixir" }, w);
}

void test_input_operator_single_word_stream_good() {
	std::istringstream input { "Cobol" };
	Word w { };
	ASSERT(input >> w);
}

void test_input_operator_called_once_first_word() {
	std::istringstream input { "Ceylon Go" };
	Word w { };
	input >> w;
	ASSERT_EQUAL(Word { "Ceylon" }, w);
}

void test_input_operator_called_once_stream_good() {
	std::istringstream input { "Lua Oberon" };
	Word w { };
	ASSERT(input >> w);
}

void test_input_operator_on_empty_stream_fail() {
	std::istringstream input { };
	Word w { };
	input >> w;
	ASSERT(input.fail());
}

void test_input_operator_on_stream_without_word() {
	std::istringstream input { "1337" };
	Word w { };
	input >> w;
	ASSERT(input.fail());
}

void test_input_operator_on_empty_stream_word_unchanged() {
	std::istringstream input { };
	Word w { "Eiffel" };
	input >> w;
	ASSERT_EQUAL(Word { "Eiffel" }, w);
}

void test_input_operator_stops_on_slash() {
	std::istringstream input { "PL/SQL" };
	Word w { };
	input >> w;
	ASSERT_EQUAL(Word { "PL" }, w);
}

void test_input_operator_stops_at_end_of_word() {
	std::istringstream input { "VB6" };
	Word w { };
	int i { };
	input >> w >> i;
	ASSERT_EQUAL(6, i);
}

void test_input_operator_skips_leading_non_alpha() {
	std::istringstream input { "3switchBF" };
	Word w { };
	input >> w;
	ASSERT_EQUAL(Word { "switchBF" }, w);
}

void test_input_operator_overwrites_word() {
	std::istringstream input { "Kotlin" };
	Word w { "JavaScript" };
	input >> w;
	ASSERT_EQUAL(Word { "Kotlin" }, w);
}

void test_exercise_example() {
	std::istringstream input { "compl33tely ~ weird !!??!! 4matted in_put" };
	Word w { };
	input >> w;
	ASSERT_EQUAL(Word { "compl" }, w);
	input >> w;
	ASSERT_EQUAL(Word { "tely" }, w);
	input >> w;
	ASSERT_EQUAL(Word { "weird" }, w);
	input >> w;
	ASSERT_EQUAL(Word { "matted" }, w);
	input >> w;
	ASSERT_EQUAL(Word { "in" }, w);
	input >> w;
	ASSERT_EQUAL(Word { "put" }, w);
	input >> w;
	ASSERT_EQUAL(Word { "put" }, w);
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//operator tests
	s.push_back(CUTE(test_opGT_lt));
	s.push_back(CUTE(test_opGT_gt));
	s.push_back(CUTE(test_opGT_eq));
	s.push_back(CUTE(test_opLT_lt));
	s.push_back(CUTE(test_opLT_gt));
	s.push_back(CUTE(test_opLT_eq));
	s.push_back(CUTE(test_opGTE_lt));
	s.push_back(CUTE(test_opGTE_gt));
	s.push_back(CUTE(test_opGTE_eq));
	s.push_back(CUTE(test_opLTE_lt));
	s.push_back(CUTE(test_opLTE_gt));
	s.push_back(CUTE(test_opLTE_eq));
	s.push_back(CUTE(test_opEQ_lt));
	s.push_back(CUTE(test_opEQ_gt));
	s.push_back(CUTE(test_opEQ_eq));
	s.push_back(CUTE(test_opNEQ_lt));
	s.push_back(CUTE(test_opNEQ_gt));
	s.push_back(CUTE(test_opNEQ_eq));

	//IO tests
	s.push_back(CUTE(test_print));
	s.push_back(CUTE(test_read_once_valid));
	s.push_back(CUTE(test_read_twice_valid));
	s.push_back(CUTE(test_read_empty_invalid));
	s.push_back(CUTE(test_read_numeric_invalid));
	s.push_back(CUTE(test_read_twice_numericDelimiter_valid));
	s.push_back(CUTE(test_read_four_multipleDelimiters_valid));
	s.push_back(CUTE(test_opOUT_valid));
	s.push_back(CUTE(test_opIN_valid));
	s.push_back(CUTE(test_opIN_invalid));

	//kwic tests
	s.push_back(CUTE(test_1line_10words));
	s.push_back(CUTE(test_2lines_3words));
	s.push_back(CUTE(test_2lines_samewords));
	s.push_back(CUTE(test_identical_lines));
	s.push_back(CUTE(test_same_words_different_lines));
	s.push_back(CUTE(test_empty));
	s.push_back(CUTE(test_no_words));

	//provided tests
	s.push_back(CUTE(test_cannot_create_empty_word));
	s.push_back(CUTE(test_cannot_create_word_with_space));
	s.push_back(CUTE(test_cannot_create_word_with_number));
	s.push_back(CUTE(test_cannot_create_word_with_punctuation));
	s.push_back(CUTE(test_output_operator));
	s.push_back(CUTE(test_same_words_are_equal));
	s.push_back(CUTE(test_same_word_with_different_cases_are_equal));
	s.push_back(CUTE(test_same_word_is_not_lower_than));
	s.push_back(CUTE(test_smaller_word_with_capital_letters_is_smaller));
	s.push_back(CUTE(test_smaller_word_is_smaller));
	s.push_back(CUTE(test_greater_word_is_greater));
	s.push_back(CUTE(test_greater_word_with_capital_letters_is_greater));
	s.push_back(CUTE(test_smaller_word_is_less_equal));
	s.push_back(CUTE(test_same_word_is_less_equal));
	s.push_back(CUTE(test_greater_word_is_greater_equal));
	s.push_back(CUTE(test_same_word_is_greater_equal));
	s.push_back(CUTE(test_different_words_are_not_equal));
	s.push_back(CUTE(test_input_operator_single_word));
	s.push_back(CUTE(test_input_operator_called_once_first_word));
	s.push_back(CUTE(test_input_operator_called_once_stream_good));
	s.push_back(CUTE(test_input_operator_single_word_stream_good));
	s.push_back(CUTE(test_input_operator_on_empty_stream_fail));
	s.push_back(CUTE(test_input_operator_on_empty_stream_word_unchanged));
	s.push_back(CUTE(test_input_operator_stops_on_slash));
	s.push_back(CUTE(test_input_operator_stops_at_end_of_word));
	s.push_back(CUTE(test_input_operator_skips_leading_non_alpha));
	s.push_back(CUTE(test_same_word_with_different_cases_are_not_smaller));
	s.push_back(CUTE(test_input_operator_overwrites_word));
	s.push_back(CUTE(test_input_operator_on_stream_without_word));
	s.push_back(CUTE(test_exercise_example));

	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
	return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
