//setting up build - setting source and dest folders: cmake -S . -B build/
//compile: cmake --build build/
//run: ./build/litecpp
//

#include <iostream>
#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

enum class TokenType {
    _return,
    int_literal,
    semicolon,
};


struct Token {
    TokenType type;
    std::optional<std::string> value{};
};

//build tokens
std::vector<Token> tokenize(std::string& input) {
    std::vector<Token> tokens;
    std::string buffer;
    for (int i = 0; i < input.length(); i++) {
        char c = input.at(i);
        if (std::isalpha(c)) {
            buffer.push_back(c);
            i++;
            while (std::isalnum(input.at(i))) {
                buffer.push_back(input.at(i));
                i++;
            }
            i--;

            if (buffer == "return") {
                tokens.push_back({.type = TokenType::_return});
                buffer.clear();
                continue;
            }else {
                std::cerr << "Error!!" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (std::isdigit(c)) {
            buffer.push_back(c);
            i++;
            while (std::isdigit(input.at(i))) {
                buffer.push_back(input.at(i));
                i++;
            }
            i--;
            tokens.push_back(Token{TokenType::int_literal, buffer});
            buffer.clear();
        }
        else if (c == ';') {
            tokens.push_back(Token{TokenType::semicolon});
        }
        else if (std::isspace(c)) {
            continue;
        }else {
            std::cerr << "Error!!" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    return tokens;
}


//convert token to assembly
std::string tokens_to_asm(const std::vector<Token>& inputToken) {
    std::stringstream output;
    output << "global _start\n_start:\n";
    for (int i = 0; i < inputToken.size(); i++) {
        const Token& token = inputToken.at(i);
        //if it is 'return' check whether there are at-least two more tokens and that ar integer and semicolon.
        if (token.type == TokenType::_return) {
            if (i+1 < inputToken.size() &&
                inputToken.at(i+1).type == TokenType::int_literal) {
                if (i+2 < inputToken.size() &&
                    inputToken.at(i+2).type == TokenType::semicolon) {
                    output <<" mov rax, 60\n";
                    output <<" mov rdi, " << inputToken.at(i+1).value.value() << "\n";
                    output <<" syscall";
                }

            }
        }
    }
    return output.str();
}

int main(int argc, char* argv[]){
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input filename>.lcp" << std::endl;
        return EXIT_FAILURE;
    }

    std::stringstream ss;
    std::fstream input(argv[1], std::ios::in);
    ss << input.rdbuf();

    std::string content = ss.str();
    input.close();

    //std::cout << content << std::endl;
    std::vector<Token> tokens = tokenize(content);
    //std::cout << tokens_to_asm(tokens) << std::endl;

    //create assembly file
    std::fstream outFile ("out.asm", std::ios::out);
    outFile <<tokens_to_asm(tokens) ;

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");
    return 0;
}