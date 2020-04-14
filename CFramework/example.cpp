#include <string.h>
#include <stdlib.h>
#include <cctype>
#include "example.h"

// 指针铁律
void Example::Test1()
{
    int a = 10;                      // int是值类型，所以入栈。
    int *p = NULL;                   // 声明变量为指针变量，在C中，NULL表示的是指向0的指针，而在C++中，NULL就直接跟0一样了。
    p = &a;                          // 将a变量的内存地址给指针变量p。
    *p = 20;                         // *p放在等号左边，即修改a变量标示的内存空间的值。
    printf("a:%d, &a:%d \n", a, &a); // 检查是否可以通过*p间接的修改a变量标示的内存空间的值。
    int b = 0;                       // int是值类型，所以入栈。
    b = *p;                          // *p放在等号右边，即取得a变量标示的内存空间的值来修改b变量标示的内存空间。
    printf("b:%d, &b:%d \n", b, &b); // 输出b变量标示的内存空间的值，根据输出的a和b的内存地址的不同，该操作只是让b变量标示的内存空间改变了。

    int c[10]; // 分配40个字节的内存。
    // c和&c（地址值c）结果一样，但是c+1和&c+1的结果不一样？
    // 这是因为c和&c所代表的数据类型不一样，
    // c 代表数组首元素的地址，&c 代表整个数组的地址，
    // 而在c语言中，加减法运算对于地址的操作和对于值的操作是不同的，
    // 当两边的操作数一个是地址，另一个是整数时，这个整数值先乘以该地址的数据类型的大小（如sizeof(int)），然后再和地址的值（相加/相减）。
    // 当两边的操作数都是地址时，则这两个地址的数据类型必须一致（如都是int 类型），否则无法通过编译。运算的结果为地址值的（和/差），再除以该地址的数据类型的大小（如sizeof(int)）。
    printf("c:%d,c+1:%d,&c:%d,&c+1:%d \n", c, c + 1, &c, &c + 1);
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
    for (i = 0; *(from + i) != '\0'; i++)
    {
        *(to + i) = *(from + i);
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
    while ((*to++ = *from++) != '\0')
    {
    }
}

void Example::copy_str4(char *from, char *to)
{
    while ((*to++ = *from++))
    {
    }
}

// char *p = "abcd1234abcd5678abcd9012abcd"；
// 求字符串中 “abcd” 出现的次数
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
    while (p = strstr(p, needle)) // 在字符串 haystack 中查找第一次出现字符串 needle（不包含空结束字符）的位置。
    {
        tmpCount++;
        p += strlen(needle);
    }
    *count = tmpCount;
    return result;
}

// 两头堵模型
void Example::Test4()
{
    char *p = "     abcdefg     ";
    int count = 0;
    getCountWithoutSpace(p, &count);
    printf("count: %d \n", count);
    char buf[128];
    strcpy(buf, p);
    trimSpace(buf); // 注意，不能直接使用p指针所指向的内存空间，因为该指针指向的内存空间在常量区，不能被修改。
    printf("trim space: %s \n", buf);
}

// 求非空格的字符串长度
void Example::getCountWithoutSpace(char *str, int *count)
{
    int i = 0;
    int j = strlen(str) - 1;
    while (isspace(str[i]) && str[i] != '\0')
    {
        i++;
    }
    while (isspace(str[j]) && str[j] != '\0')
    {
        j--;
    }

    *count = j - i + 1;
}

// 去除字符串前后的空格
// str所指向的内存空间，可以被修改才行
void Example::trimSpace(char *str)
{
    if (str == NULL)
    {
        return;
    }
    int i = 0;
    int j = strlen(str) - 1;
    while (isspace(str[i]) && str[i] != '\0')
    {
        i++;
    }
    while (isspace(str[j]) && str[j] != '\0')
    {
        j--;
    }
    int ncount = j - i + 1;
    strncpy(str, str + i, ncount);
    str[ncount] = '\0';
}

// 字符串反转
void Example::Test5()
{
    char buf1[] = "abcdefg";
    char buf2[8] = {0};
    inverse(buf1);
    inverse(buf1, buf2);
    printf("inverse: %s, %s \n", buf1, buf2);
}

// 通过指针的方式实现字符串反转
void Example::inverse(char *str)
{
    int length = strlen(str);
    char *p1 = str;
    char *p2 = str + length - 1;

    while (p1 < p2)
    {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }
}

// 通过递归的方式实现字符串反转
void Example::inverse(char *str1, char *str2)
{
    if (str1 == NULL || str2 == NULL) // 递归结束的异常条件
    {
        return;
    }
    if (*str1 == '\0') // 递归结束的条件
    {
        return;
    }

    inverse(str1 + 1, str2);

    strncat(str2, str1, 1); // 把 str1 所指向的字符串追加到 str2 所指向的字符串的结尾。
}

// 二级指针做输入
// 第一种内存模型
void Example::Test6()
{
    // 数组 数组中的每一个元素是指针 指针数组
    char *myArray[] = {"b", "a", "c", "e", "d"};
    int num = sizeof(myArray) / sizeof(myArray[0]);

    printf("第一种内存模型排序之前\n");
    for (int i = 0; i < num; i++)
    {
        printf("%s \n", myArray[i]);
    }

    sortStringArray(myArray, num);

    printf("第一种内存模型排序之后\n");
    printStringArray(myArray, num);
}

void Example::printStringArray(char **strArray, int num)
{
    for (int i = 0; i < num; i++)
    {
        printf("%s \n", *(strArray + i));
    }
}

