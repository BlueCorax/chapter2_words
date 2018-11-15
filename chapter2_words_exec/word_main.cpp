#include "src/kwic.h"
#include <iostream>
#include <sstream>

int main(){
	auto input = "one two three\n four five six\n";
	std::istringstream in{ input };
	std::ostringstream o{};
	std::cout << "input: " << input;
	kwic::kwic(in, o);
	std::cout << o.str() << '\n';
}
