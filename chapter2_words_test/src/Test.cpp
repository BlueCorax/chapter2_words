#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "src/word.h"
#include "src/kwic.h"
#include "word_tests.h"

#include <sstream>


//operator tests
void test_opGT_lt(){
	word::Word w1{"abc"};
	word::Word w2("def");
	ASSERT(!(w1 > w2));
}

void test_opGT_eq(){
	word::Word w1{"abc"};
	word::Word w2("abc");
	ASSERT(!(w1 > w2));

}

void test_opGT_gt(){
	word::Word w1{"def"};
	word::Word w2("abc");
	ASSERT(w1 > w2);

}

void test_opLT_lt(){
	word::Word w1{"abc"};
	word::Word w2("def");
	ASSERT(w1 < w2);

}

void test_opLT_eq(){
	word::Word w1{"abc"};
	word::Word w2("abc");
	ASSERT(!(w1 < w2));

}

void test_opLT_gt(){
	word::Word w1{"def"};
	word::Word w2("abc");
	ASSERT(!(w1 < w2));
}

void test_opGTE_lt(){
	word::Word w1{"abc"};
	word::Word w2("def");
	ASSERT(!(w1 >= w2));
}

void test_opGTE_eq(){
	word::Word w1{"abc"};
	word::Word w2("abc");
	ASSERT(w1 >= w2);
}

void test_opGTE_gt(){
	word::Word w1{"def"};
	word::Word w2("Abc");
	ASSERT(w1 >= w2);
}

void test_opLTE_lt(){

}

void test_opLTE_eq(){

}

void test_opLTE_gt(){

}

void test_opEQ_lt(){

}

void test_opEQ_eq(){

}

void test_opEQ_gt(){

}

void test_opNEQ_lt(){

}

void test_opNEQ_eq(){

}

void test_opNEQ_gt(){

}

//IO Tests
void test_print(){

}

void test_read_once_valid(){

}

void test_read_twice_valid(){

}

void test_read_empty_invalid(){

}

void test_read_numeric_invalid(){

}

void test_read_twice_numericDelimiter_valid(){

}

void test_read_twice_invalidLetterDelimiter_valid(){

}

void test_read_four_multipleDelimiters_valid(){

}

void test_opOUT_valid(){

}

void test_opIN_valid(){

}

void test_opIN_invalid(){

}

//kwic tests
void test_2lines_3words(){
	std::istringstream in{"one two three\n four five six\n"};
	std::ostringstream out{};
	kwic::kwic(in, out);
	ASSERT_EQUAL(	"five six four \n"
					"four five six \n"
					"one two three \n"
					"six four five \n"
					"three one two \n"
					"two three one \n", out.str());
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
	s.push_back(CUTE(test_read_twice_invalidLetterDelimiter_valid));
	s.push_back(CUTE(test_read_four_multipleDelimiters_valid));
	s.push_back(CUTE(test_opOUT_valid));
	s.push_back(CUTE(test_opIN_valid));
	s.push_back(CUTE(test_opIN_invalid));

	//kwic tests
	s.push_back(CUTE(test_2lines_3words));
	push_back_AllTests(s);
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
