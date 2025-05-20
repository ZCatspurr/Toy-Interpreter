#include <iostream>
#include <fstream>
#include "tokenizer.hpp"
#include "parser.hpp"
#include "lexer.hpp"

int WinMain() {
    string filename = "sample.txt";
    
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    unordered_map<string, int> global_vars;
    string line;
    while (getline(inputFile, line)) {
        line = line.substr(0, line.find("//"));
        if (line.empty()) continue;

        cout << "\nProcessing: " << line << endl;

        Tokenizer token(line);
        token.Tokened();
        
        Lexer lexed(token.getTokenedItems());
        lexed.print_Tokens();
        Parser parsed(lexed.get_tokens(), global_vars);
        parsed.process();

        auto new_vars = parsed.getMapping();
        global_vars.insert(new_vars.begin(), new_vars.end());
    
        cout << "Current variables:" << endl;
        for (auto& [var, val] : global_vars) {
            cout << var << " = " << val << endl;
        }
    }

    inputFile.close();
    return 0;
}