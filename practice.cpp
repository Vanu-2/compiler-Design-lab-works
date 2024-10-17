#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;

int main()
{
    ifstream inputfile("input.txt");
    ofstream outputfile("output.txt");

    string temp;
    int flag = 0;
    const string keywords[] = {"int", "float", "void", "if", "else"};
    string found_keywords[10];
    int found_count = 0;

    const char symbol[] = {'#', '(', ')', ';', '<', '>', '='};
    const string symbol_name[] = {"hash", "opening bracket", "closing bracket", "semicolon", "lt", "gt", "eq"};

    string founds[100];
    int scount = 0;

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

            outputfile << line_without_comments << "\n";
            string num;

            string word;
            string current_type = "";
            bool is_type = false;

            for (int i = 0; i <= line_without_comments.length(); i++)
            {
                char c = line_without_comments[i];

                if (isalpha(c) || (word.length() > 0 && (isdigit(c) || c == '_')))
                {
                    word = word + c;
                }
                else if (isdigit(c) || c == '.')
                {
                    num = num + c;
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

                        num_array[ncount++] = num;
                        num.clear();
                    }

                    if (!word.empty())
                    {
                        if (i < line_without_comments.length() && line_without_comments[i] == '(')
                        {
                            word.clear();
                            continue;
                        }

                        for (int j = 0; j < num_keywords; j++)
                        {
                            if (word == keywords[j])
                            {
                                found_keywords[found_count++] = word;
                                is_type = true;
                                current_type = word;
                            }
                        }

                        if (!is_type && !current_type.empty())
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
                                var_types[var_count++] = current_type;
                            }
                        }

                        word.clear();
                        is_type = false;
                    }

                    for (int k = 0; k < num_symbol; k++)
                    {
                        if (c == symbol[k])
                        {
                            founds[scount++] = string(1, c) + "   :   " + symbol_name[k];
                        }
                    }
                }
            }
        }

        inputfile.close();
    }

    outputfile << "\nKeyword list: ";
    for (int i = 0; i < found_count; i++)
    {
        outputfile << found_keywords[i] << " ";
    }

    outputfile << "\nSymbol list with names:\n";
    for (int i = 0; i < scount; i++)
    {
        outputfile << founds[i] << "\n";
    }

    outputfile << "\nSymbol Table:\n";
    outputfile << "\nVariable\t";
    outputfile << "type \n";
    for (int v = 0; v < var_count; v++)
    {
        outputfile << variables[v] << " \t \t \t" << var_types[v] << endl;
    }

    outputfile << "\nNumber list with types:\n";
    for (int i = 0; i < ncount; i++)
    {
        outputfile << num_array[i] << " (" << num_types[i] << ")\n";
    }

    outputfile.close();

    return 0;
}
