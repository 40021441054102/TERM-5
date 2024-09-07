# include <iostream>
# include <sstream>
# include <string>

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
    UNKNOWN,
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

std::istringstream iss;

bool match(const std::string& token) {
    std::string line;
    std::getline(iss, line);
    return line.find(token) != std::string::npos;
}

bool parse_num() {
    std::string token;
    iss >> token;
    for (char c : token) {
        if (!isdigit(c) && c != '-') {
            return false;
        }
    }
    return true;
}

bool parse_type() {
    return match("char") || match("real") || match("integer");
}

bool parse_array();

bool parse_array_inner() {
    return match("[") && parse_num() && match("..") && parse_num() && match("]") && match("of") && (parse_type() || parse_array());
}

bool parse_array() {
    return match("array") && parse_array_inner();
}

bool parse() {
    return parse_array() && iss.eof();
}

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        iss.str(line);
        iss.clear();
        if (parse()) {
            std::cout << "parse successful!\n";
        } else {
            std::cout << "parse failure!\n";
        }
    }
    return 0;
}

int main() {
    char _char;
    State state = State::START;
    std::string token;
    while (std::cin.get(_char)) {
        switch (state) {
            case State::START:
                if (isdigit(_char)) {
                    state = State::NUM;
                    token = _char;
                } else if (isalpha(_char)) {
                    state = State::SIMPLE;
                    token = _char;
                } else if (_char == '^') {
                    state = State::ID;
                    token = _char;
                } else if (_char == 'a') {
                    state = State::ARRAY;
                    token = _char;
                } else if (_char == '.') {
                    state = State::DOTDOT;
                    token = _char;
                } else if (_char == 'o') {
                    state = State::OF;
                    token = _char;
                } else {
                    state = State::UNKNOWN;
                }
                break;
            case State::NUM:
                if (isdigit(_char)) {
                    token += _char;
                } else if (_char == '.' && state == State::ARRAY) {
                    // Allow a dot in array bounds, e.g., [-2..10]
                    token += _char;
                    state = State::DOTDOT;
                } else {
                    std::cout << "TYPE_NUM: " << token << '\n';
                    state = State::START;
                }
                break;
            case State::SIMPLE:
                if (isalpha(_char)) {
                    token += _char;
                } else {
                    std::cout << "TYPE_SIMPLE: " << token << '\n';
                    state = State::START;
                }
                break;
            case State::ID:
                if (isalpha(_char) || isdigit(_char)) {
                    token += _char;
                } else {
                    std::cout << "TYPE_ID: " << token << '\n';
                    state = State::START;
                }
                break;
            case State::ARRAY:
                if (_char == '[') {
                    token += _char;
                    state = State::NUM;
                } else {
                    std::cout << "TYPE_ARRAY: " << token << '\n';
                    state = State::START;
                }
                break;
            case State::DOTDOT:
                if (_char == '.') {
                    // Handle consecutive dots
                    token += _char;
                    if (token == "..") {
                        std::cout << "TYPE_DOTDOT: " << token << '\n';
                    } else {
                        std::cout << "TYPE_UNKNOWN: " << token << '\n';
                    }
                    state = State::START;
                } else if (isdigit(_char)) {
                    // Start accumulating digits for the second number
                    token += _char;
                    state = State::NUM;
                } else {
                    std::cout << "TYPE_DOTDOT: " << token << '\n';
                    state = State::START;
                }
                break;
            case State::OF:
                if (isspace(_char)) {
                    continue; // Skip spaces after 'of'
                } else if (isalpha(_char)) {
                    token = _char;
                    state = State::TYPE;
                } else {
                    std::cout << "TYPE_OF: " << token << '\n';
                    state = State::UNKNOWN;
                }
                break;
            case State::UNKNOWN:
                if (isspace(_char)) {
                    continue; // Skip spaces after unknown construct
                } else {
                    std::cout << "TYPE_UNKNOWN: " << token << '\n';
                    state = State::START;
                }
                break;
            case State::TYPE:
                if (isalpha(_char)) {
                    token += _char;
                } else {
                    std::cout << "TYPE_OF: " << token << '\n';
                    state = State::START;
                }
                break;
        }
    }
    return 0;
}
