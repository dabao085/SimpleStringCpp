// Author : Chengx
// Date: 2019-11-18

#ifndef _MY_STRING_H_
#define _MY_STRING_H_

#include <stdio.h>
#include <memory>

class String
{
friend void swap(String&, String&);    
public:
    String():data_(nullptr), end_(nullptr), size_(0){}
    String(const char*);
    String(const String&);
    String(String&&) noexcept;              // Must have noexcept.
    String& operator=(const String&);
    String& operator=(String&&) noexcept;   // Must have noexcept.
    ~String();

    // capacity
    size_t size() const { return size_; }
    size_t length() const { return size_; }
    void resize(size_t n, char c = ' ');
    void clear();
    bool empty() const { return data_ == end_; }

    const char* begin() const { return data_; }
    char* begin() { return data_; }
    const char* end() const { return end_; }
    char* end() { return end_; }

    char& operator[](size_t);
    String operator+(const String&);
    String& operator+=(const String&);
    bool operator<(const String&) const;    // 必须要加最后的const. Must have const.

private:
    std::pair<char*, char*> alloc_n_copy(const char* start, size_t size);
    void free();
    bool check(size_t);
private:
    static std::allocator<char> alloc_;
    char *data_;
    char *end_;
    size_t size_;
};

void swap(String&, String&);    
std::ostream& operator<<(std::ostream&, const String&); // 不可做为成员函数

#endif