void Example::sortStringArray(char **strArray, int num)
{
    char *tmp = NULL;
    for (int i = 0; i < num; i++)
    {
        for (int j = i; j < num; j++)
        {
            if (strcmp(strArray[i], strArray[j]) > 0)
            {
                tmp = strArray[i]; // 注意，交换的是指针变量的值，即改变指针的指向。
                strArray[i] = strArray[j];
                strArray[j] = tmp;
            }
        }
    }
}

// 二级指针做输入
// 第二种内存模型
void Example::Test7()
{
    int i = 0;
    int num = 5;
    char tmpBuf[30];
    char myArray[10][30] = {"b", "a", "c", "e", "d"}; // 编译器只关心，数组有10行，每行30列。 为什么？ myArray+1 多维数组名的本质，即步长=30。

    printf("第二种内存模型排序之前\n");
    for (int i = 0; i < num; i++)
    {
        printf("%s \n", myArray[i]);
    }

    for (int i = 0; i < num; i++)
    {
        for (int j = i + 1; j < num; j++)
        {
            if (strcmp(myArray[i], myArray[j]) > 0)
            {
                strcpy(tmpBuf, myArray[i]); // 注意，交换的是内存块。
                strcpy(myArray[i], myArray[j]);
                strcpy(myArray[j], tmpBuf);
            }
        }
    }

    printf("第二种内存模型排序之后\n");
    for (int i = 0; i < num; i++)
    {
        printf("%s \n", myArray[i]);
    }
}

// 二级指针做输入
// 第三种内存模型
void Example::Test8()
{
    int num = 5;
    char **p1 = NULL;
    char *tmp = NULL;
    char tmpBuf[100];
    getMem(&p1, num);

    printf("第三种内存模型排序之前\n");
    printStringArray(p1, num);

    // 排序交换指针
    sortStringArray(p1, num);

    printf("排序交换指针之后\n");
    for (int i = 0; i < num; i++)
    {
        printf("%s \n", p1[i]);
    }

    // 排序交换内存
    for (int i = 0; i < num; i++)
    {
        for (int j = i + 1; j < num; j++)
        {
            if (strcmp(p1[i], p1[j]) < 0)
            {
                strcpy(tmpBuf, p1[i]); // 注意，交换的是内存块。
                strcpy(p1[i], p1[j]);
                strcpy(p1[j], tmpBuf);
            }
        }
    }

    printf("排序交换内存之后\n");
    printStringArray(p1, num);

    // 释放内存
    getMemFree(&p1, num);
}

void Example::getMem(char ***p1, int num)
{
    char **tmp = NULL;
    tmp = (char **)malloc(sizeof(char *) * num);

    for (int i = 0; i < num; i++)
    {
        tmp[i] = (char *)malloc(sizeof(char) * 100); // char buf[100];
        sprintf(tmp[i], "%d", num - i);
    }

    *p1 = tmp;
}

void Example::getMemFree(char ***p1, int num)
{
    char **tmp = *p1;
    for (int i = 0; i < num; i++)
    {
        if (tmp[i] != NULL)
        {
            free(tmp[i]);
            tmp[i] = NULL;
        }
    }
    if (tmp != NULL)
    {
        free(tmp);
        *p1 = NULL; // 把实参赋值成NULL，避免野指针。
    }
}

// 定义数组指针变量的方法
void Example::Test9()
{
    char *myArray1[] = {"abc", "def", "ghi"}; // 指针数组

    // 数组指针，用一个指针来指向一个数组

    // 第一种方法：
    typedef int(MyArrayType)[5]; // 定义了一个数据类型， 数组数据类型
    MyArrayType myArray2;
    MyArrayType *pArray2; // 定义一个指针变量，这个指针变量 指向一个数组

    pArray2 = &myArray2;

    // 第二种方法：
    typedef int(*PArrayType)[5]; // 定义一个数组指针类型
    PArrayType pArray3;          // 告诉编译器，给我分配一个指针变量

    int myArray3[5];
    pArray3 = &myArray3;

    // 第三种方法：
    int(*pArray4)[5]; // 直接定义一个指向数组的，数组指针变量

    int a[3][5];
    int tmp = 1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            a[i][j] = tmp++;
        }
    }

    printf("多维数组名的本质：指向数组的指针变量\n");
    // 比如二维数组名的本质，就是指向一维数组的指针变量
    pArray4 = a;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%d ", pArray4[i][j]);
        }
    }
    printf("\n");
    printf("a : %d, a + 1 : %d \n", a, a + 1);     // a + 1的步长，是20个字节，4 x 5 即一维数组的长度
    printf("&a : %d, &a + 1 : %d \n", &a, &a + 1); // &a + 1的步长， 是60个字节， 3 x 20 即二维数组的长度
    // a[i][j] == *( *(a + i) + j )
}

// 定义一个结构体类型
// 类型的重定义 typedef struct 类型名 { 成员表列 } 别名;
typedef struct Student
{
    char name[64];
    int age;
    int id;
} Student;

// 结构体
void Example::Test10()
{
    struct Student s1;            // 告诉C编译器分配内存
    Student s2 = {"小明", 18, 1}; // 注意，在C中只有进行了类型重定义之后才可以这样写！
    printf("姓名：%s 年龄：%d 学号：%d \n", s2.name, s2.age, s2.id);
    // s2. 操作符是干什么？有没有操作内存？
    // . 寻址操作，计算name相对于s2变量的偏移量,在cpu中进行计算
    // 没有操作内存

    Student *p = NULL;
    p = &s2;
    p->age = 21; // 通过指针的方式操作内存空间
    // -> 寻址操作，计算age相对于s2变量的偏移量,在cpu中进行计算
    // 没有操作内存
    printf("姓名：%s 年龄：%d 学号：%d \n", p->name, p->age, p->id);
}