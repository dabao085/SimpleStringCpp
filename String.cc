// Author : Chengx
// Date: 2019-11-18

#include "String.h"
#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;

allocator<char> String::alloc_;

void swap(String& lhs, String& rhs)
{
    // cout << "swap()..." << lhs << " -> " << rhs << endl;
    using std::swap;
    swap(lhs.data_, rhs.data_);
    swap(lhs.end_, rhs.end_);
    swap(lhs.size_, rhs.size_);
    swap(lhs.capacity_, rhs.capacity_);
}

String::String(const char* str)
{
    size_t sz = strlen(str);
    auto a = alloc_n_copy(str, sz);
    data_ = a.first;
    end_ = a.second;
    size_ = capacity_ = sz;
}

String::String(const String& str)
{
    auto a = alloc_n_copy(str.data_, str.size_, str.capacity_);
    data_ = a.first;
    end_ = a.second;
    size_ = str.size_;
    capacity_ = str.capacity_;
}

String::String(String&& str) noexcept
{
    // cout << "move String::String" << endl;
    data_ = str.data_;
    end_ = str.end_;
    size_ = str.size_;
    capacity_ = str.capacity_;
    str.data_ = str.end_ = nullptr;
    str.size_ = str.capacity_ = 0;  // 这一句加不加没有影响
}

// swap and copy
String& String::operator=(const String& str)
{
    String tmp(str);
    // cout << "operator=";
    swap(*this, tmp);
    return *this;
}

String& String::operator=(String&& str) noexcept
{
    // cout << "move String::operator=" << endl;
    data_ = str.data_;
    end_ = str.end_;
    size_ = str.size_;
    capacity_ = str.capacity_;
    str.data_ = str.end_ = nullptr;
    str.size_ = str.capacity_ = 0;

    return *this;
}

String::~String()
{
    free();
}

    // capacity.
void String::resize(size_t n, char c)
{
    if(n <= size())
    {
        // 方案1. destroy掉多余的空间, 但是无法deallocate。
        auto capacity_end = data_ + capacity_;
        for(; capacity_end != data_ + n;)
        {
            alloc_.destroy(--capacity_end);
        }
        size_ = capacity_ = n;
        end_ = data_ + size_;

        // 方案2. 复制一份，并destroy和deallocate掉以前的空间，性能较差，但空间上较优。
        // auto data = alloc_n_copy(data_, n);
        // free();
        // data_ = data.first;
        // end_ = data.second;
        // size_ = end_ - data_;
    }
    else
    {
        if(n <= capacity_)  // 未超过capacity, 不用申请新的空间
        {
            uninitialized_fill_n(end_, n - size_, c);
            end_ = data_ + n;
            size_ = n;
        }
        else
        {
            auto dataStart = alloc_.allocate(n);
            auto dataEnd = uninitialized_copy_n(data_, size_, dataStart);
            uninitialized_fill_n(dataEnd, n - size_, c);
            free();
            data_ = dataStart;
            end_ = dataStart + n;
            size_ = capacity_ = n;
        }
    }
}

void String::clear()
{
    free();
}

void String::reserve(size_t n)
{
    // 方案1. 不释放空间，只是修改capacity_大小。
    if(size_ <= n && n <= capacity_)
    {
        capacity_ = n;
    }
    else if( n < size_)
    {
        capacity_ = size_;
    }
    else    // size > capacity_
    {
        auto data = alloc_n_copy(data_, size_, capacity_);
        free(); // 释放之前的空间
        data_ = data.first;
        end_ = data.second;
        size_ = end_ - data_;
        capacity_ = n;
    }
    // 方案2. 释放空间，性能略差。
}

char& String::operator[](size_t index)
{
    if(check(index))
    {
        return *(data_ + index);
    }
    else
    {
        throw out_of_range("index out of range");
    }
}

String String::operator+(const String& str)
{
    String retstr;
    size_t size = size_ + str.size_;
    // cout << __LINE__ << " allocate size:" << size << endl;
    auto databegin = alloc_.allocate(size);
    auto dataend1 = uninitialized_copy(data_, end_, databegin);
    auto dataend2 = uninitialized_copy(str.data_, str.end_, dataend1);

    retstr.data_ = databegin;
    retstr.end_ = dataend2;
    retstr.size_ = retstr.capacity_ = size;

    return retstr;
}

String& String::operator+=(const String& str)
{
    *this = *this + str;
    return *this;
}

bool String::operator<(const String& str) const
{
    if(strcmp(this->data_, str.data_) <= 0)
    {
        // cout << this->data_ << " <= " << str.data_ << endl;
        return true;
    }
    else
    {
        // cout << this->data_ << " > " << str.data_ << endl;
        return false;
    }
}

pair<char*, char*> String::alloc_n_copy(const char* start, size_t size, size_t capacity)
{
    // cout << __LINE__ << " allocate size: " << size << endl;
    size_t realCapacity = capacity == 0 ? size : capacity;
    auto dataStart = alloc_.allocate(realCapacity);
    auto dataEnd = uninitialized_copy_n(start, size, dataStart);
    return {dataStart, dataEnd};
}

void String::free()
{
    if(data_ != nullptr && end_ != nullptr)
    {
        // cout << "free str: " << data_ << " size: " << size_ << endl;
        for_each(data_, end_, [](char &ch){ alloc_.destroy(&ch); });
        alloc_.deallocate(data_, capacity_);

        data_ = nullptr;
        end_ = nullptr;
        size_ = capacity_ = 0;
    }
}

bool String::check(size_t index)
{
    if(index >= size_)
    {
        return false;
    }
    else
    {
        return true;
    }
}

ostream& operator<<(ostream& os, const String& str)
{
    // os << str.begin();
    for(size_t i = 0; i != str.size(); ++i)
    {
        os << *(str.begin() + i);
    }
    return os;
}