#include <stdio.h>
void static_cast_demo(){
    int i = 0x12345;
    char c = 'c';
    int* pi = &i; 
    char* pc = &c; 
    c = static_cast<char>(i);//用于
    //pc = static_cast<char*>(pi);//error static_cast 用于基本类型之间的转换,不能用于基本类型指针间的转换
}
void const_cast_demo(){
    const int& j = 1;
    int& k = const_cast<int&>(j);
    const int x = 2;
    int& y = const_cast<int&>(x);
    //int z = const_cast<int>(x);
    k = 5;
    printf("k = %d\n", k);//5
    printf("j = %d\n", j);//5
    y = 8;
    printf("x = %d\n", x);//2
    printf("y = %d\n", y);//8
    printf("&x = %p\n", &x);
    printf("&y = %p\n", &y);
}
void reinterpret_cast_demo(){
    int i = 0;
    char c = 'c';
    int* pi = &i; 
    char* pc = &c; 
    pc = reinterpret_cast<char*>(pi);
    pi = reinterpret_cast<int*>(pc);
    pi = reinterpret_cast<int*>(i);
 //   c = reinterpret_cast<char>(i); 
}
void dynamic_cast_demo(){
    int i = 0;
    int* pi = &i; 
 //   char* pc = dynamic_cast<char*>(pi);
}
int main(){
    static_cast_demo();
    const_cast_demo();
    reinterpret_cast_demo();
    dynamic_cast_demo();
    return 0;
}
/*
k = 5
j = 5
x = 2
y = 8
&x = 0x7ffe26db5dc0
&y = 0x7ffe26db5dc0
*/
