#include <iostream>
#include <sstream>
#include <string>

std::istringstream iss;

bool match(const std::string& token) {
    std::string input_token;
    iss >> input_token;
    return input_token == token;
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