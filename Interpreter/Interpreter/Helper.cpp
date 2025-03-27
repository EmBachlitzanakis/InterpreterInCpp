#include "Helper.h"



bool isLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_');
}

bool isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}
