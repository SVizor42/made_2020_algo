#include "parser.h"
#include "expression.h"
#include "tokenizer.h"

Parser::Parser(char* line): tokens(new Tokenizer(line)) {};

Parser::~Parser() {
	delete tokens;
}

std::pair<std::string, Expression*> Parser::parseAssignment() {
	int mark = tokens->mark();
	VariableExpression *var = nullptr;
	Expression *rhs = nullptr;
	
	if ((var = tokens->variable()) && tokens->character('=') && (rhs = parseSum()) && tokens->atEnd()) {
		return {var->getVar(), new AssignmentExpression(var, rhs)};
	}
	
	if (var) {
		delete var;
	}
    if (rhs) {
		delete rhs;
    }
	tokens->reset(mark);
	
	return {nullptr, nullptr};
}

Expression* Parser::parseExpression() {
	int mark = tokens->mark();
	Expression *exp = nullptr;
	if (tokens->character('(') && (exp = parseSum()) && (tokens->character(')')))
		;
	else {
    	if (exp) {
    		delete exp;
    		exp = nullptr;
    		tokens->reset(mark);
    	}
	}
	
	return exp;
}

Expression* Parser::parseTerm() {
	Expression *exp = nullptr;
	if ((exp = parseExpression()) || (exp = tokens->variable()) || (exp = tokens->number()))
		;
		
	return exp;
}

Expression* Parser::parseFactor() {
	Expression *exp = nullptr;
	if (exp = parseTerm())
		;
		
	return exp;
}

Expression* Parser::parseSum() {
	int mark = tokens->mark();
	Expression *lhs = parseProduct();
	Expression *rhs;

	while (lhs) {
		if (tokens->character('+')) {
			if (rhs = parseProduct())
				lhs = new ArithmeticExpression('+', lhs, rhs);
			else {
				delete lhs;
				lhs = nullptr;
			}
		}
		else if (tokens->character('-')) {
			if (rhs = parseProduct())
				lhs = new ArithmeticExpression('-', lhs, rhs);
			else {
				delete lhs;
				lhs = nullptr;
			}
		}
		else {
			break;
		}
	}

	if (lhs == nullptr) {
		tokens->reset(mark);
	}
	
	return lhs;
}

Expression* Parser::parseProduct() {
	int mark = tokens->mark();
	Expression *lhs = parseFactor();
	Expression *rhs;
	
	while (lhs) {
		if (tokens->character('*')) {
			if (rhs = parseFactor())
				lhs = new ArithmeticExpression('*', lhs, rhs);
			else {
				delete lhs;
				lhs = nullptr;
			}
		}
		else {
		    if (tokens->character('/')) {
    			if (rhs = parseFactor()) {
    				lhs = new ArithmeticExpression('/', lhs, rhs);
    			}
    			else {
    				delete lhs;
    				lhs = nullptr;
    			}
    		}
    		else {
    			break;
    		}
		}
	}
	
	if (lhs == nullptr) {
		tokens->reset(mark);
	}
		
	return lhs;
}