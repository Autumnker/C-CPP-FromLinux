/*===============================================
*   文件名称：fstream.cpp
*   创 建 者：Autumnker
*   创建日期：2026年01月22日
*   描    述：
================================================*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define READ_MODE 1

string FILE_NAME_TEXT = "src/test.txt";
string FILE_NAME_BINARY = "src/bin_test.bin";

typedef struct {
    int index;
    char name[32];
    // string name;
    float grade;
}Node;

int main(int argc, char const* argv[])
{
    // 创建文件流对象
    fstream t_fs;
    fstream b_fs;

    // 打开文件(fstream 对象用默认值打开文件时,不会截断原有内容)
    t_fs.open(FILE_NAME_TEXT, ios::in | ios::out);
    if (!t_fs.is_open()) {
        cerr << FILE_NAME_TEXT << "打开失败" << endl;
        return EXIT_FAILURE;
    }
    b_fs.open(FILE_NAME_BINARY, ios::binary | ios::in | ios::out);
    if (!b_fs.is_open()) {
        cerr << FILE_NAME_BINARY << "打开失败" << endl;
        t_fs.close();
        return EXIT_FAILURE;
    }

#if READ_MODE

    // 读取文件内容
    // char buff[1024];
    string buff;
    while (getline(t_fs, buff)) {
        cout << buff << endl;
    }

    Node node;
    while (b_fs.read((char*)&node, sizeof(Node))) {
        cout << "index : " << node.index << "; name : " << node.name << "; grade : " << node.grade << endl;
    }

#else

    // 向文件中写入数据
    string src = "===============123456789\tABC\tdef\t！@#$!\t123456789\n\n=============";
    t_fs << src;

    Node node1 = { 1,"lynn",100.0 };
    Node node2 = { 2,"藤森理惠",99.9 };

    b_fs.write((const char*)&node1, sizeof(Node));
    b_fs.write((const char*)&node2, sizeof(Node));

#endif

    t_fs.close();
    b_fs.close();

    return 0;
}
