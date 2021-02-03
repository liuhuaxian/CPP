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
    A *p2 = new B(); //���Ӽ�����ԭ�� ��������
    p2->Do();//��̬�� ������virtual�͵���ָ��ָ���ʵ���ڴ�ռ���Ķ���
    delete p2;//p2->������������virtual,��ȡp2ָ���Լ�������(A)����Ķ���

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
