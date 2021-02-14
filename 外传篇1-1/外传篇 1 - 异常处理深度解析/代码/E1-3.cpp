#include <iostream>
#include <cstdlib>
#include <exception>

using namespace std;

void my_terminate()
{
    cout << "void my_terminate()" << endl;
    // exit(1);
    abort();
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
        
        throw 2;
    }
};


int main()
{
    set_terminate(my_terminate);
    
    static Test t;
    
    throw 1;
	
    return 0;
}
