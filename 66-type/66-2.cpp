1 #include <iostream>
  2 #include <string>
  3 #include <typeinfo>
  4 using namespace std;
  5 class Base{
  6 public:
  7     virtual ~Base(){}
  8 };
  9 class Derived : public Base{
 10 public:
 11     void printf(){
 12         cout << "I'm a Derived." << endl;
 13     }
 14 };
 15 
 16 void test(Base* b){
 17         const type_info& tb = typeid(*b);
 18         cout << tb.name() << endl;
 19 }
 20 
 21 int main(int argc, char *argv[])
 22 {
 23     int i = 0;
 24     const type_info& tiv = typeid(i);//静态类型信息
 25     const type_info& tii = typeid(int);//静态类型信息
 26     cout << (tiv == tii) << endl;//1
 27 
 28     Base b;
 29     Derived d;
 30 
 31     test(&b);
 32     test(&d);
 33     return 0;
 34 }
 35 /*注释掉第7行的打印信息
 36  * 1
 37  * 4Base 没有虚函数表,返回的是静态类型信息
 38  * 4Base*/
 39 
 40 /*解开第7行的打印信息
 41  * 1 
 42  * 4Base
 43  * 7Derived  //17行typeid检查b指针指向的对象是否有虚函数表，有(返回动态类型信息)
 44  */
