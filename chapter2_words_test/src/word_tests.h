#ifndef SRC_WORD_TESTS_H_
#define SRC_WORD_TESTS_H_

#include "cute.h"

void test_cannot_create_empty_word();

void test_cannot_create_word_with_space();

void test_cannot_create_word_with_number();

void test_cannot_create_word_with_punctuation();

void test_output_operator();

void test_same_words_are_equal();

void test_different_words_are_not_equal();

void test_same_word_with_different_cases_are_equal();

void test_same_word_is_not_lower_than();

void test_smaller_word_is_smaller();

void test_smaller_word_with_capital_letters_is_smaller();

void test_same_word_with_different_cases_are_not_smaller();

void test_greater_word_is_greater();

void test_greater_word_with_capital_letters_is_greater();

void test_smaller_word_is_less_equal();

void test_same_word_is_less_equal();

void test_greater_word_is_greater_equal();

void test_same_word_is_greater_equal();
void test_input_operator_single_word();

void test_input_operator_single_word_stream_good();

void test_input_operator_called_once_first_word();

void test_input_operator_called_once_stream_good();

void test_input_operator_on_empty_stream_fail();

void test_input_operator_on_stream_without_word();

void test_input_operator_on_empty_stream_word_unchanged();

void test_input_operator_stops_on_slash();

void test_input_operator_stops_at_end_of_word();

void test_input_operator_skips_leading_non_alpha();

void test_input_operator_overwrites_word();

void test_exercise_example();

void push_back_AllTests(cute::suite & s);
#endif /* SRC_WORD_TESTS_H_ */
