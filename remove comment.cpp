#include <iostream>

using namespace std;

void removeComments() {
    char ch;
    bool inBlockComment = false, inLineComment = false;

    while (cin.get(ch)) {
        if (inBlockComment) {

            if (ch == '*' && cin.peek() == '/') {
                cin.get();
                inBlockComment = false;
            }
        }
        else if (inLineComment) {

            if (ch == '\n') {
                inLineComment = false;
                cout << ch;
            }
        }
        else
        {

            if (ch == '/' && cin.peek() == '*') {
                cin.get();
                inBlockComment = true;
             }

            else if (ch == '/' && cin.peek() == '/') {
                cin.get();
                inLineComment = true;
            }

            else {
                cout << ch;
            }

        }
    }
}

int main() {

    freopen("main.cpp", "r", stdin);
    freopen("output.cpp", "w", stdout);

    //cout << "Hello World" << endl;
removeComments();
}
