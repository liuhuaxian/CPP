#include <iostream>
using namespace std;
class A{
public:
    A() {cout << "A()" <<endl;}
    ~A() {cout << "Out A!" << endl;}
    virtual void Do(){cout << "Do A!" << endl;}
};
class B: public A{
public:
    B() {cout << "B()" <<endl;}
    ~B(){cout << "Out B" << endl;}
    void Do(){cout << "Do B" << endl;}
};
int main(){
    B*p1 = new B();
    p1->Do();
    delete p1;
    cout << endl;
    A *p2 = new B(); //父子兼容性原则 向上造型
    p2->Do();//多态性 函数加virtual就调用指针指向的实际内存空间里的东西
    delete p2;//p2->析构函数不加virtual,就取p2指针自己的类型(A)类里的东西

    return 0;
}
/*A()
 * B()
 * Do B
 * Out B
 * Out A!
 *
 * A()
 * B()
 * Do B
 * Out A!
 */
