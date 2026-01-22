/*===============================================
*   文件名称：ifstream.cpp
*   创 建 者：Autumnker
*   创建日期：2026年01月21日
*   描    述：
================================================*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string FILE_NAME = R"(src/test.txt)";

int main(int argc, char const* argv[])
{
    ifstream fin;
    fin.open(FILE_NAME);

    if (!fin.is_open()) {
        cerr << FILE_NAME << "打开失败" << endl;
        return EXIT_FAILURE;
    }

    string buffer;
    /**
     * 注意：
     * 1. fin >> buffer 会跳过空白字符(空格,换行,制表符符等),因为 operator>> 默认以空白符作为分隔符
     * 2. getline(fin,buffer) 会读取空白符但是会丢弃它,所以需要手动补充换行符
     */
    //  while (fin >> buffer) {
    //      cout << buffer << endl;
    //  }

    while (getline(fin, buffer)) {
        cout << buffer << endl;
    }

    fin.close();

    return 0;
}
