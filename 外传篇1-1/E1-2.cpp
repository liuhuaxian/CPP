#include <iostream>
#include <cstdlib>
#include <exception>

using namespace std;

void my_terminate()
{
    cout << "void my_terminate()" << endl;
    exit(1);//exit()函数确保所有全局对象和静态局部对象全部都正常的析构
	//abort()
}

class Test 
{
public:
    Test() 
    {
        cout << "Test()"; 
        cout << endl;
    }
	
    ~Test() 
    {
        cout << "~Test()"; 
        cout << endl;
    }
};


int main()
{
    set_terminate(my_terminate);
    
    static Test t;//定义了一个静态的局部对象
    
    throw 1;
	
    return 0;
}
/*输出
Test()
void my_terminate()
~Test()
*/
/*
第10行把exit()换成abort()的打印信息
Test()
void my_terminate()
已放弃(吐核)

abort()函数异常终止,在异常终止的时候不会调用任何对象的析构函数
*/

//总结2个重要的知识点：
//①在main函数中扔出去的异常如果没有被处理，会被最终的全局结束函数处理掉
//②c++编译器之间是存在差异的

//在析构函数中抛出异常会发生什么：造成内存泄漏
//不允许在析构函数中抛出异常,原因是析构函数是释放资源的地方,有可能导致资源得不到释放,
//有可能造成全局的处理函数terminate重复的调用，让系统计入不稳定的状态。terminate()函数异常终止
//调用abort()函数，在调用abort()函数之前有可能会打印资格字符串或者是弹出一个对话框出来
