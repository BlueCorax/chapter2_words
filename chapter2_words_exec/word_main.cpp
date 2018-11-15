#include "src/kwic.h"
#include <iostream>
#include <sstream>

int main(){
	auto input = "one two three\nfour five six\n\n";
	std::istringstream in{ input };
	std::ostringstream o{};
	std::cout << "input:\n" << input;
	kwic::kwic(in, o);
	std::cout << "output:\n";
	std::cout << o.str() << '\n';
}
