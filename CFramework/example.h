#ifndef example_h
#define example_h

#include <stdio.h>

class Example
{
public:
    void Test1();
    void Test2();
    void Test3();
    void Test4();
    void Test5();
    void Test6();
    void Test7();
    void Test8();

private:
    void copy_str1(char *from, char *to);
    void copy_str2(char *from, char *to);
    void copy_str3(char *from, char *to);
    void copy_str4(char *from, char *to);
    int getCount(char *haystack, char *needle, int *count);
    void getCountWithoutSpace(char *str, int *count);
    void trimSpace(char *str);
    void inverse(char *str);
    void inverse(char *str1, char *str2);
    void printStringArray(char **strArray, int num);
    void sortStringArray(char **strArray, int num);
    void getMem(char ***p1, int num);
    void getMemFree(char ***p1, int num);
};

#endif
