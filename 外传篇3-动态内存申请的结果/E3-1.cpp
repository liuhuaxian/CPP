#include <iostream>
#include <new>
#include <cstdlib>
#include <exception>
/*
malloc 函数申请失败时返回 NULL 值
    new 关键字申请失败时（根据编译器不同）
        返回 NULL 值 （古代）
        抛出 std::bad_alloc 异常 （现代）
		
问题： new 语句中的异常是怎么抛出来的呢？
new 关键字在 C++ 规范中的标准行为   在堆空间申请足够的内存
成功：在获取的空间中调用构造函数创建对象 返回对象的地址
失败 抛出 std::bad_alloc 异常

new 关键字在 C++ 规范中的标准行为
new 在分配内存时,如果空间不足,会调用全局的new_handler()函数,函数中抛出 std::bad_alloc 异常
可以自定义 new_handler() 函数,处理默认的 new 内存分配失败的情况

new_handler() 中，可以手动做一些内存整理的工作，使得更多的堆空间可以被使用。
new_handler() 函数的替换,自定义一个无返回值无参数的函数
调用 set_new_handler() 设置自定义的函数,参数类型为 void(*)(),返回值为默认的 new_handler() 函数入口地址

*/
using namespace std;

class Test
{
    int m_value;
public:
    Test()
    {
        cout << "Test()" << endl;
        
        m_value = 0;
    }
    
    ~Test()
    {
        cout << "~Test()" << endl;  
    }
    
    void* operator new (size_t size) throw()
    {
        cout << "operator new: " << size << endl;
        
        // return malloc(size);
        
        return NULL;  // 注意这里！ 模拟内存申请失败
    }
    void* operator new[] (size_t size) throw()
    {
        cout << "operator new[]:" << size << endl;
        //return malloc(size);
        return NULL;// 注意这里！ 模拟内存申请失败
    
    void operator delete (void* p)
    {
        cout << "operator delete: " << p << endl;
        
        free(p);
    }
     
    
    void operator delete[] (void* p)
    {
        cout << "operator delete[]: " << p << endl;
        
        free(p);
    }
};

void my_new_handler()//定义一个自己的new_handle()函数
{
    cout << "void my_new_handler()" << endl;
}
/*
系统提示出现了std::bad_alloc异常。
已知：在使用new分配内存空间时，内存空间不够时就会抛出该异常。
解决：在程序中加入delete和clear及时释放内存，
并且对原始数据进行分割处理。
new_handler是预定义的函数指针，类型是
*/
/*首先，namespace std中有如下定义：
Typedef void  (*new_handler)();
https://blog.csdn.net/wzxq123/article/details/51502356
        new_handler  set_new_handler(new_handler  new_p) throw();//C++98
        new_handler  set_new_handler (new_handler  new_p) noexcept;//C++11
译文开始：对于函数set_new_handler

函数说明

1.   set_new_handler函数的作用是设置new_p指向的函数为new操作或new[]操作失败时调用的处理函数。

2.   设置的处理函数可以尝试使更多空间变为可分配状态，这样新一次的new操作就可能成功。
当且仅当该函数成功获得更多可用空间它才会返回；
否则它将抛出bad_alloc异常（或者继承该异常的子类）或者终止程序（例如调用abort或exit）。		
		*/
void ex_func_1()//证明new_handle()全局函数的存在
{//set_new_handler()返回值是原来的处理函数
    new_handler func = set_new_handler(my_new_handler);
    
    try
    {//默认情况下是没有处理函数的,显然func为空
        cout << "func = " << func << endl;
        
        if( func )
        {
            func();
        }
    }
	//这里是为了证明默认的new_handler()处理函数确实是要抛出
	//bad_alloc异常的
    catch(const bad_alloc&)
    {
        cout << "catch(const bad_alloc&)" << endl;
    }
}

void ex_func_2()
{
    Test* pt = new Test();
    
    cout << "pt = " << pt << endl;
    
    delete pt;
    
    pt = new Test[5];
    
    cout << "pt = " << pt << endl;
    
    delete[] pt; 
}

void ex_func_3()
{//不管结果是什么都不要抛出异常,申请内存失败了返回空指针就可以了
    int* p = new(nothrow) int[10];
    
    // ... ...
    
    delete[] p; 
    
    int bb[2] = {0};
    
    struct ST
    {
        int x;
        int y;
    };
    //在指定的内存空间上ST创建对象
    ST* pt = new(bb) ST();
    
    pt->x = 1;
    pt->y = 2;
    
    cout << bb[0] << endl;
    cout << bb[1] << endl;
    
    pt->~ST();//需要手动调用析构函数
}

int main(int argc, char *argv[])
{
	//BCC编译器是有默认处理函数的,1说明不同的编译器new失败的行为是有区别的
    // ex_func_1();输出:func=0 说明了new_handler()并没有全局的处理函数
    // ex_func_2();
    // ex_func_3();
    
    return 0;
}

