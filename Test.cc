#include "String.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
// #include <utility>
using namespace std;

void testMove(const String& str)
{
    cout << str << endl;
}

void testMove(String&& str)
{
    String tmp;
    tmp = std::move(str);
    cout << tmp << endl;
}

int main()
{
    // 测试构造
    String str1;
    cout << "str1: " << str1 << endl;
    String str2("Hi");
    cout << "str2: " << str2 << endl;
    String str3(str2);
    cout << "str3: " << str3 << endl;
    String str4(std::move(str3));
    cout << "str4: " << str4 << endl;
    // 此时str4仍可以访问，但不保证其正确性，所以在std::move后，最好不要访问被move的元素。

    // 测试赋值
    String str5 = str4;
    cout << "str5: " << str5 << endl;
    String str6 = std::move(str5);
    cout << "str6: " << str6 << endl;

    // 测试字符串操作
    String str7("hello ");
    String str8("world！");
    cout << "str7 + str8: " << str7 + str8 << endl;
    str7 += str8;
    cout << "str7 += str8, str7: " << str7 << endl;

    // 测试随机读取
    String str9("cheng");
    str9[0] = 'C';
    cout << "str9: " << str9 << endl;

    // 测试字符串排序
    String str10("nice");
    String str11("to");
    String str12("meet");
    String str13("you");

    vector<String> strvec{str10, str11, str12, str13};
    sort(strvec.begin(), strvec.end());
    cout << "print after sort..." << endl;
    for_each(strvec.begin(), strvec.end(), [](const String& str){ cout << str << endl;});

    return 0;
}