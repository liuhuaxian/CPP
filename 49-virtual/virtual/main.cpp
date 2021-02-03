#include <iostream>
#include <string>
using namespace std;

class parent{
public:
    virtual void print(){//��virtual�����ĺ���Ϊ�麯�� ������д�����̬ʵ��
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
    p->print();//�˴�չ�ֶ�̬����Ϊ :)
}

void run(parent* p){
    p->func(1,2);// չ�ֶ�̬������  ��̬����(�ڳ������к����ȷ������ĺ�������),������д
}

int main(){
    parent p;
    child c;

    how_to_print(&p);//I'm Parent. �����ж���
    c.parent::print();//I'm Parent.�Ӹ����м̳�
    how_to_print(&c);//I'm child.  ����������д/����

    p.func();         // ��̬���� void func()
    p.func(1);        // ��̬���� void func(int i) : 1
    p.func(1, 2);     // ��̬���� void func(int i, int j) : (1,2)

    cout << endl;

    c.func(1, 2);     // ��̬���� void func(int i, int j) : 3
    run(&p);    //(1,2)
    run(&c);   //3
    return 0;
}

