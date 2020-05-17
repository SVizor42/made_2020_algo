#pragma once
#include <string>
#include <utility>

class Expression;
class Tokenizer;

class Parser {
public:
	Parser(char* line);
	~Parser();

    std::pair<std::string, Expression*> parseAssignment();
	
private:
	Tokenizer* tokens;

	Expression* parseExpression();
	Expression* parseTerm();
	Expression* parseFactor();
	Expression* parseProduct();
	Expression* parseSum();
};
