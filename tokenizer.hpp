#ifndef tokenizer_hpp
#define tokenizer_hpp

#include<stdio.h>
#include <string>
#include <vector>

using namespace std;

class Tokenizer {
    private:
        vector<string> tokened;
        string next_to_be_tokened;
        
    public:
        Tokenizer();
        Tokenizer(string);
        void Tokened();
        vector<string> getTokenedItems();
};
#endif