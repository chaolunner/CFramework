#include <string.h>
#include "example.h"

// 指针铁律
void Example::Test1()
{
    int a = 10; // int是值类型，所以入栈。
    int *p = NULL; // 声明变量为指针变量，在C中，NULL表示的是指向0的指针，而在C++中，NULL就直接跟0一样了。
    p = &a; // 将a变量的内存地址给指针变量p。
    *p = 20; // *p放在等号左边，即修改a变量标示的内存空间的值。
    printf("a:%d，&a:%d \n", a, &a); // 检查是否可以通过*p间接的修改a变量标示的内存空间的值。
    int b = 0; // int是值类型，所以入栈。
    b = *p; // *p放在等号右边，即取得a变量标示的内存空间的值来修改b变量标示的内存空间。
    printf("b:%d，&b:%d \n", b, &b); // 输出b变量标示的内存空间的值，根据输出的a和b的内存地址的不同，该操作只是让b变量标示的内存空间改变了。

    int c[10]; // 分配40个字节的内存。
    // c和&c（地址值c）结果一样，但是c+1和&c+1的结果不一样？
    // 这是因为c和&c所代表的数据类型不一样，
    // c 代表数组首元素的地址，&c 代表整个数组的地址，
    // 而在c语言中，加减法运算对于地址的操作和对于值的操作是不同的，
    // 当两边的操作数一个是地址，另一个是整数时，这个整数值先乘以该地址的数据类型的大小（如sizeof(int)），然后再和地址的值（相加/相减）。
    // 当两边的操作数都是地址时，则这两个地址的数据类型必须一致（如都是int 类型），否则无法通过编译。运算的结果为地址值的（和/差），再除以该地址的数据类型的大小（如sizeof(int)）。
    printf("c:%d,c+1:%d,&c:%d,&c+1:%d \n", c, c+1, &c, &c+1);
}

// 字符串的基本操作
void Example::Test2()
{
    char a[] = "abcd"; // a表示数组的首元素指针（只读，即常量指针）。
    // 这样的设计是为了保证局部变量的内存的首地址的安全性，确保a指向的内存空间可以安全释放。
    // 所以你无法轻易的通过a=a+1来改变a的地址。
    char b[4] = "abc";
    printf("a len: %d \n", strlen(a)); // strlen(a)取的是字符串从开始到遇到第一个“\0”的长度，所以结果是4。
    printf("a size %d \n", sizeof(a)); // sizeof(a)取得的是字符串”abcd”占的总空间。”abcd”中，共有a b c d \0五个字符，所以结果为5。
    printf("b size %d \n", sizeof(b)); // b已经定义成了长度是4的数组，所以sizeof(b)一定等于4，而后面跟的字符串也只能小于4个字符，不然无法通过编译。
    
    // 字符串copy函数的技术推演，注意观察函数内部实现的变化。
    char c[5];
//    copy_str1(a, c);
//    copy_str2(a, c);
//    copy_str3(a, c);
    copy_str4(a, c);
    
    printf("c:%s \n", c);
}

void Example::copy_str1(char *from, char *to)
{
    int i = 0;
    for (i = 0; *(from+i) != '\0'; i++)
    {
        *(to+i) = *(from+i);
    }
    // '\0' 没有拷贝到c指向的内存空间中，所以下面这一步很重要。
    to[i] = '\0';
}

void Example::copy_str2(char *from, char *to)
{
    while ((*to = *from) != '\0')
    {
        from++;
        to++;
    }
}

void Example::copy_str3(char *from, char *to)
{
    while ((*to++ = *from++) != '\0') { }
}

void Example::copy_str4(char *from, char *to)
{
    while ((*to++ = *from++)) { }
}

// char *p = "abcd1234abcd5678abcd9012abcd"；
// 求字符串中 “abcd” 出现的次数。
void Example::Test3()
{
    char *p = "abcd1234abcd5678abcd9012abcd";
    char n[] = "abcd";
    int count = 0;
    
    getCount(p, n, &count);
    printf("count: %d \n", count);
}

int Example::getCount(char *haystack, char *needle, int *count)
{
    int result = 0;
    if (haystack == NULL || needle == NULL || count == NULL)
    {
        result = -1;
        return result;
    }
    char *p = haystack; // 不要轻易的改变形参的值。
    int tmpCount = 0;
    while(p = strstr(p, needle)) // 在字符串 haystack 中查找第一次出现字符串 needle（不包含空结束字符）的位置。
    {
        tmpCount++;
        p += strlen(needle);
    }
    *count = tmpCount;
    return result;
}
