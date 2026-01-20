/*===============================================
*   文件名称：ParenthesisMatching.cpp
*   创 建 者：Autumnker
*   创建日期：2026年01月20日
*   描    述：
================================================*/
#include <iostream>
#include<string>
#include<stack>
#include<unistd.h>
#include<string.h>

using namespace std;

bool ParenthesisMatching(const string& str) {
    stack<char> leftParenthesis;
    for (const char i : str) {
        if (i == '(' || i == '[' || i == '{') {
            leftParenthesis.push(i);
        }
        else if (i == ')' || i == ']' || i == '}') {
            if (leftParenthesis.empty()) {
                return false;
            }
            char topParentheses = leftParenthesis.top();
            leftParenthesis.pop();
            if (i == '(' && topParentheses != ')' ||
                i == '[' && topParentheses != ']' ||
                i == '{' && topParentheses != '}') {

                return false;
            }
        }
    }
    return leftParenthesis.empty();
}

int fileCheck(const string& path, string& text) {
    FILE* fp = fopen(path.c_str(), "r");
    if (fp == nullptr) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    int readNum = 0;
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    while ((readNum = fread(buffer, sizeof(char), sizeof(buffer), fp)) > 0) {
        buffer[readNum] = '\0';
        text += buffer;
        memset(buffer, 0, readNum);
    }

    if (ferror(fp)) {
        perror("fread failed");
        fclose(fp);
        return EXIT_FAILURE;
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

int main(int argc, char const* argv[])
{

    string text;
    fileCheck(argv[1], text);

    cout << text << endl;
    cout << "===========================================" << endl;

    cout << ParenthesisMatching(text) << endl;

    return 0;
}

