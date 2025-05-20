#include "tokenizer.hpp"

Tokenizer::Tokenizer(){
    next_to_be_tokened = string();
}

Tokenizer::Tokenizer(const string passed_in){
    next_to_be_tokened = passed_in;
}

void Tokenizer::Tokened(){
    string temp = string();
    string semicolon = ";";

    for (char& ch: next_to_be_tokened){
        if (ch != ' ' && ch != ';') {
            temp += ch;
        } 
        if (ch == ' '){
            tokened.push_back(temp);
            temp.clear();
        }
        if (ch == ';'){
            tokened.push_back(temp);
            tokened.push_back(semicolon);
            temp.clear();
        }
    }
}

vector<string> Tokenizer::getTokenedItems(){
    return tokened;
}