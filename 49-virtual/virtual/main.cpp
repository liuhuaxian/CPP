#include <iostream>
#include <string>
using namespace std;

class parent{
public:
    virtual void print(){//被virtual声明的函数为虚函数 函数重写必须多态实现
        cout << "I'm Parent." << endl;
    }

    virtual void func(){
        cout << "void func()" << endl;
    }
    virtual void func(int i){
        cout << "void func(int i) : " << i << endl;
    }
    virtual void func(int i, int j){
        cout << "void func(int i, int j) : " << "(" << i << ", " << j << ")" << endl;
     }
};

class child:public parent{

public:
    void print(){
        cout << "I'm child." << endl;
    }

    void func(int i,int j){
        cout << "void func(int i, int j) : " << i + j << endl;
    }
    void func(int i, int j, int k){
        cout << "void func(int i, int j, int k) : " << i + j + k << endl;
    }

};

void how_to_print(parent* p){
    p->print();//此处展现多态的行为 :)
}

void run(parent* p){
    p->func(1,2);// 展现多态的特性  动态联编(在程序运行后才能确定具体的函数调用),函数重写
}

int main(){
    parent p;
    child c;

    how_to_print(&p);//I'm Parent. 父类中定义
    c.parent::print();//I'm Parent.从父类中继承
    how_to_print(&c);//I'm child.  在子类中重写/覆盖

    p.func();         // 静态联编 void func()
    p.func(1);        // 静态联编 void func(int i) : 1
    p.func(1, 2);     // 静态联编 void func(int i, int j) : (1,2)

    cout << endl;

    c.func(1, 2);     // 静态联编 void func(int i, int j) : 3
    run(&p);    //(1,2)
    run(&c);   //3
    return 0;
}

