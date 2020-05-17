#include <cmath>
#include "expression.h"

std::map<std::string, double> Expression::vars;

double Expression::lookUp(const std::string& var) {
	if (vars.find(var) != vars.end()) {
		return vars[var];
	}
	
	return 0;
}

void Expression::record(const std::string& var, double value) {
	vars[var] = value;
}

double NumberExpression::evaluate() {
	return value;
}

double VariableExpression::evaluate() {
	return Expression::lookUp(variable);
}

ArithmeticExpression::~ArithmeticExpression() {
	if (left) {
		delete left;
	}
	if (right) {
		delete right;
	}
}

double ArithmeticExpression::evaluate() {
	if (left == nullptr || right == nullptr) {
		return 0;
	}

	double result = 0;
	double a = left->evaluate();
	double b = right->evaluate();
	
	switch (op) {
	    case '+':
		    result = a + b;
		    break;
	    case '-':
		    result = a - b;
		    break;
	    case '*':
		    result = a * b;
		    break;
	    case '/':
		    result = a / b;
	}
	
	return result;
}

AssignmentExpression::~AssignmentExpression() {
	if (var) {
		delete var;
	}
	if (value) {
		delete value;
	}
}

double AssignmentExpression::evaluate() {
	double result = 0;
	if (value) {
		result = value->evaluate();
	}
	if (var) {
		Expression::record(var->getVar(), result);
	}
	
	return result;
}
