/*===============================================
*   文件名称：seek.cpp
*   创 建 者：Autumnker
*   创建日期：2026年01月22日
*   描    述：seekp、seekg
================================================*/
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;

string FILE_NAME = R"(src/test.txt)";

/**
 * 输入流 (seekg)
 * istream& seekg(streampos pos);               // 绝对位置
 * istream& seekg(streamoff offset, ios_base::seekdir dir);  // 相对位置
 *
 * 输出流 (seekp)
 * ostream& seekp(streampos pos);               // 绝对位置
 * ostream& seekp(streamoff offset, ios_base::seekdir dir);  // 相对位置
 *
 * 参数说明：
 * pos：绝对位置（从文件开头计算的字节偏移量）。
 * offset：相对位置的偏移量（可正可负）。
 * dir：基准位置，取值为：
 *  - ios::beg（文件开头）
 *  - ios::cur（当前位置）
 *  - ios::end（文件末尾）
 */

int main(int argc, char const* argv[])
{
    // 清空文件
    ofstream fout(FILE_NAME, ios::trunc);
    fout.close();

    // 打开文件
    fstream fs;
    fs.open(FILE_NAME, ios::in | ios::out);
    if (!fs.is_open()) {
        cerr << FILE_NAME << "打开失败" << endl;
        return EXIT_FAILURE;
    }

    // 向文件中写入初始值
    string buf = "abc\ndef\nghi\n";
    fs.write(buf.c_str(), buf.length());
    fs.flush();
    fs.seekp(0, ios::beg);
    while (getline(fs, buf)) {
        cout << buf << endl;
    }
    fs.clear();                                   // 清除文件流的eofbit标志位

    sleep(3);

    // 移动文件位置指针并读取文件位置指针偏移量
    /**ifstream seekg */
    fs.seekg(0, ios::beg);
    cout << "fs.tell = " << fs.tellg() << endl;   // 文件打开时的输入流位置指针

    fs >> buf;
    cout << "buf = " << buf << endl;
    cout << "fs.tell = " << fs.tellg() << endl;   // 读取到空白符时的输入流位置指针

    fs.seekg(4, ios::cur);                          // 在当前位置向后移动四个字节
    fs >> buf;                                      // 读取到空白符

    cout << "buf = " << buf << endl;
    cout << "fs.tell = " << fs.tellg() << endl;

    fs.seekg(-8, ios::end);                         // 输入流位置指针从文件末尾向前偏移8个字节
    fs >> buf;
    cout << "buf = " << buf << endl;
    cout << "fs.tell = " << fs.tellg() << endl;

    cout << "=====================================" << endl;
    /**ofstream seekp */
    fs.seekp(0, ios::beg);
    cout << "fs.tell = " << fs.tellp() << endl;

    fs.seekp(-4, ios::end);
    fs << "123" << endl;
    cout << "fs.tell = " << fs.tellp() << endl;

    fs << "456" << endl;
    cout << "fs.tell = " << fs.tellp() << endl;

    fs.close();

    return 0;
}

