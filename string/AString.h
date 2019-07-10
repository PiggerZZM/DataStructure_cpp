#ifndef ASTRING_H
#define ASTRING_H
// 程序4.13 顺序串的类定义
#include <cstring>
#include <iostream>
using namespace std;

const int defaultSize = 128;
class AString
{
private:
    char *ch;
    int curLength; // 不包括\0
    int maxSize;   // 不包括\0
public:
    AString(int sz = defaultSize);
    AString(const char *init);
    AString(const AString &ob);
    ~AString() { delete[] ch; }
    int Length() const { return curLength; }
    AString operator()(int pos, int len); // 取出从pos所指位置开始连续取len个字符组成的子串
    int operator==(AString &ob) const
    {
        return strcmp(ch, ob.ch) == 0;
    }
    int operator!=(AString &ob) const
    {
        return strcmp(ch, ob.ch) != 0;
    }
    int operator!() const
    {
        return curLength == 0;
    }
    AString &operator=(const AString &ob);
    AString &operator+=(const AString &ob);
    char operator[](int i);
    int Find(AString &pat) const;
    void replace(AString &tar, AString &rep);
};

AString::AString(int sz) : maxSize(sz)
{
    ch = new char[maxSize + 1];
    curLength = 0;
    ch[0] = '\0';
}

AString::AString(const char *init)
{
    int len = strlen(init);
    maxSize = (len > defaultSize) ? len : defaultSize;
    ch = new char[maxSize + 1];
    curLength = len;
    strcpy(ch, init);
}

AString::AString(const AString &ob)
{
    maxSize = ob.maxSize;
    ch = new char[maxSize + 1];
    curLength = strlen(ob.ch);
    strcpy(ch, ob.ch);
}

AString AString::operator()(int pos, int len)
{
    AString temp;
    if (pos < 0 || pos + len - 1 >= maxSize || len < 0)
    {
        temp.curLength = 0;
        temp.ch[0] = '\0';
    }
    else
    {
        if (pos + len - 1 >= curLength)
            len = curLength - pos;
        temp.curLength = len;
        for (int i = 0, j = pos; i < len; i++, j++)
            temp.ch[i] = ch[j];
        temp.ch[len] = '\0';
    }
    return temp;
}

AString &AString::operator=(const AString &ob)
{
    if (&ob != this)
    {
        delete[] ch;
        ch = new char[ob.maxSize + 1];
        maxSize = ob.maxSize;
        curLength = ob.curLength;
        strcpy(ch, ob.ch);
    }
    return *this;
}

AString &AString::operator+=(const AString &ob)
{
    char *temp = ch;
    int n = curLength + ob.curLength;
    int m = (maxSize >= n) ? maxSize : n;
    ch = new char[m];
    maxSize = m;
    curLength = n;
    strcpy(ch, temp);
    strcat(ch, ob.ch);
    delete[] temp;
    return *this;
}

char AString::operator[](int i)
{
    if (i < 0 || i >= curLength)
    {
        cout << "字符串下标越界！" << endl;
        exit(1);
    }
    return ch[i];
}

int AString::Find(AString &pat) const
{
    int i, j;
    for (i = 0; i <= curLength - pat.curLength; i++)
    {
        for (j = 0; j < pat.curLength; j++)
        {
            if (ch[i + j] != pat.ch[j])
                break;
        }
        if (j == pat.curLength)
            return i;
    }
    return -1;
}

void AString::replace(AString &tar, AString &rep)
{
    // 用子串v替换掉字符串s中所有子串t
    AString temp;
    int rep_len = rep.curLength;
    int tar_len = tar.curLength;
    int diff = rep_len - tar_len;
    int pos = Find(tar);
    if (pos > 0)
    {
        while (pos <= curLength - tar_len)
        {
            if (diff < 0) // 先腾出位置
            {
                for (int i = pos + tar_len; i <= curLength; i++)
                    ch[i + diff] = ch[i];
            }
            else if (diff > 0)
            {
                for (int i = curLength; i >= pos + tar_len; i--)
                    ch[i + diff] = ch[i];
            }
            int j;
            for (j = 0; j < rep_len; j++) // 替换
                ch[pos++] = rep[j];
            curLength += diff;
            temp = (*this)(pos, curLength - pos);
            if (temp.Find(tar) > 0)
                pos += temp.Find(tar);
            else
                break;
        }
    }
}

#endif