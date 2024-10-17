#include<bits/stdc++.h>
using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    int flag = 0, i;
    string temp;
    const string keyword[] = {"int", "float", "if", "char", "return", "string", "char"};
    const char symbol[] = {',', '.', ';', '<', '>', '=', '#', ','};
    const string symbolName[] = {"comma", "point", "semicolon", "less than", "greater than", "equal", "hash", "comma"};

    char foundSym[100];
    int sym_count = 0;

    string found_keyword[100];
    int found_count = 0;

    string variables[100];  // To store variable names
    string var_types[100];  // To store the corresponding types
    int var_count = 0;

    if (input.is_open()) {
        while (getline(input, temp)) {
            string without;
            for (i = 0; i < temp.size(); i++) {
                if (temp[i] == '/' && temp[i + 1] == '/') {
                    break;
                } else if (temp[i] == '/' && temp[i + 1] == '*') {
                    flag = 1;
                    i++;
                } else if (((i + 1) < temp.size()) && temp[i] == '*' && temp[i + 1] == '/') {
                    flag = 0;
                    i++;
                    i++;
                }
                if (flag == 0 && i < temp.size()) {
                    without += temp[i];
                }
            }

            output << without << "\n";

            string word;
            string current_type = "";

            // Parsing variables and their types
            for (int j = 0; j < without.length(); j++) {
                char c = without[j];
                if (isalpha(c)) {
                    word = word + c;
                } else {
                    if (!word.empty()) {
                        if (j < without.length() && without[j] == '(') {
                            word.clear();
                            continue;
                        }

                        bool is_type = false;
                        for (int k = 0; k < 7; k++) {
                            if (word == keyword[k]) {
                                is_type = true;
                                current_type = word;
                                bool found = false;

                                for (int l = 0; l < found_count; l++) {
                                    if (word == found_keyword[l]) {
                                        found = true;
                                        break;
                                    }
                                }

                                if (!found) {
                                    found_keyword[found_count++] = word;
                                }
                            }
                        }

                        // Store variable name and type in arrays if it's a variable
                        if (!is_type && !current_type.empty()) {
                            bool found = false;
                            for (int v = 0; v < var_count; v++) {
                                if (variables[v] == word) {
                                    found = true;
                                    break;
                                }
                            }

                            if (!found) {
                                variables[var_count] = word;
                                var_types[var_count++] = current_type;
                            }
                        }
                        word.clear();
                    }
                }
            }

            // Parse for symbols
            for (int k = 0; k < without.length(); k++) {
                char c = without[k];
                for (int l = 0; l < 8; l++) {
                    if (c == symbol[l]) {
                        foundSym[sym_count++] = c;
                    }
                }
            }
        }
    }

    input.close();

    // Output keywords
    output << "\nKeywords:\n";
    for (int j = 0; j < found_count; j++) {
        output << found_keyword[j] << " ";
    }

    // Output symbols and their names
    output << "\nSymbol list:\n";
    for (int j = 0; j < sym_count; j++) {
        for (int k = 0; k < 8; k++) {
            if (symbol[k] == foundSym[j]) {
                output << symbol[k] << "  " << symbolName[k] << "\n";
            }
        }
    }

    // Output variable names and their types
    output << "\nVariable list with type:\n";
    for (int v = 0; v < var_count; v++) {
        output << "Variable: " << variables[v] << " Type: " << var_types[v] << endl;
    }

    output.close();

    return 0;
}
