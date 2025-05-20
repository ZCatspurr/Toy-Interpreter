#include "parser.hpp"
#include <deque>
#include <iostream>

using namespace std;


Parser::Parser(std::deque<std::pair<std::string, std::string>> tokens, 
               std::unordered_map<std::string, int>& vars)
    : symbols(tokens), variables(vars), curr_token({"",""}) {
    if (!tokens.empty()) {
        curr_token = tokens.front();
    }
}

void Parser::get_Token() {
    curr_token = symbols.front();
    symbols.pop_front();
}

void Parser::matchings(string token) {
    if (token == curr_token.first) {
        get_Token();
    } else {
        cerr << "Parser Error: Expected '" << token 
             << "' but received '" << curr_token.first 
             << "'" <<  endl;
        exit(EXIT_FAILURE); 
    }
}

void Parser::process() {
    while (!symbols.empty()) {
        if (curr_token.first == "identifier") {
            string var_name = curr_token.second;
            matchings("identifier");
            matchings("equals");
            
            int value = exp(); 
            mapping[var_name] = value;
            
            if (!symbols.empty() && curr_token.first == "semi") {
                matchings("semi");
            } else {
                cerr << "Error: Missing semicolon after expression" << endl;
                break;
            }
        }
        else {
            cerr << "Error: Unexpected token '" << curr_token.first 
                 << "' at start of statement" << endl;
            if (!symbols.empty()) {
                symbols.pop_front();
                curr_token = symbols.empty() ? pair{"", ""} : symbols.front();
            }
            continue;
        }
    }
}

unordered_map<string, int> Parser::getMapping(){
    return mapping;
}

int Parser::exp_manip(){
    if (curr_token.first == "plus"){
        matchings("plus");
        return exp();
    } 
    if (curr_token.first == "minus"){
        matchings("minus");
        return -exp();
    } 
    return 0;
}

int Parser::exp() {
    int left = term();
    while (curr_token.first == "plus" || curr_token.first == "minus") {
        string op = curr_token.first;
        get_Token();
        int right = term();
        left = (op == "plus") ? left + right : left - right;
    }
    return left;
}

int Parser::term_prime(){
    matchings("multiply");
    return term();
}

int Parser::term() {
    int left = finExp();
    while (curr_token.first == "multiply" || curr_token.first == "divide") {
        string op = curr_token.first;
        get_Token();
        int right = finExp();
        left = (op == "multiply") ? left * right : left / right;
    }
    return left;
}

int Parser::finExp() {
    if (curr_token.first == "minus") {
        get_Token();
        return -finExp();  
    }
    else if (curr_token.first == "plus") {
        get_Token();
        return finExp(); 
    }
    else if (curr_token.first == "left") {
        get_Token();
        int num = exp(); 
        matchings("right");
        return num;
    }
    else if (curr_token.first == "literal") {
        int num = stoi(curr_token.second);
        get_Token();  
        return num;
    }
    else if (curr_token.first == "identifier") {
        if (mapping.find(curr_token.second) == mapping.end()) {
            cerr << "Error: Variable '" << curr_token.second << "' not defined\n";
            exit(EXIT_FAILURE);
        }
        int val = mapping[curr_token.second];
        get_Token();
        return val;
    }
    else {
        cerr << "Error: Unexpected token '" << curr_token.first 
             << "' with value '" << curr_token.second << "'\n";
        exit(EXIT_FAILURE);
    }
}