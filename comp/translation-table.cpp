# include <iostream>
# include <string>
# include <vector>

enum class State {
    START,
    SIMPLE,
    ID,
    ARRAY,
    NUM,
    DOTDOT,
    OF,
    TYPE,
    REAL,
    INTEGER,
    CHAR,
    NONE,
    END
};

bool isdigit(char c) {
    return c >= '0' && c <= '9';
}

bool isalpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isspace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
}

int main() {
    // Define the translation table
    std::vector<std::vector<State>> translationTable = {
        //        alphabet          dot              of               [                 ]            ^              other
        /* START */     {State::SIMPLE,  State::DOTDOT,    State::OF,      State::ARRAY,   State::NONE,    State::ID,      State::NONE},
        /* SIMPLE */    {State::REAL,    State::INTEGER,   State::CHAR,    State::NUM,     State::DOTDOT,  State::NONE,    State::NONE},
        /* ID */        {State::NONE,    State::NONE,      State::NONE,    State::NONE,    State::NONE,    State::NONE,    State::NONE},
        /* ARRAY */     {State::NONE,    State::DOTDOT,    State::NONE,    State::NONE,    State::NONE,    State::NONE,    State::NONE},
        /* NUM */       {State::NONE,    State::DOTDOT,    State::NONE,    State::NONE,    State::NONE,    State::NONE,    State::NONE},
        /* DOTDOT */    {State::NONE,    State::NONE,      State::NONE,    State::NONE,    State::NONE,    State::NONE,    State::NONE},
        /* OF */        {State::TYPE,    State::NONE,      State::NONE,    State::NONE,    State::NONE,    State::NONE,    State::NONE},
        /* TYPE */      {State::SIMPLE,  State::NONE,      State::NONE,    State::NONE,    State::NONE,    State::NONE,    State::NONE},
        /* REAL */      {State::NONE,    State::NONE,      State::NONE,    State::NONE,    State::NONE,    State::NONE,    State::NONE},
        /* INTEGER */   {State::NONE,    State::NONE,      State::NONE,    State::NONE,    State::NONE,    State::NONE,    State::NONE},
        /* CHAR */      {State::NONE,    State::NONE,      State::NONE,    State::NONE,    State::NONE,    State::NONE,    State::NONE},
        /* NONE */      {State::NONE,    State::NONE,      State::NONE,    State::NONE,    State::NONE,    State::NONE,    State::NONE},
        /* END */       {State::END,     State::END,       State::END,     State::END,     State::END,     State::END,     State::END}
    };
    char _char;
    State state = State::START;
    std::string token;
    while (std::cin.get(_char)) {
        switch (state) {
            case State::START: {
                for (int i = 0; i < translationTable[0].size(); i++) {
                    if (isalpha(_char)) {
                        state = translationTable[0][0];
                        token = _char;
                    } else if (_char == '.') {
                        state = translationTable[0][1];
                        token = _char;
                    } else if (_char == 'o') {
                        state = translationTable[0][2];
                        token = _char;
                    } else if (_char == '[') {
                        state = translationTable[0][3];
                        token = _char;
                    } else if (_char == ']') {
                        state = translationTable[0][4];
                        token = _char;
                    } else if (_char == '^') {
                        state = translationTable[0][5];
                        token = _char;
                    } else {
                        state = translationTable[0][6];
                    }
                }
                break;
            }
            case State::SIMPLE: {
                for (int i = 0; i < translationTable[1].size(); i++) {
                    if (isalpha(_char)) {
                        state = translationTable[1][0];
                        token += _char;
                    } else if (isdigit(_char)) {
                        state = translationTable[1][1];
                        token += _char;
                    } else if (_char == '\'') {
                        state = translationTable[1][2];
                        token += _char;
                    } else if (_char == '.') {
                        state = translationTable[1][3];
                        token += _char;
                    } else if (_char == 'o') {
                        state = translationTable[1][4];
                        token += _char;
                    } else {
                        state = translationTable[1][5];
                    }
                }
                break;
            }
            case State::ID: {
                for (int i = 0; i < translationTable[2].size(); i++) {
                    if (isalpha(_char) || isdigit(_char)) {
                        state = translationTable[2][0];
                        token += _char;
                    } else {
                        state = translationTable[2][1];
                    }
                }
                break;
            }
            case State::ARRAY: {
                for (int i = 0; i < translationTable[3].size(); i++) {
                    if (_char == '[') {
                        state = translationTable[3][0];
                        token += _char;
                    } else {
                        state = translationTable[3][1];
                    }
                }
                break;
            }
            case State::NUM: {
                for (int i = 0; i < translationTable[4].size(); i++) {
                    if (isdigit(_char)) {
                        state = translationTable[4][0];
                        token += _char;
                    } else if (_char == '.' && state == State::ARRAY) {
                        // Allow a dot in array bounds, e.g., [-2..10]
                        token += _char;
                        state = translationTable[4][1];
                    } else {
                        state = translationTable[4][2];
                    }
                }
                break;
            }
            case State::DOTDOT: {
                for (int i = 0; i < translationTable[5].size(); i++) {
                    if (_char == '.') {
                        // Handle consecutive dots
                        token += _char;
                        if (token == "..") {
                            state = translationTable[5][0];
                        } else {
                            state = translationTable[5][1];
                        }
                    } else if (isdigit(_char)) {
                        // Start accumulating digits for the second number
                        token += _char;
                        state = translationTable[5][2];
                    } else {
                        state = translationTable[5][3];
                    }
                }
                break;
            }
            case State::OF: {
                for (int i = 0; i < translationTable[6].size(); i++) {
                    if (isspace(_char)) {
                        continue; // Skip spaces after 'of'
                    } else if (isalpha(_char)) {
                        state = translationTable[6][0];
                        token += _char;
                    } else {
                        state = translationTable[6][1];
                    }
                }
                break;
            }
            case State::TYPE: {
                for (int i = 0; i < translationTable[7].size(); i++) {
                    if (isalpha(_char)) {
                        state = translationTable[7][0];
                        token += _char;
                    } else {
                        state = translationTable[7][1];
                    }
                }
                break;
            }
            case State::REAL: {
                for (int i = 0; i < translationTable[8].size(); i++) {
                    state = translationTable[8][0];
                }
                break;
            }
            case State::INTEGER: {
                for (int i = 0; i < translationTable[9].size(); i++) {
                    state = translationTable[9][0];
                }
                break;
            }
            case State::CHAR: {
                for (int i = 0; i < translationTable[10].size(); i++) {
                    state = translationTable[10][0];
                }
                break;
            }
            case State::NONE: {
                for (int i = 0; i < translationTable[11].size(); i++) {
                    if (isspace(_char)) {
                        continue; // Skip spaces after unknown construct
                    } else {
                        state = translationTable[11][0];
                    }
                }
                break;
            }
            case State::END: {
                for (int i = 0; i < translationTable[12].size(); i++) {
                    state = translationTable[12][0];
                }
                break;
            }
        }
    }
    return 0;
}
