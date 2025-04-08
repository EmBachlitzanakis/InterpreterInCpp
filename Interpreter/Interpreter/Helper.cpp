#include "Helper.h"



bool Helper::isLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_');
}

bool Helper::isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}
bool Helper::isWhitespace(char ch) {
	return (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');
}