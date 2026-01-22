/*===============================================
*   文件名称：bin_ifstream.cpp
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
    // 创建文件输入流对象
    ifstream fin;

    // 以二进制读取形式打开文件
    fin.open(FILE_NAME, ios::binary | ios::in);
    if (!fin.is_open()) {
        cerr << FILE_NAME << "打开失败" << endl;
        return EXIT_FAILURE;
    }

    Node node;

    // 读取数据
    while (fin.read((char*)&node, sizeof(Node))) {
        cout << "index : " << node.index << ";name : " << node.name << ";index : " << node.grade << endl;
    }

    // 关闭文件流
    fin.close();

    return 0;
}
