#include <iostream>
#include <string>
using namespace std;
class boss{
public:
    int fight(){
        int ret = 10;
        cout << "Boss::fight() : " << ret << endl;
        return ret;
    }
};

class master{
public:
    virtual int eightswordkill(){
        int ret = 8;
        cout << "Master::eightSwordKill() : " << ret << endl;
        return ret;
    }
};

class newmaster:public master{
public:
    int eightswordkill(){
        int ret = master::eightswordkill()*2;//16  子类中想用父类的函数,可以用作用域分辨符::
        cout << "newmaster::eightswordkill()" << ret << endl;
        return ret;
    }
};

void pk(master* ma,boss*bo){
    int m = ma->eightswordkill();
    int b = bo->fight();
    if(m > b){
        cout << "boss killed.." <<endl;
    }else{
        cout << "master killed.." <<endl;
    }
}
int main(){
    master ma;
    boss bo;
    cout << "Master vs Boss" << endl;
    pk(&ma,&bo);

    cout << "NewMaster vs Boss" << endl;
    cout << endl;
    newmaster newm;//注意这里的输出！Master::eightSwordKill() : 8  newmaster::eightswordkill()16
    pk(&newm,&bo);//Boss::fight() : 10
    return 0;
}

