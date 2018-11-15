#include "src/kwic.h"
#include <iostream>
#include <sstream>

int main(){
	std::istringstream in{"one two three\n four five six"};
	std::ostringstream o{};
	kwic::kwic(in, o);
	std::cout << o.str() << '\n';
}
