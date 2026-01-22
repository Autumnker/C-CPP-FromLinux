/*===============================================
*   文件名称：eof_good_fail_bad.cpp
*   创 建 者：Autumnker
*   创建日期：2026年01月22日
*   描    述：eof、good、fail、bad
================================================*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string FILE_NAME = R"(src/test.txt)";

/**
 * 一、
 * 标志位	含义	                                        触发条件
 * goodbit	流处于正常状态，无错误。	                     初始状态，或调用 clear() 后重置。
 * eofbit	已到达文件末尾（End Of File）。	                 读取操作尝试越过文件末尾时（如 getline 或 >> 读到文件结尾）。
 * failbit	流操作失败，但流未完全损坏（可恢复）。	           格式错误（如用 >> 读取非数字到 int）、文件打开失败、seekg 越界等。
 * badbit	流严重错误，无法继续操作（如文件损坏或硬件故障）。	非法操作（如对未打开的文件读写）、缓冲区错误等。
 *
 * 二、
 * 方法	            作用
 * good()	        返回 true 当且仅当 所有错误标志未设置（goodbit 状态）。
 * eof()	        返回 true 如果设置了 eofbit（文件读完）。
 * fail()	        返回 true 如果设置了 failbit 或 badbit（操作失败）。
 * bad()	        返回 true 仅当设置了 badbit（严重错误）。
 * operator bool()	等价于 !fail()，可用于条件判断（如 if (fs) {...}）。
 *
 * 三、
 * 状态标志的组合关系
 * good() 为 true：eofbit、failbit、badbit 均未设置。
 * eof()  为 true：eofbit 被设置，但 failbit 和 badbit 可能未设置。
 * fail() 为 true：failbit 或 badbit 被设置（包括 eofbit + failbit）。
 * bad()  为 true：仅 badbit 被设置（通常不可恢复）。
 */

int main(int argc, char const* argv[])
{
    // 打开文件
    fstream fs;
    fs.open(FILE_NAME, ios::in | ios::out);
    if (!fs.is_open()) {
        cerr << FILE_NAME << "打开失败" << endl;
        return EXIT_FAILURE;
    }

    string buf;
    while (getline(fs, buf)) {
        cout << buf << endl;
    }   // 此时,eofbit为1

    cout << "before clear fs.eofbit = " << fs.eof() << endl;
    fs.clear(); // 此时, eofbit 为 0
    cout << "after clear fs.eofbit = " << fs.eof() << endl;

    // ……

    fs.close();

    return 0;
}
