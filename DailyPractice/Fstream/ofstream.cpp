/*===============================================
*   文件名称：ofstream.cpp
*   创 建 者：Autumnker
*   创建日期：2026年01月21日
*   描    述：
================================================*/
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string FILE_NAME = R"(./src/test.txt)";

int main(int argc, char const* argv[])
{
    // 创建文件输出流并打开/创建文件
    ofstream fout;

    // open(文件路径,打开模式)
    /**
     * 打开模式分为:
     * ios::app	    追加模式。所有写入都追加到文件末尾。
     * ios::ate	    文件打开后定位到文件末尾。
     * ios::in	    打开文件用于读取。
     * ios::out	    打开文件用于写入。
     * ios::trunc   如果该文件已经存在，其内容将在打开文件之前被截断，即把文件长度设为 0。
     */
    fout.open(FILE_NAME, ios::out);

    if (!fout.is_open()) {
        cerr << FILE_NAME << "打开失败" << endl;
        return EXIT_FAILURE;
    }

    // 写入数据
    string src = "123456789\tABC\tdef\t！@#$!\t123456789\n\n";
    fout << src;

    // 关闭输出流
    fout.close();

    return 0;
}
