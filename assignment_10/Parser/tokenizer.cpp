#include <cctype>
#include "tokenizer.h"
#include "expression.h"

Tokenizer::Tokenizer(char* data) : str(std::string(data)) {};

NumberExpression* Tokenizer::number() {
	this->skipWhiteSpace();
	char symbol = str.peek();
	if (std::isdigit(symbol)) {
		double x;
		str >> x;
		return new NumberExpression(x);
	}
	
	return nullptr;
}

VariableExpression* Tokenizer::variable() {
	this->skipWhiteSpace();
	char symbol = str.peek();
	std::string s;
	while (std::isalpha(symbol) || symbol == '_') {
		symbol = str.get();
		s += symbol;
		symbol = str.peek();
	}
	
	if (s.length() > 0) {
		return new VariableExpression(s);
	}
		
	return nullptr;
}

bool Tokenizer::character(char expected) {
	this->skipWhiteSpace();
	char symbol = str.peek();
	if (symbol == expected) {
		symbol = str.get();
		return true;
	}
	
	return false;
}

int Tokenizer::mark() {
	return str.tellg();
}

bool Tokenizer::atEnd() {
	return str.eof();
}

void Tokenizer::reset(int mark) {
	str.clear();
	str.seekg(mark);
}

void Tokenizer::skipWhiteSpace() {
	char symbol = str.peek();
	while (symbol == ' ' || symbol == '\t') {
		symbol = str.get();
		symbol = str.peek();
	}
}
