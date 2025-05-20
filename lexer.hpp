#ifndef lexer_hpp
#define lexer_hpp

#include <stdio.h>
#include <regex>
#include <string>
#include <deque>
#include<vector>
#include "tokenizer.hpp"

class Lexer {
    private:
        deque<pair<string, string>> tokens;
    
    public:
        Lexer(vector<string> tokened);
        deque<pair<string, string>> get_tokens();
        void print_Tokens();  
};
#endif