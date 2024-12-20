#include "expressions.h"

// Function to skip whitespace
void skipWhitespace(const string& expression, size_t& pos) {
    while (pos < expression.size() && isspace(expression[pos])) {
        pos++;
    }
}

// Function to parse a number (including decimals or 'x')
double parseNumber(const string& expression, size_t& pos, double xValue) {
    skipWhitespace(expression, pos);
    double result = 0.0;
    size_t startPos = pos;

    // Read digits, including the decimal point or 'x' for the variable
    while (pos < expression.size() && (isdigit(expression[pos]) || expression[pos] == '.' || expression[pos] == 'x')) {
        pos++;
    }

    string numberStr = expression.substr(startPos, pos - startPos);

    if (numberStr == "x") {
        return xValue;  // Return the value of x when 'x' is found
    }

    result = stod(numberStr);  // Convert the substring to a double
    return result;
}

// Function to parse parentheses and numbers (including x)
double parseFactor(const string& expression, size_t& pos, double xValue) {
    skipWhitespace(expression, pos);
    double result = 0.0;

    if (expression[pos] == '(') {
        pos++;  // Consume '('
        result = parseExpression(expression, pos, xValue);  // Recursively parse inner expression
        skipWhitespace(expression, pos);
        if (expression[pos] == ')') {
            pos++;  // Consume ')'
        } else {
            throw runtime_error("Mismatched parentheses!");
        }
    } else {
        result = parseNumber(expression, pos, xValue);
    }

    return result;
}

// Function to parse exponentiation (handles '^')
double parseExponentiation(double base, const string& expression, size_t& pos, double xValue) {
    skipWhitespace(expression, pos);
    if (expression[pos] == '^') {
        pos++;  // Consume '^'
        double exponent = parseFactor(expression, pos, xValue);
        base = pow(base, exponent);  // Apply exponentiation
    }
    return base;
}

// Function to parse terms (handles '*' and '/')
double parseTerm(const string& expression, size_t& pos, double xValue) {
    double result = parseFactor(expression, pos, xValue);
    result = parseExponentiation(result, expression, pos, xValue);  // Handle exponentiation

    while (pos < expression.size()) {
        skipWhitespace(expression, pos);
        if (expression[pos] == '*') {
            pos++;  // Consume '*'
            result *= parseFactor(expression, pos, xValue);
        } else if (expression[pos] == '/') {
            pos++;  // Consume '/'
            double divisor = parseFactor(expression, pos, xValue);
            if (divisor == 0) throw runtime_error("Division by zero!");
            result /= divisor;
        } else {
            break;
        }
    }

    return result;
}

// Function to parse expressions (handles '+' and '-')
double parseExpression(const string& expression, size_t& pos, double xValue) {
    double result = parseTerm(expression, pos, xValue);

    while (pos < expression.size()) {
        skipWhitespace(expression, pos);
        if (expression[pos] == '+') {
            pos++;  // Consume '+'
            result += parseTerm(expression, pos, xValue);
        } else if (expression[pos] == '-') {
            pos++;  // Consume '-'
            result -= parseTerm(expression, pos, xValue);
        } else {
            break;
        }
    }

    return result;
}