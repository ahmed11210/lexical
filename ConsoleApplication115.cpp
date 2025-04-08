#include <iostream>
#include <cctype>
#include <string>
#include <cstring>
using namespace std;

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
#define EOF_TOKEN -1

#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
string input = "x=(t+3-w)";
int currentIndex = 0;

void addChar();
void getChar();
void getNonBlank();
int lex();
int lookup(char ch);

int lookup(char ch) {
    switch (ch) {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;
        break;
    case '=':
        addChar();
        nextToken = ASSIGN_OP;
        break;
    default:
        addChar();
        nextToken = UNKNOWN;
        break;
    }
    return nextToken;
}

void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = '\0';
    }
    else {
        cout << "Error - lexeme is too long" << endl;
    }
}

void getChar() {
    if (currentIndex < input.length()) {
        nextChar = input[currentIndex++];
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else {
        charClass = EOF_TOKEN;
    }
}

void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

int lex() {
    lexLen = 0;
    getNonBlank();

    switch (charClass) {
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;

    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;

    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;

    case EOF_TOKEN:
        nextToken = EOF_TOKEN;
        strcpy(lexeme, "EOF");
        break;
    }

    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
    return nextToken;
}

int main() {
    cout << "Processing the expression: " << input << endl;
    currentIndex = 0;
    getChar();

    do {
        lex();
    } while (nextToken != EOF_TOKEN);

    return 0;
}
