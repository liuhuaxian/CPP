#include <iostream>
#include <cstdlib>
#include <exception>

using namespace std;

void my_unexpected()
{
    cout << "void my_unexpected()" << endl;
    // exit(1);
    throw 1;
}

void func() throw(int)
{
    cout << "func()";
    cout << endl;
    
    throw 'c';
}

int main()
{
    set_unexpected(my_unexpected);
    
    try 
    {
        func();
    } 
    catch(int) 
    {
        cout << "catch(int)";
        cout << endl;
    } 
    catch(char) 
    {
        cout << "catch(char)";
        cout << endl;
    }

    return 0;
}
/*
linux输出
func()
void my_unexpected()
catch(int)
*/