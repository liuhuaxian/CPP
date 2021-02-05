#include <iostream>
#include <string>
using namespace std;
class Base{
public:
    virtual string type(){
        return "Base";
    }   
};
class Derived:public Base{
public:
        string type(){
                return "Derived";    
        }   
void print(){
        cout << "I'm a Derived." << endl;
    }   
};
class Child:public Base{
public:
        string type(){
                return "Child";
        }   
};
void test(Base* b){ 
    /** 危险的转换方式 */
    if(b->type()=="Derived"){//if()中的函数不会调用
                Derived* d = static_cast<Derived*>(b);
                d->print();
        }   
        /*cout << dynamic_cast<Derived*>(b)<< endl;
 *      0
        I'm a Derived.
        0x7ffdd92349c0
        0
思考：dynamic_cast<Derived*>(b); 为什么不适用于这里呢？
dynamic_cast 可以判断是否转换成功，但无法识别指针实际指向的动态类型
*/
}
int main(){
        Base b;
        Derived d;
        Child c;
        test(&b);
        test(&d);
        test(&c);
		return 0;
}
		