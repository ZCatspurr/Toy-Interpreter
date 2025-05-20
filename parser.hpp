#ifndef parser_hpp
#define parser_hpp

#include <stdio.h>
#include "lexer.hpp"
#include <deque>
#include <unordered_map>

class Parser {
    private:
        pair<string, string> curr_token;
        deque<pair<string, string>> symbols;
        unordered_map<string, int> mapping;
        unordered_map<std::string, int>& variables;

    public:
       // Parser(deque<pair<string, string>>);
        Parser(std::deque<std::pair<std::string, std::string>> tokens, 
           std::unordered_map<std::string, int>& vars);
        void get_Token();
        void matchings(string);
        void process();
        unordered_map<string, int> getMapping();
        int exp_manip();
        int exp();
        int term();
        int term_prime();
        int finExp();
};

#endif