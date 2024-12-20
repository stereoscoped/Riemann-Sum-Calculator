#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <stdexcept>

using namespace std;

// Function prototypes
double parseExpression(const string& expression, size_t& pos, double xValue);
double parseTerm(const string& expression, size_t& pos, double xValue);
double parseFactor(const string& expression, size_t& pos, double xValue);
double parseNumber(const string& expression, size_t& pos, double xValue);
void skipWhitespace(const string& expression, size_t& pos);