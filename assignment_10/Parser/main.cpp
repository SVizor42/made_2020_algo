#include <iostream>
#include <memory>
#include <utility>
#include "expression.h"
#include "parser.h"
#include "tokenizer.h"

int main() {
	char buffer[128];

	std::cout << "Enter an expression to evaluate: \n";
	while (std::cin >> buffer) {
		if (buffer[0] == '\0')
			break;
		Parser p(buffer);
        std::pair<std::string, Expression*> result = p.parseAssignment();

		std::string id = result.first;		
		Expression* e = result.second;
		if (e) {
		    std::cout << id << "=";
			std::cout << e->evaluate() << std::endl;
			delete e;
		}
		else {
			std::cout << "Error" << std::endl;
		}
	}

	return 0;
}
