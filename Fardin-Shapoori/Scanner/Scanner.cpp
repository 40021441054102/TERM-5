#include <iostream>
#include <string>

#define SUCCESS "\033[38;2;0;255;0m[SUCCESS]\033[0m "
#define FAILED "\033[38;2;255;0;0m[FAILED]\033[0m "

enum States {
    STATE_START,
    STATE_SIMPLE,
    STATE_ID,
    STATE_ARRAY,
    STATE_NUM,
    STATE_DOTDOT,
    STATE_OF,
    STATE_TYPE,
    STATE_REAL,
    STATE_INTEGER,
    STATE_CHAR,
    STATE_UNKNOWN,
    STATE_END
};

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isSpace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
}

int main() {
    char character;
    int state = STATE_START;
    std::string token;
    int lastState = STATE_START;

    while (std::cin.get(character)) {
        switch (state) {
            case STATE_START: {
                if (character == '^') {
                    state = STATE_ID;
                    token = character;
                } else if (character == '.') {
                    state = STATE_DOTDOT;
                    token = character;
                } else if (character == 'o') {
                    state = STATE_OF;
                    token = character;
                    std::cout << SUCCESS "TYPE [OF] : " << token << std::endl;
                } else if (isDigit(character)) {
                    state = STATE_NUM;
                    token = character;
                } else if (isAlpha(character)) {
                    state = STATE_SIMPLE;
                    token = character;
                } else {
                    state = STATE_UNKNOWN;
                }
                break;
            }
            case STATE_NUM: {
                if (isDigit(character) || (character == '.' && lastState == STATE_DOTDOT)) {
                    token += character;
                } else if (character == '.') {
                    std::cout << SUCCESS "TYPE [NUM] : " << token << std::endl;
                    if (state == STATE_ARRAY) {
                        token = character;
                        state = STATE_DOTDOT;
                    } else {
                        if (lastState == STATE_DOTDOT) {
                            std::cout << FAILED "TYPE [UNKNOWN] : " << token << std::endl;
                        }
                        state = STATE_START;
                    }
                } else {
                    if (lastState != STATE_DOTDOT) {
                        std::cout << SUCCESS "TYPE [NUM] : " << token << std::endl;
                        state = STATE_START;
                    } else {
                        if (token != "..") {
                            std::cout << SUCCESS "TYPE [NUM] : " << token << std::endl;
                            token = "";
                            state = STATE_START;
                        }
                    }
                }
                break;
            }
            case STATE_SIMPLE: {
                if (isAlpha(character)) {
                    token += character;
                    if (token == "array") {
                        state = STATE_ARRAY;
                    } else if (token == "real") {
                        state = STATE_REAL;
                    } else if (token == "integer") {
                        state = STATE_INTEGER;
                    } else if (token == "char") {
                        state = STATE_CHAR;
                    }
                } else {
                    std::cout << SUCCESS "TYPE [SIMPLE] : " << token << std::endl;
                    state = STATE_START;
                }
                break;
            }
            case STATE_ID: {
                if (isAlpha(character) || isDigit(character)) {
                    token += character;
                } else {
                    std::cout << SUCCESS "TYPE [ID] : " << token << std::endl;
                    state = STATE_START;
                }
                break;
            }
            case STATE_ARRAY: {
                if (character == '[') {
                    token += character;
                    state = STATE_NUM;
                } else {
                    std::cout << SUCCESS "TYPE [ARRAY] : " << token << std::endl;
                    state = STATE_START;
                }
                break;
            }
            case STATE_DOTDOT: {
                if (character == '.') {
                    token += character;
                    if (token == "..") {
                        std::cout << SUCCESS "TYPE [DOTDOT] : " << token << std::endl;
                        state = STATE_NUM;
                        lastState = STATE_DOTDOT;
                    } else {
                        if (isDigit(character) || isSpace(character)) {
                            token = character;
                            state = STATE_NUM;
                        } else {
                            std::cout << FAILED "TYPE [UNKNOWN] : " << token << std::endl;
                            state = STATE_START;
                        }
                    }
                } else if (isDigit(character)) {
                    token += character;
                    state = STATE_NUM;
                } else {
                    std::cout << SUCCESS "TYPE [DOTDOT] : " << token << std::endl;
                    state = STATE_START;
                }
                break;
            }
            case STATE_OF: {
                if (isSpace(character)) {
                    continue;
                } else if (isAlpha(character)) {
                    token = character;
                    state = STATE_TYPE;
                } else {
                    std::cout << FAILED "TYPE [OF] : " << token << std::endl;
                    state = STATE_UNKNOWN;
                }
                break;
            }
            case STATE_TYPE: {
                if (isAlpha(character)) {
                    token += character;
                } else {
                    std::cout << SUCCESS "TYPE [TYPE] : " << token << std::endl;
                    state = STATE_START;
                }
                break;
            }
            case STATE_REAL: {
                if (isDigit(character)) {
                    token += character;
                } else {
                    std::cout << SUCCESS "TYPE [REAL] : " << token << std::endl;
                    state = STATE_START;
                }
                break;
            }
            case STATE_INTEGER: {
                if (isDigit(character)) {
                    token += character;
                } else {
                    std::cout << SUCCESS "TYPE [INTEGER] : " << token << std::endl;
                    state = STATE_START;
                }
            }
            case STATE_CHAR: {
                if (character == '\'') {
                    std::cout << SUCCESS "TYPE [CHAR] : " << token << std::endl;
                    state = STATE_START;
                } else {
                    token += character;
                }
                break;
            }
            case STATE_UNKNOWN: {
                std::cout << FAILED "TYPE [UNKNOWN] : " << character << std::endl;
                state = STATE_START;
                break;
            }
            case STATE_END: {
                break;
            }
        }

        if (state != STATE_NUM) {
            lastState = state;
        }
    }

    return 0;
}
