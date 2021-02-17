#include <iostream>
#include <new>
#include <cstdlib>
#include <exception>

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
    
    void* operator new (unsigned int size) throw()
    {
        cout << "operator new: " << size << endl;
        
        // return malloc(size);
        
        return NULL;
    }
    
    void operator delete (void* p)
    {
        cout << "operator delete: " << p << endl;
        
        free(p);
    }
    
    void* operator new[] (unsigned int size) throw()
    {
        cout << "operator new[]: " << size << endl;
        
        // return malloc(size);
        
        return NULL;
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
{
    int* p = new(nothrow) int[10];
    
    // ... ...
    
    delete[] p; 
    
    int bb[2] = {0};
    
    struct ST
    {
        int x;
        int y;
    };
    
    ST* pt = new(bb) ST();
    
    pt->x = 1;
    pt->y = 2;
    
    cout << bb[0] << endl;
    cout << bb[1] << endl;
    
    pt->~ST();
}

int main(int argc, char *argv[])
{
	//BCC编译器是有默认处理函数的,1说明不同的编译器new失败的行为是有区别的
    // ex_func_1();输出:func=0 说明了new_handler()并没有全局的处理函数
    // ex_func_2();
    // ex_func_3();
    
    return 0;
}

