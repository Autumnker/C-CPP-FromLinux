/*===============================================
*   文件名称：bin_ofstream.cpp
*   创 建 者：Autumnker
*   创建日期：2026年01月22日
*   描    述：
================================================*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string FILE_NAME = R"(src/bin_test.bin)";

typedef struct {
    int index;
    char name[32];
    // string name;
    float grade;
}Node;

int main(int argc, char const* argv[])
{
    // 创建文件输出流对象
    ofstream fout;

    // 以二进制写入形式打开文件
    fout.open(FILE_NAME, ios::binary | ios::out);
    if (!fout.is_open()) {
        cerr << FILE_NAME << "打开失败" << endl;
        return EXIT_FAILURE;
    }

    Node node1 = { 1,"章子怡",99.0 };
    Node node2 = { 2,"阿库娅",99.2 };

    // 写入数据
    fout.write((const char*)&node1, sizeof(Node));
    fout.write((const char*)&node2, sizeof(Node));

    // 关闭文件流
    fout.close();

    return 0;
}
