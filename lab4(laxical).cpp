#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;

int main()
{
    ifstream inputfile("input1.txt");
    ofstream outputfile("output1.txt");

    string temp;
    int flag = 0;
    const string keywords[] = {"int", "float", "void", "if", "else"};
    string found_keywords[10];
    int found_count = 0;

    const char symbol[] = {'#', '(', ')', ';', '<', '>', '='};
    const string symbol_name[] = {"hash", "opening bracket", "closing bracket", "semicolon", "lt", "gt", "eq"};

    struct Token {
        string lexeme;
        string token_name;
        string attribute_value;
    };

    Token tokens[100];  // To store the tokens
    int token_count = 0;

    string variables[100];
    string var_types[100];
    int var_count = 0;

    string num_array[1000];
    string num_types[1000];  // To store the type of numbers (int or float)
    int ncount = 0;

    const int num_keywords = sizeof(keywords) / sizeof(keywords[0]);
    const int num_symbol = sizeof(symbol) / sizeof(symbol[0]);

    if (inputfile.is_open())
    {
        while (getline(inputfile, temp))
        {
            string line_without_comments;
            for (int i = 0; i < temp.length(); i++)
            {
                if (temp[i] == '/' && temp[i + 1] == '/')
                {
                    break;
                }
                if (temp[i] == '/' && temp[i + 1] == '*')
                {
                    flag = 1;
                    i++;
                    continue;
                }
                if (temp[i] == '*' && temp[i + 1] == '/')
                {
                    flag = 0;
                    i++;
                    continue;
                }
                if (flag == 0)
                {
                    line_without_comments += temp[i];
                }
            }

            string num;
            string word;
            string current_type = "";
            bool is_type = false;

            for (int i = 0; i <= line_without_comments.length(); i++)
            {
                char c = line_without_comments[i];

                if (isalpha(c) || (word.length() > 0 && (isdigit(c) || c == '_')))
                {
                    word += c;
                }
                else if (isdigit(c) || c == '.')
                {
                    num += c;
                }
                else
                {
                    if (!num.empty())
                    {
                        // Classify the number as int or float
                        if (num.find('.') != string::npos)
                        {
                            num_types[ncount] = "float";
                        }
                        else
                        {
                            num_types[ncount] = "int";
                        }

                        // Add to token table
                        tokens[token_count++] = {num, "number", num_types[ncount]};
                        num_array[ncount++] = num;
                        num.clear();
                    }

                    if (!word.empty())
                    {
                        bool is_keyword = false;
                        for (int j = 0; j < num_keywords; j++)
                        {
                            if (word == keywords[j])
                            {
                                found_keywords[found_count++] = word;
                                tokens[token_count++] = {word, "keyword", ""};
                                is_type = true;
                                current_type = word;
                                is_keyword = true;
                            }
                        }

                        if (!is_keyword && !current_type.empty())
                        {
                            bool found = false;
                            for (int v = 0; v < var_count; v++)
                            {
                                if (variables[v] == word)
                                {
                                    found = true;
                                    break;
                                }
                            }

                            if (!found)
                            {
                                variables[var_count] = word;
                                var_types[var_count] = current_type;
                                tokens[token_count++] = {word, "id", "pointer to symbol table entry " + to_string(var_count + 1)};
                                var_count++;
                            }
                        }
                        word.clear();
                        is_type = false;
                    }

                    for (int k = 0; k < num_symbol; k++)
                    {
                        if (c == symbol[k])
                        {
                            tokens[token_count++] = {string(1, c), "special symbol", symbol_name[k]};
                        }
                    }
                }
            }
        }

        inputfile.close();
    }

    // Output Token Table
    outputfile << "Tokens Table\n";
    outputfile << "Lexemes\t\tToken Name\t\tAttribute Value\n";
    for (int i = 0; i < token_count; i++)
    {
        outputfile << tokens[i].lexeme << "\t\t" << tokens[i].token_name << "\t\t" << tokens[i].attribute_value << "\n";
    }

    // Output Symbol Table
    outputfile << "\nSymbol Table:\n";
    outputfile << "Symbol\t\tToken\t\tData Type\tPointer\n";
    for (int v = 0; v < var_count; v++)
    {
        outputfile << variables[v] << "\t\tid\t\t" << var_types[v] << "\t\t" << (v + 1) << "\n";
    }

    outputfile.close();

    return 0;
}
