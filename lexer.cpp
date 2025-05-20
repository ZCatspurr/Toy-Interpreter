#include "lexer.hpp"
#include <iostream>
#include <cctype>

using namespace std;

Lexer::Lexer(vector<string> tokened){
    int u = 1;
    bool flag = true;

    for (auto t: tokened){
        if (isalpha(t[0]) || t[0] == '_'){
            while (u < t.length() && flag == true){
                if (isalpha(t[u]) || t[u] == '_' || isdigit(t[u])){
                    u++;
                } else {
                    flag = false;
                }
            }
            if (flag){
                tokens.push_back(pair<string, string>("identifier", t));
            }
        }
        else if (t[0] == '='){
            tokens.push_back(pair<string, string>("equals", t));
        } else if (t[0] == '-') {
            if (t.length() > 1 && t[1] == '-') {
            tokens.push_back({"minus", t.substr(0,1)});
            tokens.push_back({"minus", t.substr(1)}); 
            } else {
            tokens.push_back(pair<string, string>("minus", t));
            }
        } else if (t[0] == '+') {
            tokens.push_back(pair<string, string>("plus", t));
        } else if (t[0] == '*') {
            tokens.push_back(pair<string, string>("multiply", t));
        } else if (t[0] == '(') {
            tokens.push_back(pair<string, string>("left", t));
        } else if (t[0] == ')') {
            tokens.push_back(pair<string, string>("right", t));
        } else if (t[0] == ';') {
            tokens.push_back(pair<string, string>("semi", t));
        } else if (t[0] == '0' && t.length() == 1) {
            tokens.push_back(pair<string, string>("literal", t));
        }
        else if (t[0] >= '1' && t[0] <= '9'){
            flag = true;
            u = 1;
            while (u < t.length() && flag == true){
                if (!isdigit(t[u])){
                    flag = false;
                }
                u++;
            }
            if (flag){
                tokens.push_back(pair<string, string>("literal", t));
            }
        }
        else {
            tokens.push_back(pair<string, string>("error", "Invalid input: " + t));
        }
    }
}

void Lexer::print_Tokens(){
    for (auto t: tokens){
        cout << t.first << ": " << t.second << endl;
    }
}

deque<pair<string,string>> Lexer::get_tokens(){
    return tokens;
}