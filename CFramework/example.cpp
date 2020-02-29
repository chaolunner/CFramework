#include "example.hpp"

void Example::Test1()
{
    int a = 10; // int是值类型，所以入栈。
    int *p = NULL; // 声明变量为指针变量，初值为0。
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
