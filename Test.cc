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

void printInfo(const String& name, const String& str)
{
    cout << name << " : content: " << str << " : "<< str.size() << " : " << str.length() << " : " << str.capacity() << endl;
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

    String str14("Hello World!");
    str14.resize(5);
    cout << "After resize: " << str14 << endl;
    String str15("Hello");
    str15.resize(10, '-');
    cout << str15 << endl;
    String str16("Hello");
    str16.resize(10);
    cout << str16 << " : size: " << str16.size() << endl;

    str16.clear();
    cout << "After clear: " << str16 << " : size: " << str16.size() << endl;

    String str17("Hello");
    printInfo("str17", str17);
    str17.reserve(10);
    printInfo("str17", str17);
    str17.reserve(8);
    printInfo("str17", str17);

    String str18 = str17;
    printInfo("str18", str18);
    String str19 = str17 + str18;
    printInfo("str19", str19);

    return 0;
}